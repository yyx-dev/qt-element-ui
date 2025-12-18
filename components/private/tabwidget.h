#pragma once

#include "private/utils.h"
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
        SideBar(QWidget* parent = nullptr);
    protected:
        void paintEvent(QPaintEvent* event) override;
        void mousePressEvent(QMouseEvent* event) override;
    };

    struct MenuItem
    {
        QAction* action;
        QWidget* page;
        Icon::Name icon = Icon::None;
        MenuItem(QAction* a, QWidget* p, Icon::Name icon = Icon::None)
            : action(a), page(p), icon(icon)
        {}
    };

    class TabWidget : public QTabWidget
    {
        Q_OBJECT
    public:
        TabWidget(QWidget* parent = nullptr);

    public:
        int addTab(QWidget* page, const QString& text);
        TabWidget& setTabIcon(int index, Icon::Name icon);

        QVector<MenuItem>& menus();
        QAction* checkedAction();

    signals:
        void actionTriggered(QAction* action);

    public slots:
        void handleTabClicked(int index);

    private:
        QVector<MenuItem> _menus;
        QAction* _checkedAction = nullptr;
        QSSHelper _qsshelper;
    };
}
