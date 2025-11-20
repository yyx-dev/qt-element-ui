#include "widget.h"
#include "base.h"

namespace Example
{
    Widget::Widget(QWidget* parent)
        : QWidget(parent)
        , _layout(new QVBoxLayout(this))
        , _appbar(new Element::AppBar(this))
        , _menu(new Element::Menu(this))
        , _stack(new Element::Stack(_menu, this))
    {
        setMinimumSize(Element::sc(1200, 741));

        QPalette pal = palette();
        pal.setColor(QPalette::Window, Qt::white);
        setAutoFillBackground(true);
        setPalette(pal);

        QHBoxLayout* layout = new QHBoxLayout;
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);
        layout->addWidget(_menu);
        layout->addWidget(_stack);

        _layout->setContentsMargins(0, 0, 0, 0);
        _layout->setSpacing(0);
        _layout->addWidget(_appbar);
        _layout->addLayout(layout);
    }

    void Widget::setupUI()
    {
        Element::Menu::Item* aim_test = _menu->addTopItem(Element::Icon::Aim, "目标测试");
        _menu->addTopItem(Element::Icon::Aim, "目标测试");
        _menu->addTopItem(Element::Icon::Aim, "目标测试");
        _menu->addTopItem(Element::Icon::Aim, "目标测试");
    }

}