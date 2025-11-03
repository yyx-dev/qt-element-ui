#include "menu.h"

#include "base.h"
#include "color.h"
#include "qglobal.h"

#include <QMouseEvent>
#include <QPainter>

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
        setFixedWidth(170);
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
                                    : (selected ? Color::primary() : Color::primaryText()));
        QRect textRect = rect.adjusted(_type != Type::TopItem ? 50 :
                                          Icon::isNone(_icon) ? 60 : 70, 0, -20, 0);
        painter.drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, _text);

        // 绘制箭头
        if (_type == Type::TopItem && _item->childCount() > 0)
        {
            QIcon icon = Icon::instance().getIcon(_item->isExpanded() ? Icon::ArrowUp : Icon::ArrowDown, Color::primaryText(), 14);
            icon.paint(&painter, rect.adjusted(130, 0, 0, 0), Qt::AlignLeft | Qt::AlignVCenter);
        }
    }

    Menu::Menu(QWidget* parent)
        : QTreeWidget(parent)
    {
        setHeaderHidden(true);
        setRootIsDecorated(false);
        setIndentation(0);
        setFixedWidth(170);
        setColumnCount(1);
        setStyleSheet("border: none; border-right: 1px solid " + Color::baseBorder() + ';');
    }

    Menu::Item* Menu::addTopItem(const QString& text)
    {
        return addTopItem(Icon::None, text);
    }

    Menu::Item* Menu::addTopItem(Icon::Name icon, const QString& text)
    {
        QTreeWidgetItem* item = new QTreeWidgetItem(this);
        setItemWidget(item, 0, new MenuItemWidget(MenuItemWidget::Type::TopItem, text, icon, item));
        return item;
    }

    Menu& Menu::addSubItem(Item* topLevelItem, const QString& text)
    {
        QTreeWidgetItem* item = new QTreeWidgetItem(topLevelItem);
        setItemWidget(item, 0, new MenuItemWidget(MenuItemWidget::Type::SubItem, text, item));
        return *this;
    }

    Menu& Menu::addGroupDesc(Item* topLevelItem, const QString& text)
    {
        QTreeWidgetItem* item = new QTreeWidgetItem(topLevelItem);
        setItemWidget(item, 0, new MenuItemWidget(MenuItemWidget::Type::GroupDesc, text, item));
        return *this;
    }

    void Menu::mousePressEvent(QMouseEvent* event)
    {
        if (event->button() == Qt::LeftButton)
        {
            QTreeWidgetItem* item = itemAt(event->pos());

            if (!item) return;

            if (item->childCount() > 0)
            {
                item->setExpanded(!item->isExpanded());
                event->accept();
                return;
            }
            else // 需排除groupdesc
            {
                MenuItemWidget* widget = qobject_cast<MenuItemWidget*>(itemWidget(item, 0));
                if (widget && widget->getType() == MenuItemWidget::Type::GroupDesc)
                {
                    event->accept();
                    return;
                }
                else
                {
                    qDebug() << "Menu selected item:" << widget;
                }
            }
        }

        QTreeWidget::mousePressEvent(event);
    }
}