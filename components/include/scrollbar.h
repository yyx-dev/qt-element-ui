#pragma once

#include <QApplication>

namespace Element
{

    class SetScrollBar
    {
    public:
        SetScrollBar();
        void operator()(QApplication* app);
    };

}
