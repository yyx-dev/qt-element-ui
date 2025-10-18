#pragma once

#include "base.h"

#include <QTableWidget>
#include <QHeaderView>


namespace Element
{
    class Table : public QTableWidget
    {
    Q_OBJECT

    public:
        enum class Highlight
        {
            Primary,
            Success,
            Info,
            Warning,
            Danger,
        };

    public:
        Table& setWidth(const QList<int>& widths = QList<int>());
        Table& setStripe(bool stripe);
        Table& setBorder(bool border);
        Table& setHightlight(int row, Highlight type);

//        Table& setHeight(int height);
//        Table& setMaxHeight(int maxHeight);


    public:
       Table(QWidget* parent = nullptr);
       Table(const QStringList& headers, QWidget* parent = nullptr);
       Table(const QStringList& headers, const QList<int>& widths, QWidget* parent = nullptr);
       Table(const QStringList& headers, const QList<QStringList>& content, QWidget* parent = nullptr);

    protected:
        bool eventFilter(QObject* watched, QEvent* event) override;
        void paintEvent(QPaintEvent* event) override;

    private:
        void highlightRow(int row);
        void clearHighlight();

        int _currentHoverRow = -1;

    private:
       QSSHelper _qsshelper;
    };

//    class CustomHeaderView : public QHeaderView
//    {
//    public:
//        CustomHeaderView(Qt::Orientation orientation, QWidget* parent = nullptr);
//    protected:
//        void paintSection(QPainter* painter, const QRect& rect, int logicalIndex) const override;
//    };
}
