#pragma once

#include "qlist.h"
#include <QTabBar>
#include <QTabWidget>

namespace Element
{
    class TabBar;

    class Tabs : public QTabWidget
    {
        Q_OBJECT

    public:
        enum class Type
        {
            Default,
            Card,
            BorderCard,
        };

        enum class TabPosition
        {
            Top,
            Bottom,
            Left,
            Right,
        };

    public:
        Tabs& setType(Type type);
        Tabs& setTabPosition(TabPosition position);
        Tabs& setCloseable(bool closable);
        Tabs& setAddable(bool addable);
        Tabs& setEditable(bool editable);
        Tabs& setStretch(bool stretch);

    public:
        QHash<int, int>& getTabWidths();

    public:
        Tabs(QWidget* parent = nullptr);
        Tabs(Type type, QWidget* parent = nullptr);
        Tabs(TabPosition position, QWidget* parent = nullptr);
        Tabs(Type type, TabPosition position, QWidget* parent = nullptr);

    protected:
        void paintEvent(QPaintEvent* event) override;

    private:
        void paintDefaultStyle();
        void paintCardStyle();
        void paintBorderCardStyle();

    private:
        Type _type = Type::Default;
        TabPosition _position = TabPosition::Top;

        bool _closable = false;
        bool _addable = false;
        bool _editable = false;
        bool _stretch = false;

    private:
        TabBar* _bar = nullptr;
        QHash<int, int> _tabWidths;
    };

    class TabBar : public QTabBar
    {
        Q_OBJECT

    public:
        void setType(Tabs::Type type);
        void setTabPosition(Tabs::TabPosition pos);

    public:
        TabBar(Tabs::Type type, Tabs::TabPosition pos, Tabs* tabs, QWidget* parent = nullptr);

    protected:
        void paintEvent(QPaintEvent* event) override;
        QSize tabSizeHint(int index) const override;

    private:
        void paintDefaultStyle();
        void paintCardStyle();
        void paintBorderCardStyle();
        void drawTextDefaultStyle();
        void drawTextCardStyle();

    private:
        Tabs::Type _type;
        Tabs::TabPosition _position;

    private:
        Tabs* _tabs = nullptr;
    };
}
