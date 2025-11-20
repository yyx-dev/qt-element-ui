#include "menu.h"

#include "base.h"
#include "color.h"
#include "qglobal.h"

#include <QMouseEvent>
#include <QPainter>
#include <QtMath>

namespace Element
{
    MenuItemWidget::MenuItemWidget(Type type, const QString& text, Item* item, QWidget* parent)
        : MenuItemWidget(type, text, Icon::None, item, parent)
    {}

    MenuItemWidget::MenuItemWidget(Type type, const QString& text, Icon::Name icon, Item* item, QWidget* parent)
        : QWidget(parent)
        , _type(type)
        , _text(text)
        , _icon(icon)
        , _item(item)
    {
        setFixedHeight(_type == Type::TopItem ? 70 : _type == Type::SubItem ? 60 : 40);
        setFont(FontHelper().setPixelSize(15).getFont());
        if (_type == Type::TopItem || _type == Type::SubItem)
            setCursor(Qt::PointingHandCursor);
    }

    void MenuItemWidget::paintEvent(QPaintEvent*)
    {
        QPainter painter(this);
        QRect rect = this->rect();

        bool selected = _item->isSelected();
        bool hovered = underMouse();

        // 绘制背景
        painter.fillRect(rect, _type == Type::GroupDesc ? Color::baseBackground()
                                              : hovered ? Color::primaryL5()
                                             : selected ? Color::primaryL5() : Color::baseBackground());
        // 绘制图标
        if (!Icon::isNone(_icon))
        {
            QIcon icon = Icon::instance().getIcon(_icon, selected ? Color::primary() : Color::primaryText(), 20);
            icon.paint(&painter, rect.adjusted(30, 0, 0, 0), Qt::AlignLeft | Qt::AlignVCenter);
        }

        // 绘制文本
        painter.setPen(_type == Type::GroupDesc ? Color::secondaryText()
                                     : selected ? Color::primary() : Color::primaryText());
        QRect textRect = rect.adjusted(!Icon::isNone(_icon) ? 60
                                   : _type == Type::TopItem ? 30 : 50, 0, 0, 0);

        painter.drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, _text);

        // 绘制箭头
        if (_type == Type::TopItem && _item->childCount() > 0)
        {
            QIcon icon = Icon::instance().getIcon(_item->isExpanded() ? Icon::ArrowUp : Icon::ArrowDown, Color::primaryText(), 14);
            icon.paint(&painter, rect.adjusted(0, 0, -sc(20), 0), Qt::AlignRight | Qt::AlignVCenter);
        }
    }

    Menu::Menu(QWidget* parent)
        : QTreeWidget(parent)
        , _minWidth(sc(60))
        , _maxWidth(sc(200))
        , _width(_minWidth)
    {
        setHeaderHidden(true);
        setRootIsDecorated(false);
        setIndentation(0);
        setColumnCount(1);

        setMinimumWidth(_minWidth);
        setMaximumWidth(_maxWidth);

        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        setStyleSheet("QTreeWidget { \
            border: none; \
            border-right: 1px solid " + Color::baseBorder() + "; }" );
    }

    Menu::Item* Menu::addTopItem(const QString& text)
    {
        return addTopItem(Icon::None, text);
    }

    Menu::Item* Menu::addTopItem(Icon::Name icon, const QString& text)
    {
        Item* item = new Item(this);
        Widget* widget = new Widget(Widget::Type::TopItem, text, icon, item);
        setItemWidget(item, 0, widget);

        updateWidth(Widget::Type::TopItem, icon, text);
        return item;
    }

    Menu::Item* Menu::addSubItem(Item* topItem, const QString& text)
    {
        Item* item = new Item(topItem);
        Widget* widget = new Widget(Widget::Type::SubItem, text, item);
        setItemWidget(item, 0, widget);

        updateWidth(Widget::Type::SubItem, Icon::None, text);
        return item;
    }

    void Menu::addGroupDesc(Item* topItem, const QString& text)
    {
        Item* item = new Item(topItem);
        Widget* widget = new Widget(Widget::Type::GroupDesc, text, item);
        setItemWidget(item, 0, widget);
    }

    void Menu::mousePressEvent(QMouseEvent* event)
    {
        if (event->button() == Qt::LeftButton)
        {
            Item* item = itemAt(event->pos());

            if (!item) return;

            if (item->childCount() > 0) // 有子项
            {
                item->setExpanded(!item->isExpanded());
                event->accept();
            }
            else
            {
                auto* widget = qobject_cast<Widget*>(itemWidget(item, 0));
                if (!widget) return;

                if (widget->getType() != Widget::Type::GroupDesc)
                {
                    itemClicked(item);
                }
                event->accept();
            }
        }

        QTreeWidget::mousePressEvent(event);
    }

    void Menu::updateWidth(Widget::Type type, Icon::Name icon, const QString& text)
    {
        int width = FontHelper().setPixelSize(15).getTextWidth(text)
                    + (!Icon::isNone(icon) ? 60 : type == Widget::Type::TopItem ? 30 : 50)
                    + 20 + 35;
        width = qBound(_width, width, _maxWidth);

        if (width > _width)
        {
            setFixedWidth(width);
            _width = width;
        }
    }

}