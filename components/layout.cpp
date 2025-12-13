#include "layout.h"
#include "base.h"
#include <QTimer>

namespace Element
{
    Layout::Layout(QWidget* parent)
        : Layout(SpaceSize::Default, parent)
    {}

    Layout::Layout(SpaceSize size, QWidget* parent)
        : QBoxLayout(TopToBottom, parent)
    {
        setContentsMargins(0, 0, 0, 0);
        setSpacing(size);
        addStretch();
    }

    void Layout::setSpacing(SpaceSize size)
    {
        _size = size;
        QBoxLayout::setSpacing(size == SpaceSize::None ? 0
                            : size == SpaceSize::Small ? sc(8)
                          : size == SpaceSize::Default ? sc(12) : sc(16));
    }

    void Layout::addWidget(QWidget* widget)
    {
        QBoxLayout::insertWidget(count() - 1, widget);
    }

    void Layout::addWidgets(QList<QWidget*> widgets)
    {
        FlowLayout* layout = new FlowLayout(static_cast<FlowLayout::SpaceSize>(_size));
        foreach (QWidget* widget, widgets)
            layout->addWidget(widget);
        QBoxLayout::insertLayout(count() - 1, layout);
    }


    FlowLayout::FlowLayout(QWidget* parent)
        : FlowLayout(SpaceSize::Default, parent)
    {}

    FlowLayout::FlowLayout(SpaceSize size, QWidget* parent)
        : QLayout(parent)
    {
        setSpacing(size);
    }

    void FlowLayout::setSpacing(SpaceSize size)
    {
        spacing = size == SpaceSize::None ? 0
               : size == SpaceSize::Small ? sc(8)
             : size == SpaceSize::Default ? sc(12) : sc(16);
    }

    void FlowLayout::addItem(QLayoutItem *item)
    {
        itemList.append(item);
    }

    int FlowLayout::count() const
    {
        return itemList.size();
    }

    QLayoutItem *FlowLayout::itemAt(int index) const
    {
        return itemList.value(index);
    }

    QLayoutItem *FlowLayout::takeAt(int index)
    {
        if (index >= 0 && index < itemList.size())
            return itemList.takeAt(index);
        return nullptr;
    }

    bool FlowLayout::hasHeightForWidth() const
    {
        return true;
    }

    int FlowLayout::heightForWidth(int width) const
    {
        int height = doLayout(QRect(0, 0, width, 0), true);
        return height;
    }

    void FlowLayout::setGeometry(const QRect &rect)
    {
        QLayout::setGeometry(rect);
        doLayout(rect, false);
    }

    QSize FlowLayout::sizeHint() const
    {
        return minimumSize();
    }

    QSize FlowLayout::minimumSize() const
    {
        QSize size;
        for (const QLayoutItem *item : qAsConst(itemList))
            size = size.expandedTo(item->minimumSize());

        const QMargins margins = contentsMargins();
        size += QSize(margins.left() + margins.right(), margins.top() + margins.bottom());
        return size;
    }

    int FlowLayout::doLayout(const QRect &rect, bool testOnly) const
    {
        int left, top, right, bottom;
        getContentsMargins(&left, &top, &right, &bottom);

        QRect effectiveRect = rect.adjusted(+left, +top, -right, -bottom);
        int x = effectiveRect.x();
        int y = effectiveRect.y();
        int lineHeight = 0;

        for (QLayoutItem* item : qAsConst(itemList))
        {
            int nextX = x + item->sizeHint().width() + spacing;
            if (nextX - spacing > effectiveRect.right() && lineHeight > 0)
            {
                x = effectiveRect.x();
                y = y + lineHeight + spacing;
                nextX = x + item->sizeHint().width() + spacing;
                lineHeight = 0;
            }

            if (!testOnly)
                item->setGeometry(QRect(QPoint(x, y), item->sizeHint()));

            x = nextX;
            lineHeight = qMax(lineHeight, item->sizeHint().height());
        }
        return y + lineHeight - rect.y() + bottom;
    }


    FluidLayout::FluidLayout(QWidget* parent)
        : FluidLayout(SpaceSize::Default, parent)
    {}

    FluidLayout::FluidLayout(SpaceSize size, QWidget* parent)
        : QLayout(parent)
    {
        setSpacing(size);
    }

    void FluidLayout::setSpacing(SpaceSize size)
    {
        spacing = size == SpaceSize::None ? 0
               : size == SpaceSize::Small ? sc(8)
             : size == SpaceSize::Default ? sc(12) : sc(16);
    }

    void FluidLayout::addItem(QLayoutItem *item)
    {
        itemList.append(item);
    }

    int FluidLayout::count() const
    {
        return itemList.size();
    }

    QLayoutItem *FluidLayout::itemAt(int index) const
    {
        return itemList.value(index);
    }

    QLayoutItem *FluidLayout::takeAt(int index)
    {
        if (index >= 0 && index < itemList.size())
            return itemList.takeAt(index);
        return nullptr;
    }

    bool FluidLayout::hasHeightForWidth() const
    {
        return true;
    }

    int FluidLayout::heightForWidth(int width) const
    {
        int height = doLayout(QRect(0, 0, width, 0), true);
        return height;
    }

    void FluidLayout::setGeometry(const QRect &rect)
    {
        QLayout::setGeometry(rect);
        doLayout(rect, false);
    }

    QSize FluidLayout::sizeHint() const
    {
        return minimumSize();
    }

    QSize FluidLayout::minimumSize() const
    {
        QSize size;
        for (const QLayoutItem *item : qAsConst(itemList))
            size = size.expandedTo(item->minimumSize());

        const QMargins margins = contentsMargins();
        size += QSize(margins.left() + margins.right(), margins.top() + margins.bottom());
        return size;
    }

    int FluidLayout::doLayout(const QRect &rect, bool testOnly) const
    {
        auto calcProportionalHeight = [&] (int width) -> int {
            if (itemList.isEmpty())
                return 0;

            QSize maxSize = itemList.first()->maximumSize();
            return width * maxSize.height() / maxSize.width();
        };

        int left, top, right, bottom;
        getContentsMargins(&left, &top, &right, &bottom);

        QRect effectiveRect = rect.adjusted(+left, +top, -right, -bottom);
        int x = effectiveRect.x();
        int y = effectiveRect.y();
        int availableWidth = effectiveRect.width();


        int itemMaxWidth = itemList.at(0)->maximumSize().width();
        if (itemMaxWidth <= 0) itemMaxWidth = itemList.at(0)->sizeHint().width();

        int columns = 1;
        if (availableWidth > itemMaxWidth)
        {
            int tmp = availableWidth;
            while (tmp > itemMaxWidth)
            {
                tmp -= (itemMaxWidth + spacing);
                if (tmp >= 0)
                    columns++;
            }
        }

        int totalSpacingH = (columns - 1) * spacing;
        int itemWidth = (availableWidth - totalSpacingH) / columns;

        int rowHeight = 0;
        int colIndex = 0;

        for (QLayoutItem* item : qAsConst(itemList))
        {
            int itemHeight = calcProportionalHeight(itemWidth);

            if (!testOnly)
            {
                int nextX = x + colIndex * (itemWidth + spacing);
                item->setGeometry(QRect(QPoint(nextX, y), QSize(itemWidth, itemHeight)));
            }

            rowHeight = qMax(rowHeight, itemHeight);
            colIndex++;

            if (colIndex >= columns)
            {
                y += rowHeight + spacing;
                rowHeight = 0;
                colIndex = 0;
            }
        }

        return y + rowHeight - rect.y() + bottom;
    }

}
