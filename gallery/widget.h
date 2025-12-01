#pragma once

#include "appbar.h"
#include "menu.h"
#include "stack.h"
#include "frameless.h"

#include <QWidget>
#include <QVBoxLayout>

namespace Gallery
{
    class Widget : public Element::FramelessWindow
    {
        Q_OBJECT
    public:
        Widget(QWidget* parent = nullptr);

    private:
        void setupContainer();
        void setupComponents();

    private:
        QVBoxLayout* _layout;
        Element::AppBar* _appbar;
        Element::Menu* _menu;
        Element::Stack* _stack;
    };
}
