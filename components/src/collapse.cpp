#include "collapse.h"

#include "icon.h"
#include "color.h"
#include "base.h"

#include <QPainter>
#include <QMouseEvent>


namespace Element
{
    CollapseItem::CollapseItem(QWidget* parent)
        : CollapseItem("", "", Status::Collapse, parent)
    {}

    CollapseItem::CollapseItem(const QString& title, const QString& content, QWidget* parent)
        : CollapseItem(title, content, Status::Collapse, parent)
    {}

    CollapseItem::CollapseItem(const QString& title, const QString& content, Status status, QWidget* parent)
        : QWidget(parent)
        , _status(status)
        , _title(new QLabel(title, this))
        , _content(new QLabel(content, this))
        , _icon(new QLabel(this))
    {
        QFont font = _title->font();
        font.setPointSize(9);
        font.setFamilies(Comm::fontFmailies);
        font.setBold(true);
        _title->setFont(font);

        font = _content->font();
        font.setPointSize(9);
        font.setFamilies(Comm::fontFmailies);
        _content->setFont(font);

        _title->setFixedHeight(60);
        _icon->setFixedHeight(60);

        _content->setWordWrap(true);
        _icon->setPixmap(Icon::instance().getPixmap(_collapsedIcon, Color::primaryText(), 12));

        _title->setStyleSheet("color: " + Color::primaryText() + "; ");
        _content->setStyleSheet("color: " + Color::primaryText() + "; ");

        _titleLayout = new QHBoxLayout;
        _titleLayout->setContentsMargins(0, 0, 0, 0);
        _titleLayout->setSpacing(0);
        _titleLayout->addWidget(_title);
        _titleLayout->addStretch();
        _titleLayout->addWidget(_icon);
        _titleLayout->addSpacing(10);

        _mainlayout = new QVBoxLayout(this);
        _mainlayout->setContentsMargins(0, 0, 0, 0);
        _mainlayout->setSpacing(0);
        _mainlayout->addLayout(_titleLayout);
        _mainlayout->addWidget(_content);

        setMouseTracking(true);
        _title->setMouseTracking(true);
        _icon->setMouseTracking(true);
        _content->setMouseTracking(true);

        if (_status == Status::Collapse)
            setCollapse();
        else
            setExpand();

        setFixedWidth(800);
        adjustSize();
    }

    CollapseItem& CollapseItem::setIconPosition(IconPosition position)
    {
        _iconPosition = position;

        if (_titleLayout)
        {
            QLayoutItem* item;
            while ((item = _titleLayout->takeAt(0)) != nullptr)
                delete item;

            if (_iconPosition == IconPosition::Left)
            {
                _titleLayout->addWidget(_icon);
                _titleLayout->addSpacing(10);
                _titleLayout->addWidget(_title);
                _titleLayout->addStretch();
            }
            else
            {
                _titleLayout->addWidget(_title);
                _titleLayout->addStretch();
                _titleLayout->addWidget(_icon);
                _titleLayout->addSpacing(10);
            }
        }

        return *this;
    }

    CollapseItem& CollapseItem::setAllowCollapse(bool allow)
    {
        _allowCollapse = allow;
        return *this;
    }

    CollapseItem& CollapseItem::setCollapse()
    {
        _status = Status::Collapse;

        _content->hide();
        _icon->setPixmap(Icon::instance().getPixmap(_collapsedIcon, Color::primaryText(), 12));
        _mainlayout->setContentsMargins(0, 0, 0, 0);

        adjustSize();

        if (parentWidget())
            parentWidget()->adjustSize();

        return *this;
    }

    CollapseItem& CollapseItem::setExpand()
    {
        _status = Status::Expand;

        _content->show();
        _icon->setPixmap(Icon::instance().getPixmap(_expandIcon, Color::primaryText(), 12));
        _mainlayout->setContentsMargins(0, 0, 0, 20);

        adjustSize();

        if (parentWidget())
            parentWidget()->adjustSize();

        return *this;
    }

    CollapseItem& CollapseItem::toggleStatus()
    {
        if (_status == Status::Collapse)
            setExpand();
        else
            setCollapse();

        return *this;
    }

