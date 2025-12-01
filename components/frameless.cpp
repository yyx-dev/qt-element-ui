#include "frameless.h"

#include <QGuiApplication>
#include <QScreen>
#include <QMouseEvent>
#include <dwmapi.h>

#include <QDebug>

namespace Element
{
    FramelessWindow::FramelessWindow(QWidget* parent)
        : QWidget(parent)
    {
        setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

        HWND hwnd = reinterpret_cast<HWND>(winId());

        LONG style = GetWindowLongPtr(hwnd, GWL_STYLE);
        style &= ~(WS_CAPTION | WS_THICKFRAME | WS_BORDER | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
        SetWindowLongPtr(hwnd, GWL_STYLE, style);

        setAttribute(Qt::WA_DontCreateNativeAncestors);

        MARGINS margins = { 1, 1, 1, 1 };
        DwmExtendFrameIntoClientArea(hwnd, &margins);

        int value = 2;
        DwmSetWindowAttribute(hwnd, DWMWA_NCRENDERING_POLICY, &value, sizeof(value));
        DwmSetWindowAttribute(hwnd, DWMWA_ALLOW_NCPAINT, &value, sizeof(value));

        SetWindowPos(hwnd, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

        DragProxy* dragProxy = new DragProxy(this);
    }

    void FramelessWindow::showEvent(QShowEvent *event)
    {
        QWidget::showEvent(event);
        QRect geo = QGuiApplication::primaryScreen()->availableGeometry();
        move((geo.width() - width()) / 2, (geo.height() - height()) / 2);
    }


    DragProxy::DragProxy(QWidget* parent)
        : QObject((QObject*)parent)
        , _proxyWidget(parent)
        , _mousePressed(false)
        , _regionPressed(Unknown)
        , _cursorTimerId(0)
    {
        _proxyWidget->setMouseTracking(true);
        _proxyWidget->installEventFilter(this);

        setBorderWidth(8, 8, 8, 8);
    }

    void DragProxy::setBorderWidth(int top, int right, int bottom, int left)
    {
        _top = top, _right = right, _bottom = bottom, _left = left;
        makeRegions();
    }

    void DragProxy::updateGeometry(int x, int y, int w, int h)
    {
        int minWidth = _proxyWidget->minimumWidth();
        int minHeight = _proxyWidget->minimumHeight();
        int maxWidth = _proxyWidget->maximumWidth();
        int maxHeight = _proxyWidget->maximumHeight();

        if (w < minWidth || w > maxWidth || h < minHeight || h > maxHeight)
            return;

        _proxyWidget->setGeometry(x, y, w, h);
    }

    bool DragProxy::eventFilter(QObject* obj, QEvent* event)
    {
        if (event->type() == QEvent::MouseMove)
        {
            QMouseEvent* mouseEvent = (QMouseEvent*)event;
            QPoint curPosLocal = mouseEvent->pos();
            Region region = hitRegion(curPosLocal);

            QPoint curPosGlobal = _proxyWidget->mapToGlobal(curPosLocal);

            if (!_mousePressed) // 鼠标未按下
            {
                switch (region)
                {
                case Top:
                case Bottom:
                    _proxyWidget->setCursor(Qt::SizeVerCursor);
                    break;
                case TopRight:
                case LeftBottom:
                    _proxyWidget->setCursor(Qt::SizeBDiagCursor);
                    break;
                case Right:
                case Left:
                    _proxyWidget->setCursor(Qt::SizeHorCursor);
                    break;
                case RightBottom:
                case LeftTop:
                    _proxyWidget->setCursor(Qt::SizeFDiagCursor);
                    break;
                default:
                    _proxyWidget->setCursor(Qt::ArrowCursor);
                    break;
                }

                startCursorTimer();
            }
            else // 鼠标已按下
            {
                QRect geo = _proxyWidget->geometry();

                if (_regionPressed == Inner)
                {
                    _proxyWidget->move(_originGeo.topLeft() + curPosGlobal - _originPosGlobal);
                }
                else if (_regionPressed == Top)
                {
                    int dY = curPosGlobal.y() - _originPosGlobal.y();
                    updateGeometry(_originGeo.x(), _originGeo.y() + dY, _originGeo.width(), _originGeo.height() - dY);
                }
                else if (_regionPressed == TopRight)
                {
                    QPoint dXY = curPosGlobal - _originPosGlobal;
                    updateGeometry(_originGeo.x(), _originGeo.y() + dXY.y(), _originGeo.width() + dXY.x(), _originGeo.height() - dXY.y());
                }
                else if (_regionPressed == Right)
                {
                    int dX = curPosGlobal.x() - _originPosGlobal.x();
                    updateGeometry(_originGeo.x(), _originGeo.y(), _originGeo.width() + dX, _originGeo.height());
                }
                else if (_regionPressed == RightBottom)
                {
                    QPoint dXY = curPosGlobal - _originPosGlobal;
                    updateGeometry(_originGeo.x(), _originGeo.y(), _originGeo.width() + dXY.x(), _originGeo.height() + dXY.y());
                }
                else if (_regionPressed == Bottom)
                {
                    int dY = curPosGlobal.y() - _originPosGlobal.y();
                    updateGeometry(_originGeo.x(), _originGeo.y(), _originGeo.width(), _originGeo.height() + dY);
                }
                else if (_regionPressed == LeftBottom)
                {
                    QPoint dXY = curPosGlobal - _originPosGlobal;
                    updateGeometry(_originGeo.x() + dXY.x(), _originGeo.y(), _originGeo.width() - dXY.x(), _originGeo.height() + dXY.y());
                }
                else if (_regionPressed == Left)
                {
                    int dX = curPosGlobal.x() - _originPosGlobal.x();
                    updateGeometry(_originGeo.x() + dX, _originGeo.y(), _originGeo.width() - dX, _originGeo.height());
                }
                else if (_regionPressed == LeftTop)
                {
                    QPoint dXY = curPosGlobal - _originPosGlobal;
                    updateGeometry(_originGeo.x() + dXY.x(), _originGeo.y() + dXY.y(), _originGeo.width() - dXY.x(), _originGeo.height() - dXY.y());
                }
            }
        }
        else if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent* mouseEvent = (QMouseEvent*)event;
            if (mouseEvent->button() == Qt::LeftButton)
            {
                _mousePressed = true;

                QPoint curPos = mouseEvent->pos();
                _regionPressed = hitRegion(curPos);

                _originPosGlobal = _proxyWidget->mapToGlobal(curPos);
                _originGeo = _proxyWidget->geometry();

                startCursorTimer();
            }
        }
        else if (event->type() == QEvent::MouseButtonRelease)
        {
            _mousePressed = false;
            _regionPressed = Unknown;

            _proxyWidget->setCursor(Qt::ArrowCursor);
        }
        else if (event->type() == QEvent::Resize)
        {
            makeRegions();
            qDebug() << "Resize frameless regions." << _proxyWidget->geometry();
        }
        else if (event->type() == QEvent::Leave)
        {
            _proxyWidget->setCursor(Qt::ArrowCursor);
            startCursorTimer();
        }
        else if (event->type() == QEvent::Timer)
        {
            QTimerEvent* timerEvent = (QTimerEvent*)event;
            if (timerEvent->timerId() == _cursorTimerId)
            {
                if (_regions[Inner].contains(_proxyWidget->mapFromGlobal(QCursor::pos())))
                {
                    _proxyWidget->setCursor(Qt::ArrowCursor);
                    startCursorTimer();
                }
            }
        }

        return QObject::eventFilter(obj, event);
    }

    void DragProxy::startCursorTimer()
    {
        startCursorTimer();
        _cursorTimerId = _proxyWidget->startTimer(50);
    }

    void DragProxy::stopCursorTimer()
    {
        if (_cursorTimerId != 0)
        {
            _proxyWidget->killTimer(_cursorTimerId);
            _cursorTimerId = 0;
        }
    }

    void DragProxy::makeRegions()
    {
        int width = _proxyWidget->width();
        int height = _proxyWidget->height();

        _regions[Top]         = QRect(_left, 0, width - _left - _right, _top);
        _regions[TopRight]    = QRect(width - _right, 0, _right, _top);
        _regions[Right]       = QRect(width - _right, _top, _right, height - _top - _bottom);
        _regions[RightBottom] = QRect(width - _right, height - _bottom, _right, _bottom);
        _regions[Bottom]      = QRect(_left, height - _bottom, width - _left - _right, _bottom);
        _regions[LeftBottom]  = QRect(0, height - _bottom, _left, _bottom);
        _regions[Left]        = QRect(0, _top, _left, height - _top - _bottom);
        _regions[LeftTop]     = QRect(0, 0, _left, _top);
        _regions[Inner]       = QRect(_left, _top, width - _left - _right, height - _top - _bottom);
    }

    DragProxy::Region DragProxy::hitRegion(const QPoint& pos)
    {
        for (int i = 0; i < 9; i++)
        {
            if (_regions[i].contains(pos))
                return Region(i);
        }
        return Unknown;
    }

}