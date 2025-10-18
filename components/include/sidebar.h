#pragma once

#include "base.h"
#include "icon.h"

#include <QTabWidget>
#include <QTabBar>
#include <QAction>

namespace Element
{
    class SideBar : public QTabBar
    {
        Q_OBJECT
    public:
        SideBar(QWidget* parent = nullptr, bool isSubMenu = false);
    protected:
        void paintEvent(QPaintEvent* event) override;
        void mousePressEvent(QMouseEvent* event) override;
    private:
        bool _isSubMenu; // 标记是否为子菜单
    };

    struct MenuItem
    {
        QAction* action;
        QWidget* page;
        bool hasSubMenu;
        Icon::Name iconName = Icon::None;

        QVector<QAction*> subActions;
        SideBar* subMenuBar;
        MenuItem(QAction* a, QWidget* p, bool sub, Icon::Name icon = Icon::None)
            : action(a), page(p), hasSubMenu(sub), iconName(icon), subMenuBar(nullptr)
        {}
    };

    class TabWidget : public QTabWidget
    {
        Q_OBJECT
    public:
        TabWidget(QWidget* parent = nullptr);
    public:
        QAction* addTopMenu(const QString& text, Icon::Name icon = Icon::None, bool hasSub = false);
        QAction* addSubMenu(QAction* parentMenu, const QString& text);
        TabWidget& setTabIcon(int index, Icon::Name icon);

        QVector<MenuItem>& menus();
        QAction* checkedAction();

        void showSubMenu(int index);
        void hideSubMenu();

        int addTab(QWidget* page, const QString& text);

    signals:
        void actionTriggered(QAction* action);

    public slots:
        void handleTabClicked(int index);
        void handleSubActionTriggered(QAction* action);

    private:
        QVector<MenuItem> _menus;
        QAction* _checkedAction = nullptr;
        QSSHelper _qsshelper;
        SideBar* _currentSubMenuBar = nullptr;
        int _currentSubMenuIndex = -1;
    };
}
