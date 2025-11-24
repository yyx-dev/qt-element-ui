#include "layout.h"
#include "base.h"

namespace Element
{
    Layout::Layout(QWidget* parent)
        : Layout(parent, SpaceSize::Default)
    {}

    Layout::Layout(QWidget* parent, SpaceSize size)
        : QVBoxLayout(parent)
    {
        setContentsMargins(0, 0, 0, 0);
        setSpacing(size);
        addStretch();
    }

    void Layout::setSpacing(SpaceSize size)
    {
        QVBoxLayout::setSpacing(size == SpaceSize::None ? 0
                             : size == SpaceSize::Small ? sc(8)
                           : size == SpaceSize::Default ? sc(12) : sc(16));
    }


    void Layout::addWidget(QWidget* widget)
    {
        QVBoxLayout::insertWidget(count() - 1, widget);
    }
}