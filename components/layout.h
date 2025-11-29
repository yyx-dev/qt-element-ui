#pragma once

#include <QLayout>
#include <QResizeEvent>
#include <QStyle>

namespace Element
{
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
        void addWidgets(QList<QWidget*> widgets);

    public:
        Layout(QWidget* parent = nullptr);
        Layout(SpaceSize size, QWidget* parent = nullptr);

    private:
        SpaceSize _size;
    };

    class FlowLayout : public QLayout
    {
    public:
        explicit FlowLayout(QWidget *parent, int margin = -1, int hSpacing = -1, int vSpacing = -1);
        explicit FlowLayout(int margin = -1, int hSpacing = -1, int vSpacing = -1);
        ~FlowLayout();

        void addItem(QLayoutItem *item) override;
        int horizontalSpacing() const;
        int verticalSpacing() const;
        Qt::Orientations expandingDirections() const override;
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
        int smartSpacing(QStyle::PixelMetric pm) const;

        QList<QLayoutItem *> itemList;
        int m_hSpace;
        int m_vSpace;
    };
}