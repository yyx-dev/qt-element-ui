#include "container.h"
#include "private/utils.h"

namespace Element
{

    Container::Container(QWidget* parent)
        : FramelessWindow(parent)
    {}

    ContainerBuilder::ContainerBuilder()
        : _container(new Container)
    {}

    ContainerBuilder& ContainerBuilder::addAppBar()
    {
        _appbar = new AppBar(_container->getDraMargins().top(), _container);
        return *this;
    }

    ContainerBuilder& ContainerBuilder::addMenu()
    {
        _menu = new Menu(_container);
        return *this;
    }

    ContainerBuilder& ContainerBuilder::addStack()
    {
        _stack = new Stack(_container);
        return *this;
    }

    ContainerBuilder& ContainerBuilder::addFooter(QWidget* footer)
    {
        _stack->setFooter(footer);
        return *this;
    }

    ContainerBuilder& ContainerBuilder::addConfigurator(const Configurator& configurator)
    {
        _configurator = configurator;
        return *this;
    }

    Container* ContainerBuilder::build(QWidget* parent)
    {
        _container->setParent(parent);
        setBgColor(_container, Qt::white);

        QVBoxLayout* vlayout = new QVBoxLayout(_container);
        vlayout->setContentsMargins(0, 0, 0, 0);
        vlayout->setSpacing(0);

        QHBoxLayout* hLayout = new QHBoxLayout;
        hLayout->setContentsMargins(0, 0, 0, 0);
        hLayout->setSpacing(0);

        if (_appbar)
        {
            vlayout->addWidget(_appbar);
        }

        if (_menu && _stack)
        {
            hLayout->addWidget(_menu);
            hLayout->addWidget(_stack);
            _container->setMinimumSize(sc(1200, 741));
        }
        else if (!_menu && _stack)
        {
            hLayout->addWidget(_stack);
            _container->setMinimumSize(sc(1000, 741));
        }

        vlayout->addLayout(hLayout);

        if (_configurator)
        {
            _configurator(_menu, _stack);
        }

        connect(_appbar, &AppBar::backButtonClicked, _menu, &Menu::jumpToLastItem);
        connect(_menu, &Menu::historyEmpty, _appbar, &AppBar::disableBackButton);
        connect(_menu, &Menu::historyFilled, _appbar, &AppBar::enableBackButton);
        connect(_menu, &Menu::itemClicked, _stack, &Stack::showWidget);

        return _container;
    }
}
