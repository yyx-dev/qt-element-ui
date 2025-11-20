#pragma once

#include "menu.h"

#include <QStackedWidget>

namespace Element
{
    class Stack : public QStackedWidget
    {
        Q_OBJECT
    public:
        Stack& setMenu(Menu* menu);
        Stack& addWidget(Menu::Item* item, QWidget* widget);

    public:
        Stack(QWidget* parent = nullptr);
        Stack(Menu* menu, QWidget* parent = nullptr);

    protected:

    private:
        void showWidget(Menu::Item* item);
        QWidget* defaultWidget(Menu::Item* item);

    private:
        Menu* _menu;
        QHash<Menu::Item*, int> _item2index;
    };
}