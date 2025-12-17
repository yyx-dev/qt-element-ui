#pragma once

#include "menu.h"

#include <QStackedWidget>
#include <QScrollArea>

namespace Element
{
    class Stack : public QStackedWidget
    {
        Q_OBJECT
    public:
        Stack& setFooter(QWidget* footer);
        Stack& addWidget(Menu::Item* item, QWidget* widget);

    public:
        Stack(QWidget* parent = nullptr);

    public slots:
        void showWidget(Menu::Item* item);

    private:
        QWidget* defaultWidget(Menu::Item* item);
        void setMouseTrackingRec(QWidget* widget, bool enable = true);

    private:
        Menu* _menu;
        QWidget* _footer;
        QHash<Menu::Item*, int> _item2index;
    };

    class ScrollArea : public QScrollArea
    {
        Q_OBJECT
    public:
        ScrollArea(QWidget* parent = nullptr);

    protected:
        void mousePressEvent(QMouseEvent* e) override;
        void mouseMoveEvent(QMouseEvent* e) override;
        void mouseReleaseEvent(QMouseEvent* e) override;
    };
}