    CollapseItem& CollapseItem::setTitle(const QString& title)
    {
        _title->setText(title);
        return *this;
    }

    CollapseItem& CollapseItem::setContent(const QString& content)
    {
        _content->setText(content);
        return *this;
    }

    CollapseItem& CollapseItem::setIcon(Icon::Name collapsedIcon, Icon::Name expandIcon)
    {
        _collapsedIcon = collapsedIcon;
        _expandIcon = expandIcon;
        return *this;
    }

    CollapseItem& CollapseItem::setDisabled(bool disabled)
    {
        QWidget::setDisabled(disabled);
        return *this;
    }

    void CollapseItem::paintEvent(QPaintEvent *event)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QPen pen(Color::lighterBorder());
        pen.setWidth(1);
        painter.setPen(pen);

        painter.drawLine(QPointF(0, 0), QPointF(width(), 0));

        if (_last)
            painter.drawLine(QPointF(0, height()), QPointF(width(), height()));

        QWidget::paintEvent(event);
    }

    void CollapseItem::mousePressEvent(QMouseEvent* event)
    {
        if (!_allowCollapse || !isEnabled())
            return;

        if (_titleLayout && event->y() <= _titleLayout->geometry().height())
            toggleStatus();

        QWidget::mousePressEvent(event);
    }

    void CollapseItem::mouseMoveEvent(QMouseEvent* event)
    {
        if (!isEnabled())
            setCursor(Qt::ForbiddenCursor);
        else if (_titleLayout
              && _titleLayout->geometry().contains(event->pos())
              && _allowCollapse)
            setCursor(Qt::PointingHandCursor);
       else
            unsetCursor();

        QWidget::mouseMoveEvent(event);
    }

    CollapseItem& CollapseItem::setWidth(int width)
    {
        setFixedWidth(width);
        return *this;
    }

    CollapseItem& CollapseItem::setLast(bool isLast)
    {
        _last = isLast;
        return *this;
    }

    Collapse::Collapse(QWidget* parent)
        : QWidget(parent)
    {
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);
        setLayout(layout);

        setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    }

    Collapse& Collapse::setAccordion(bool accordion)
    {
        _accordion = accordion;
        return *this;
    }

    Collapse& Collapse::setIcon(Icon::Name collapsedIcon, Icon::Name expandIcon)
    {
        for (auto& item : _items)
            item->setIcon(collapsedIcon, expandIcon);
        return *this;
    }

    Collapse& Collapse::setCollapse(int index)
    {
        if (index >= 0 && index < _items.size())
            _items[index]->setCollapse();
        return *this;
    }

    Collapse& Collapse::setExpand(int index)
    {
        if (index >= 0 && index < _items.size())
            _items[index]->setExpand();
        return *this;
    }

    Collapse& Collapse::setIconPosition(Item::IconPosition position)
    {
        for (auto& item : _items)
            item->setIconPosition(position);
        return *this;
    }

    Collapse& Collapse::toggleStatus(int index)
    {
        if (index >= 0 && index < _items.size())
        {
            if (_accordion)
            {
                for (int i = 0; i < _items.size(); ++i)
                {
                    if (i == index)
                        _items[i]->toggleStatus();
                    else
                        _items[i]->setCollapse();
                }
            }
            else
            {
                _items[index]->toggleStatus();
            }

            adjustSize();
        }
        return *this;
    }

    Collapse& Collapse::addItem(CollapseItem* item)
    {
        if (!item)
            return *this;

        if (!_items.isEmpty())
            _items.back()->setLast(false);
        item->setLast(true);

        item->setParent(this);
        _items.append(item);
        layout()->addWidget(item);
        adjustSize();

        return *this;
    }

    Collapse& Collapse::delItem(int index)
    {
        if (index >= 0 && index < _items.size())
        {
            if (index == _items.size() - 1)
            {
                _items[index]->setLast(false);
                if (index != 0) _items[index - 1]->setLast(true);
            }

            layout()->removeWidget(_items[index]);
            _items[index]->deleteLater();
            _items.removeAt(index);
        }
        return *this;
    }

    Collapse& Collapse::setWidth(int width)
    {
        setFixedWidth(width);
        for (auto& item : _items)
            item->setWidth(width);
        return *this;
    }

}
