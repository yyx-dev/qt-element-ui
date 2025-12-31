#pragma once

#include "private/utils.h"
#include "shadow.h"
#include "text.h"

#include <QHash>
#include <QLabel>
#include <QMenu>
#include <QPainter>
#include <QWidget>

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#    include <QPainterPath>
#endif
#include <QPaintEvent>
#include <QProxyStyle>
#include <QStyleOptionMenuItem>
#include <QStylePainter>


namespace Element
{
    class MenuforDropdown;

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
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        void enterEvent(QEnterEvent* event) override;
#else
        void enterEvent(QEvent* event) override;
#endif
        void leaveEvent(QEvent* event) override;

    private:
        Text* _text;
        QLabel* _icon;
        MenuforDropdown* _menu;
        QHash<QString, QAction*>* _actions;
    };

    class MenuforDropdown : public QMenu
    {
        Q_OBJECT

    public:
        MenuforDropdown(QWidget* parent = nullptr);

    protected:
        bool event(QEvent* e) override;
    };

}
