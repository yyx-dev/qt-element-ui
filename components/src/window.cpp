#include "window.h"

#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>

namespace Element
{
    Window::Window(QWidget* parent)
        : QMainWindow(parent)
    {
        setAttribute(Qt::WA_TranslucentBackground);
        setWindowFlag(Qt::FramelessWindowHint);
        setContentsMargins(20, 20, 20, 20);
    }

    void Window::setWidget(QWidget* widget)
    {
        if (!widget) return;

        setMinimumSize(widget->size());
        QMainWindow::setCentralWidget(widget);

        QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(this);
        shadow->setBlurRadius(20);
        shadow->setOffset(0, 0);
        shadow->setColor(QColor(0, 0, 0, 255));
        widget->setGraphicsEffect(shadow);
    }

    void Window::setCentralWidget(QWidget* widget)
    {
        setWidget(widget);
    }

    void Window::changeEvent(QEvent *event)
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

}