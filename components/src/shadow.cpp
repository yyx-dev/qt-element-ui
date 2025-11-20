#include "shadow.h"
#include <QPainter>
#include <QEvent>

namespace Element
{
    void ShadowEf::setShadow(QWidget* widget, Type type)
    {
        if (!widget) return;

        QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(widget);

        if (type == Type::Basic)
        {
            shadow->setBlurRadius(32);
            shadow->setOffset(0, 12);
            shadow->setColor(QColor(0, 0, 0, 0.04 * 255));
        }
        else if (type == Type::Light)
        {
            shadow->setBlurRadius(12);
            shadow->setOffset(0, 0);
            shadow->setColor(QColor(0, 0, 0, 0.12 * 255));
        }
        else if (type == Type::Lighter)
        {
            shadow->setBlurRadius(6);
            shadow->setOffset(0, 0);
            shadow->setColor(QColor(0, 0, 0, 0.12 * 255));
        }
        else if (type == Type::Dark)
        {
            shadow->setBlurRadius(48);
            shadow->setOffset(0, 16);
            shadow->setColor(QColor(0, 0, 0, 0.08 * 255));
        }

        if (!widget->autoFillBackground())
        {
            QPalette pal = widget->palette();
            pal.setColor(QPalette::Window, Qt::white);
            widget->setPalette(pal);
            widget->setAutoFillBackground(true);
        }
        widget->setGraphicsEffect(shadow);
    }

    Mask* ShadowEf::setBgMask(QWidget* widget)
    {
        return new Mask(widget);
    }

    Mask::Mask(QWidget* partner)
        : QWidget(partner->parentWidget())
        , _partner(partner)
    {
        setGeometry(parentWidget()->rect());
        partner->installEventFilter(this);
    }

    bool Mask::eventFilter(QObject* watched, QEvent* event)
    {
        if (watched == _partner)
        {
            if (event->type() == QEvent::Show)
            {
                show();
                stackUnder(_partner);
            }
            else if (event->type() == QEvent::Hide)
            {
                hide();
            }
            else if (event->type() == QEvent::Destroy)
            {
                deleteLater();
            }
            return false;
        }
        else if (watched == parentWidget())
        {
            if (event->type() == QEvent::Resize)
            {
                setGeometry(parentWidget()->rect());
            }
            return false;
        }

        return QWidget::eventFilter(watched, event);
    }

    void Mask::paintEvent(QPaintEvent* event)
    {
        QPainter painter(this);
        painter.fillRect(rect(), QColor(0, 0, 0, 128));
    }

    void Mask::mousePressEvent(QMouseEvent* event)
    {
        emit clicked();
    }
}
