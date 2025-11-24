#pragma once

#include <QWidget>

namespace Element
{
    class ShadowEf
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
