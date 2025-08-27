#pragma once

#include <QApplication>

namespace QTElementUI
{

    class ScrollBarSetting
    {
    public:
        ScrollBarSetting();
        void operator()(QApplication* app);
    };

}
