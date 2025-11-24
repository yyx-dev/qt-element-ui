#pragma once

#include "icon.h"
#include "base.h"

#include <QWidget>
#include <QLabel>
#include <QBoxLayout>

namespace Element
{

    class CollapseItem : public QWidget
    {
    Q_OBJECT

    public:
        enum class IconPosition { Left, Right };
        enum class Status { Collapse, Expand };

    public:
        CollapseItem& setIconPosition(IconPosition position);
        CollapseItem& setAllowCollapse(bool allow);
        CollapseItem& setCollapse();
        CollapseItem& setExpand();
        CollapseItem& toggleStatus();

        CollapseItem& setTitle(const QString& title);
        CollapseItem& setContent(const QString& content);
        CollapseItem& setIcon(Icon::Name collapsedIcon, Icon::Name expandIcon);
        CollapseItem& setDisabled(bool disabled);

        CollapseItem& setWidth(int width);
        CollapseItem& setLast(bool isLast);

    public:
        CollapseItem(QWidget* parent = nullptr);
        CollapseItem(const QString& title, const QString& content, QWidget* parent = nullptr);
        CollapseItem(const QString& title, const QString& content, Status status = Status::Collapse, QWidget* parent = nullptr);

    protected:
        void paintEvent(QPaintEvent* event) override;
        void mousePressEvent(QMouseEvent* event) override;
        void mouseMoveEvent(QMouseEvent* event) override;

    private:
        IconPosition _iconPosition = IconPosition::Right;
        Status _status = Status::Collapse;
        Icon::Name _collapsedIcon = Icon::ArrowRight;
        Icon::Name _expandIcon = Icon::ArrowDown;
        bool _allowCollapse = true;

    private:
        QLabel* _title = nullptr;
        QLabel* _content = nullptr;
        QLabel* _icon = nullptr;
        QHBoxLayout* _titleLayout = nullptr;
        QVBoxLayout* _mainlayout = nullptr;

    private:
        bool _last = false;
    };

    class Collapse : public QWidget
    {
    Q_OBJECT

    public:
        using Item = CollapseItem;

    public:
        Collapse& setAccordion(bool accordion);
        Collapse& setIcon(Icon::Name collapsedIcon, Icon::Name expandIcon);
        Collapse& setCollapse(int index);
        Collapse& setExpand(int index);
        Collapse& setIconPosition(Item::IconPosition position);
        Collapse& toggleStatus(int index);

        Collapse& addItem(CollapseItem* item);
        Collapse& delItem(int index);

        Collapse& setWidth(int width);

    public:
        Collapse(QWidget* parent = nullptr);

    private:
        bool _accordion = false;

    private:
        QList<CollapseItem*> _items;
    };

}
