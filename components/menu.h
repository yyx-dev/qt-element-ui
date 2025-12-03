#pragma once

#include "icon.h"

#include <QTreeWidget>
#include <QStack>


namespace Element
{
    class MenuItemWidget : public QWidget
    {
        Q_OBJECT

    public:
        using Item = QTreeWidgetItem;
        using Widget = MenuItemWidget;

        enum class Type
        {
            TopItem,
            SubItem,
            GroupDesc,
        };

    public:
        Type getType() { return _type; }
        QString getText() { return _text; }

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
        using Widget = MenuItemWidget;

    public:
        Item* addTopItem(const QString& text);
        Item* addTopItem(Icon::Name icon, const QString& text);
        Item* addSubItem(Item* topItem, const QString& text);
        void  addGroupDesc(Item* topItem, const QString& text);

    public slots:
        void jumpToLastItem();

    signals:
        void itemClicked(Item* item);
        void historyEmpty();
        void historyFilled();

    public:
        Menu(QWidget* parent = nullptr);

    protected:
        void mousePressEvent(QMouseEvent* event) override;
        void mouseMoveEvent(QMouseEvent* event) override;
        void mouseReleaseEvent(QMouseEvent* event) override;

    private:
        void updateWidth(Widget::Type type, Icon::Name icon, const QString& text);

    private:
        int _minWidth = 0, _maxWidth = 0, _width = 0;
        QStack<Item*> _history;
    };

}
