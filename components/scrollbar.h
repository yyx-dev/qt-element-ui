#pragma once

#include "inputtext.h"

#include <QApplication>

namespace Element
{

    class ScrollBar
    {
    public:
        static void setAppScrollBar();
        static void setInputTextScrollBar(InputText* inputText);
    };

}
