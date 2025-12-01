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
        , _dragProxy(new DragProxy(this))
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
    }

    QMargins FramelessWindow::getDraMargins()
    {
        return _dragProxy->getMargins();
    }

    void FramelessWindow::showEvent(QShowEvent* event)
    {
        QWidget::showEvent(event);
        QRect geo = QGuiApplication::primaryScreen()->availableGeometry();
        move((geo.width() - width()) / 2, (geo.height() - height()) / 2);
    }


    DragProxy::DragProxy(QWidget* parent)
        : QObject(parent)
        , _proxyWidget(parent)
    {
        _proxyWidget->setMouseTracking(true);
        _proxyWidget->installEventFilter(this);
        setMargins(_margins);
    }

    void DragProxy::setMargins(const QMargins& m)
    {
        setMargins(m.top(), m.right(), m.bottom(), m.left());
    }

    void DragProxy::setMargins(int top, int right, int bottom, int left)
    {
        _margins = QMargins(left, top, right, bottom);
        checkRegions();
    }

    QMargins DragProxy::getMargins()
    {
        return _margins;
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

    bool DragProxy::eventFilter(QObject* watched, QEvent* event)
    {
        if (watched != _proxyWidget)
            return QObject::eventFilter(watched, event);

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
                if (_regionPressed == Inner)
                {
                    // _proxyWidget->move(_originGeo.topLeft() + curPosGlobal - _originPosGlobal);
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
            QMouseEvent* mouseEv = (QMouseEvent*)event;
            if (mouseEv->button() == Qt::LeftButton)
            {
                _mousePressed = true;

                QPoint curPos = mouseEv->pos();
                _regionPressed = hitRegion(curPos);
                _originPosGlobal = _proxyWidget->mapToGlobal(curPos);
                _originGeo = _proxyWidget->geometry();

                stopCursorTimer();
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
            checkRegions();
        }
        else if (event->type() == QEvent::Leave)
        {
            _proxyWidget->setCursor(Qt::ArrowCursor);
            stopCursorTimer();
        }
        else if (event->type() == QEvent::Timer)
        {
            if (static_cast<QTimerEvent*>(event)->timerId() == _cursorTimerId)
            {
                if (_regions[Inner].contains(_proxyWidget->mapFromGlobal(QCursor::pos())))
                {
                    _proxyWidget->setCursor(Qt::ArrowCursor);
                    stopCursorTimer();
                }
            }
        }

        return QObject::eventFilter(watched, event);
    }

    void DragProxy::startCursorTimer()
    {
        stopCursorTimer();
        _cursorTimerId = _proxyWidget->startTimer(100);
    }

    void DragProxy::stopCursorTimer()
    {
        if (_cursorTimerId != 0)
        {
            _proxyWidget->killTimer(_cursorTimerId);
            _cursorTimerId = 0;
        }
    }

    void DragProxy::checkRegions()
    {
        int width = _proxyWidget->width(), height = _proxyWidget->height();
        int left = _margins.left(), right = _margins.right(), top = _margins.top(), bottom = _margins.bottom();

        _regions[Top]         = QRect(left, 0, width - left - right, top);
        _regions[TopRight]    = QRect(width - right, 0, right, top);
        _regions[Right]       = QRect(width - right, top, right, height - top - bottom);
        _regions[RightBottom] = QRect(width - right, height - bottom, right, bottom);
        _regions[Bottom]      = QRect(left, height - bottom, width - left - right, bottom);
        _regions[LeftBottom]  = QRect(0, height - bottom, left, bottom);
        _regions[Left]        = QRect(0, top, left, height - top - bottom);
        _regions[LeftTop]     = QRect(0, 0, left, top);
        _regions[Inner]       = QRect(left, top, width - left - right, height - top - bottom);
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
