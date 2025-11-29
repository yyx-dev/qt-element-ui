#pragma once

#include "layout.h"

#include <QWidget>

namespace Gallery
{
    using namespace Element;

    class ButtonPage : public QWidget
    {
        Q_OBJECT
    public:
        ButtonPage(QWidget* parent = nullptr);

    private:
        void setupWidget();

    private:
        Layout* _layout;
    };
}