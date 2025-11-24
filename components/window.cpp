#include "window.h"
#include "base.h"

#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>

namespace Element
{
    _ShadowWindow::_ShadowWindow(QWidget* parent)
        : QMainWindow(parent)
    {
        setAttribute(Qt::WA_TranslucentBackground);
        // setAttribute(Qt::WA_TransparentForMouseEvents);
        setWindowFlag(Qt::FramelessWindowHint);
        setContentsMargins(20, 20, 20, 20);
    }

    void _ShadowWindow::setWidget(QWidget* widget)
    {
        if (!widget) return;

        _widget = widget;
        widget->installEventFilter(this);

        setMinimumSize(widget->size());
        setCentralWidget(widget);

        QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(this);
        shadow->setBlurRadius(20);
        shadow->setOffset(0, 0);
        shadow->setColor(QColor(0, 0, 0, 255));
        setGraphicsEffect(shadow);
    }

    void _ShadowWindow::changeEvent(QEvent *event)
    {
        if (event->type() == QEvent::WindowStateChange)
        {
            QGraphicsEffect* shadow = centralWidget()->graphicsEffect();

            if (windowState() & (Qt::WindowMaximized | Qt::WindowFullScreen))
            {
                setContentsMargins(0, 0, 0, 0);
                shadow->setEnabled(false);
            }
            else
            {
                setContentsMargins(20, 20, 20, 20);
                shadow->setEnabled(true);
            }
        }
        QMainWindow::changeEvent(event);
    }

    bool _ShadowWindow::eventFilter(QObject* watched, QEvent* event)
    {
        if (watched == _widget)
        {
            if (event->type() == QEvent::Show)
            {
                show();
                return true;
            }
            else if (event->type() == QEvent::Hide)
            {
                hide();
                return true;
            }
            else if (event->type() == QEvent::Resize)
            {
                applyResize();
                return true;
            }
        }

        return QMainWindow::eventFilter(watched, event);
    }

    void _ShadowWindow::applyResize()
    {
        if (!_widget) return;

        QMargins m = contentsMargins();
        QSize size = _widget->size() + QSize(m.left() + m.right(), m.top() + m.bottom());

        if (this->size() != size)
            resize(size);
    }

    void FramelessEf::setFrameless(QWidget* widget)
    {
        _ShadowWindow* window = new _ShadowWindow;
        window->setWidget(widget);
        window->show();
    }

}