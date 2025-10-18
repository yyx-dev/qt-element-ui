#include "sidebar.h"
#include "color.h"
#include "base.h"

#include <QPainter>

#include <QStyleOptionTab>
#include <QMouseEvent>

namespace Element
{
    SideBar::SideBar(QWidget* parent, bool isSubMenu)
        : QTabBar(parent), _isSubMenu(isSubMenu)
    {
        QFont font;
        font.setFamilies(Comm::fontFmailies);
        font.setPointSize(9);
        setFont(font);
        setMouseTracking(true);
    }

    void SideBar::paintEvent(QPaintEvent*)
    {
        QPainter painter(this);
        QStyleOptionTab opt;

        for (int i = 0; i < count(); ++i)
        {
            initStyleOption(&opt, i);
            QRect rect = tabRect(i);
            bool selected = i == currentIndex();
            bool hovered = tabAt(mapFromGlobal(QCursor::pos())) == i;

            // 绘制背景
            if (hovered || selected)
                painter.fillRect(rect, Color::primaryL5());

            // 绘制边框
            if (!_isSubMenu)
            {
                painter.setPen(Color::baseBorder()) ;
                painter.drawLine(rect.right(), rect.top(), rect.right(), rect.bottom());
            }

            const MenuItem& menuItem = static_cast<TabWidget*>(parent())->menus()[i];

            // 绘制图标
            if (!_isSubMenu)
            {
                if (menuItem.iconName != Icon::None)
                {
                    QIcon icon = Icon::instance().getIcon(menuItem.iconName,
                                                                 selected ? Color::primary() : Color::primaryText(), 20);
                    icon.paint(&painter, rect.adjusted(30, 0, 0, 0), Qt::AlignLeft | Qt::AlignVCenter, QIcon::Normal);
                }
            }

            // 绘制文本
            painter.setPen(selected ? Color::primary() : Color::primaryText());
            painter.drawText(rect.adjusted(_isSubMenu ? 30 : menuItem.iconName == Icon::None ? 60 : 70, 0, -20, 0), Qt::AlignLeft | Qt::AlignVCenter, opt.text);
        }
    }

    void SideBar::mousePressEvent(QMouseEvent* event)
    {
        QTabBar::mousePressEvent(event);
    }

    TabWidget::TabWidget(QWidget* parent)
        : QTabWidget(parent)
    {
        setTabBar(new SideBar(this));
        setTabPosition(QTabWidget::West);
        setMovable(false);
        setDocumentMode(true);

        _qsshelper.setProperty("QTabWidget:pane", "border", "none");
        _qsshelper.setProperty("QTabBar:tab", "padding", "10px 20px");
        _qsshelper.setProperty("QTabBar:tab", "width", "130px");
        _qsshelper.setProperty("QTabBar:tab", "height", "50px");
        setStyleSheet(_qsshelper.generate());

        connect(this, &QTabWidget::currentChanged, this, &TabWidget::handleTabClicked);
    }


    QAction* TabWidget::addSubMenu(QAction* parentMenu, const QString& text)
    {
        QAction* action = new QAction(text, this);
        action->setCheckable(true);

        auto it = std::find_if(_menus.begin(), _menus.end(), [parentMenu](const MenuItem& item) {
            return item.action == parentMenu;
        });

        if (it != _menus.end() && it->hasSubMenu)
        {
            it->subActions.push_back(action);
            it->subMenuBar->addTab(action->text());
        }

        return action;
    }

    TabWidget& TabWidget::setTabIcon(int index, Icon::Name icon)
    {
        if (index < 0 || index >= _menus.size())
            return *this;

        _menus[index].iconName = icon;
        return *this;
    }

    void TabWidget::showSubMenu(int index)
    {
        hideSubMenu();

        if (index < 0 || index >= _menus.size())
            return;

        MenuItem& item = _menus[index];

        if (!item.hasSubMenu || !item.subMenuBar)
            return;

        // 计算子菜单位置
        QRect tabRect = tabBar()->tabRect(index);
        QPoint pos = tabBar()->mapTo(this->parentWidget(), QPoint(tabRect.right(), tabRect.top()));

        item.subMenuBar->move(pos);
        item.subMenuBar->show();

        _currentSubMenuBar = item.subMenuBar;
        _currentSubMenuIndex = index;

        // 同步选中状态
        if (_checkedAction)
        {
            for (int i = 0; i < item.subActions.size(); ++i)
            {
                if (item.subActions[i] == _checkedAction)
                {
                    item.subMenuBar->setCurrentIndex(i);
                    break;
                }
            }
        }
    }

    void TabWidget::hideSubMenu()
    {
        if (_currentSubMenuBar)
        {
            _currentSubMenuBar->hide();
            _currentSubMenuBar = nullptr;
            _currentSubMenuIndex = -1;
        }
    }

    void TabWidget::handleTabClicked(int index)
    {
        if (index < 0 || index >= _menus.size())
            return;

        MenuItem& item = _menus[index];
        if (item.hasSubMenu)
        {
            if (_currentSubMenuIndex == index)
            {
                hideSubMenu();
            }
            else
            {
                showSubMenu(index);
            }
        }
        else
        {
            hideSubMenu();
            if (_checkedAction)
                _checkedAction->setChecked(false);
            _checkedAction = item.action;
            item.action->setChecked(true);
            emit actionTriggered(item.action);
        }
    }

    void TabWidget::handleSubActionTriggered(QAction* action)
    {
        if (_checkedAction)
            _checkedAction->setChecked(false);
        _checkedAction = action;
        action->setChecked(true);
        emit actionTriggered(action);

        // 同步子菜单选中状态
        if (_currentSubMenuBar)
        {
            MenuItem& item = _menus[_currentSubMenuIndex];
            for (int i = 0; i < item.subActions.size(); ++i)
            {
                if (item.subActions[i] == action)
                {
                    _currentSubMenuBar->setCurrentIndex(i);
                    break;
                }
            }
        }
    }

    QVector<MenuItem>& TabWidget::menus()
    {
        return _menus;
    }

    QAction* TabWidget::checkedAction()
    {
        return _checkedAction;
    }

    int TabWidget::addTab(QWidget* page, const QString& text)
    {
        int index = QTabWidget::addTab(page, text);
        QAction* action = new QAction(text, this);
        action->setCheckable(true);

        MenuItem item(action, page, false);
        _menus.push_back(item);

        return index;
    }

}
