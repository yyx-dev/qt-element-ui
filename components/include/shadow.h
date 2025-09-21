#pragma once

#include <QGraphicsDropShadowEffect>
#include <QWidget>

namespace Element
{
    class Shadow
    {
    public:
        enum class Type
        {
            Basic,
            Light,
            Lighter,
            Dark,
        };

    public:
        static void setShadow(QWidget* widget, Type type);
    };
}
