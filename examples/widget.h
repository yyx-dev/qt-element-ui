#pragma once

#include "appbar.h"
#include "menu.h"
#include "stack.h"

#include <QWidget>
#include <QVBoxLayout>

namespace Example
{
    class Widget : public QWidget
    {
        Q_OBJECT

    public:
        Widget(QWidget* parent = nullptr);

        void setupUI();

    private:
        QVBoxLayout* _layout;
        Element::AppBar* _appbar;
        Element::Menu* _menu;
        Element::Stack* _stack;
    };
}