#pragma once

#include <QLayout>
#include <QResizeEvent>
#include <QStyle>

namespace Element
{

    class FlowLayout : public QLayout
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
        FlowLayout(QWidget* parent = nullptr);
        FlowLayout(SpaceSize size, QWidget* parent = nullptr);

    public:
        void setSpacing(SpaceSize size);
        void addItem(QLayoutItem *item) override;
        bool hasHeightForWidth() const override;
        int heightForWidth(int) const override;
        int count() const override;
        QLayoutItem *itemAt(int index) const override;
        QSize minimumSize() const override;
        void setGeometry(const QRect &rect) override;
        QSize sizeHint() const override;
        QLayoutItem *takeAt(int index) override;

    private:
        int doLayout(const QRect &rect, bool testOnly) const;

        QList<QLayoutItem *> itemList;
        int spacing;
    };

    class FluidLayout : public QLayout
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
        FluidLayout(QWidget* parent = nullptr);
        FluidLayout(SpaceSize size, QWidget* parent = nullptr);

    public:
        void setSpacing(SpaceSize size);
        void addItem(QLayoutItem *item) override;
        bool hasHeightForWidth() const override;
        int heightForWidth(int) const override;
        int count() const override;
        QLayoutItem *itemAt(int index) const override;
        QSize minimumSize() const override;
        void setGeometry(const QRect &rect) override;
        QSize sizeHint() const override;
        QLayoutItem *takeAt(int index) override;

    private:
        int doLayout(const QRect &rect, bool testOnly) const;

    private:
        QList<QLayoutItem *> itemList;
        int spacing;
    };

    class Layout : public QBoxLayout
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

        template<typename LayoutType>
        void addWidgets(QList<QWidget*> widgets)
        {
            if constexpr (std::is_same_v<LayoutType, FlowLayout>)
            {
                FlowLayout* layout = new FlowLayout(static_cast<FlowLayout::SpaceSize>(_size));
                foreach (QWidget* widget, widgets)
                    layout->addWidget(widget);
                QBoxLayout::insertLayout(count() - 1, layout);
            }
            else if constexpr (std::is_same_v<LayoutType, FluidLayout>)
            {
                FluidLayout* layout = new FluidLayout(static_cast<FluidLayout::SpaceSize>(_size));
                foreach (QWidget* widget, widgets)
                    layout->addWidget(widget);
                QBoxLayout::insertLayout(count() - 1, layout);
            }
        }

    public:
        Layout(QWidget* parent = nullptr);
        Layout(SpaceSize size, QWidget* parent = nullptr);

    private:
        SpaceSize _size;
    };

}