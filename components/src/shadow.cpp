#include "shadow.h"

namespace Element
{
    void Shadow::setShadow(QWidget* widget, Type type)
    {
        QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(widget);

        if (type == Type::Basic)
        {
            shadow->setBlurRadius(20);
            shadow->setOffset(0, 8);
            shadow->setColor(QColor(0, 0, 0, 20));
        }
        else if (type == Type::Light)
        {
            shadow->setBlurRadius(12);
            shadow->setOffset(0, 0);
            shadow->setColor(QColor(0, 0, 0, 30));
        }
        else if (type == Type::Lighter)
        {
            shadow->setBlurRadius(6);
            shadow->setOffset(0, 0);
            shadow->setColor(QColor(0, 0, 0, 30));
        }
        else if (type == Type::Dark)
        {
            shadow->setBlurRadius(32);
            shadow->setOffset(0, 12);
            shadow->setColor(QColor(0, 0, 0, 30));
        }

        widget->setGraphicsEffect(shadow);
    }

}
