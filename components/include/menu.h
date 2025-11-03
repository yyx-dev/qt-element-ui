#pragma once

#include "icon.h"

#include <QTreeWidget>
#include <QWidget>


namespace Element
{
    class MenuItemWidget : public QWidget
    {
        Q_OBJECT

    public:
        using Item = QTreeWidgetItem;

        enum class Type
        {
            TopItem,
            SubItem,
            GroupDesc,
        };

    public:
        Type getType() { return _type; }

    public:
        MenuItemWidget(Type type, const QString& text, Item* item, QWidget* parent = nullptr);
        MenuItemWidget(Type type, const QString& text, Icon::Name icon, Item* item, QWidget* parent = nullptr);

    protected:
        void paintEvent(QPaintEvent* event) override;

    private:
        Type _type;
        QString _text;
        Icon::Name _icon;
        Item* _item;
    };

    class Menu : public QTreeWidget
    {
        Q_OBJECT
    public:
        using Item = QTreeWidgetItem;

    public:
        Item* addTopItem(const QString& text);
        Item* addTopItem(Icon::Name icon, const QString& text);

        Menu& addSubItem(Item* topLevelItem, const QString& text);
        Menu& addGroupDesc(Item* topLevelItem, const QString& text);

    public:
        Menu(QWidget* parent = nullptr);

    protected:
        void mousePressEvent(QMouseEvent* event) override;

    private:
    private:
    };

}
