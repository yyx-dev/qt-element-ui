#pragma once

#include "base.h"
#include "text.h"
#include "shadow.h"

#include <QWidget>
#include <QLabel>
#include <QMenu>
#include <QHash>
#include <QPainter>
#include <QStylePainter>
#include <QStyleOptionMenuItem>
#include <QPaintEvent>
#include <QProxyStyle>



namespace Element
{
    class Menu;

    class Dropdown : public QWidget
    {
    Q_OBJECT

    public:
        Dropdown& setText(const QString& text);
        Dropdown& addItem(const QString& name);
        Dropdown& addSeparator();

    public:
        Dropdown(QWidget* parent);
        Dropdown(const QString& text, QWidget* parent);

    protected:
        void enterEvent(QEvent *event) override;
        void leaveEvent(QEvent *event) override;

    private:
        Text* _text;
        QLabel* _icon;
        Menu * _menu;
        QHash<QString, QAction*>* _actions;
    };

    class Menu : public QMenu
    {
    Q_OBJECT

    public:
        Menu(QWidget* parent = nullptr);
    protected:
        bool event(QEvent* e) override;
    };

}
