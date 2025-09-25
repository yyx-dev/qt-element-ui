#include "shadow.h"

namespace Element
{
    void Shadow::setShadow(QWidget* widget, Type type)
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

        widget->setGraphicsEffect(shadow);
    }

}
