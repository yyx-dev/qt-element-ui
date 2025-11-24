#pragma once

#include <QBoxLayout>

namespace Element
{
    class Layout : public QVBoxLayout
    {
    public:
        enum class SpaceSize
        {
            None,
            Default,
            Small,
            Large,
        };

    public:
        void setSpacing(SpaceSize size);
        void addWidget(QWidget* widget);

    public:
        Layout(QWidget* parent);
        Layout(QWidget* parent, SpaceSize size);

    };
}