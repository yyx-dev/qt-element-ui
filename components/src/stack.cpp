#include "stack.h"
#include "base.h"

#include <QLabel>
#include <QVBoxLayout>

namespace Element
{
    Stack::Stack(QWidget* parent)
        : Stack(nullptr, parent)
    {}

    Stack::Stack(Menu* menu, QWidget* parent)
        : QStackedWidget(parent)
    {
        setMenu(menu);
    }

    Stack& Stack::setMenu(Menu* menu)
    {
        if (menu)
        {
            _menu = menu;
            connect(_menu, &Menu::itemClicked, this, &Stack::showWidget);
        }
        return *this;
    }

    Stack& Stack::addWidget(Menu::Item* item, QWidget* widget)
    {
        int i = QStackedWidget::addWidget(widget);
        _item2index.insert(item, i);
        return *this;
    }

    void Stack::showWidget(Menu::Item* item)
    {
        if (!_item2index.contains(item))
        {
            _item2index.insert(item, count());
            QStackedWidget::addWidget(defaultWidget(item));
        }

        setCurrentIndex(_item2index.value(item));
    }

    QWidget* Stack::defaultWidget(Menu::Item* item)
    {
        QWidget* widget = new QWidget;

        MenuItemWidget* itemWidget = qobject_cast<MenuItemWidget*>(_menu->itemWidget(item, 0));

        QLabel* label = new QLabel(widget);
        label->setText(itemWidget->getText());
        label->setFont(FontHelper().setBold().getFont());
        label->setStyleSheet("QLabel{ font-size: 32px; color: #6B778C; }");

        QVBoxLayout* layout = new QVBoxLayout(widget);
        layout->addWidget(label, 0, Qt::AlignTop);
        return widget;
    }

}