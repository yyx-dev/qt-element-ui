#pragma once

#include "appbar.h"
#include "menu.h"

#include <QWidget>
#include <QVBoxLayout>

namespace Example
{
    class Widget : public QWidget
    {
        Q_OBJECT

    public:
        Widget(QWidget* parent = nullptr);

    protected:

    private:
        QVBoxLayout* _layout;
        Element::AppBar* _appbar;
        Element::Menu* _menu;
    };
}