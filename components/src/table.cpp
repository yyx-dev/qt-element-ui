#include "table.h"

#include "base.h"
#include "color.h"

#include <QHeaderView>
#include <QEvent>

#include <QMouseEvent>
#include <QPainter>
#include <QItemSelectionModel>

namespace Element
{

    Table::Table(QWidget* parent)
        : Table(QStringList(), QList<QStringList>(), parent)
    {}

    Table::Table(const QStringList& headers, QWidget* parent)
        : Table(headers, QList<QStringList>(), parent)
    {}

    Table::Table(const QStringList& headers, const QList<int>& widths, QWidget* parent)
        : Table(headers, QList<QStringList>(), parent)
    {
        for (int i = 0; i < widths.size(); i++)
            setColumnWidth(i, widths.at(i));
    }

    Table::Table(const QStringList& headers, const QList<QStringList>& content, QWidget* parent)
        : QTableWidget(parent)
    {
        int cols = headers.size();
        int rows = content.size();

        if (cols != 0)
        {
            setColumnCount(cols);
            setHorizontalHeaderLabels(headers);
        }

        if (rows != 0)
        {
            setRowCount(rows);
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    setItem(i, j, new QTableWidgetItem(content[i][j]));
                }
            }
        }

//        setHorizontalHeader(new CustomHeaderView(Qt::Horizontal, this));

        verticalHeader()->setVisible(false);
        verticalHeader()->setDefaultSectionSize(50);
        horizontalHeader()->setFixedHeight(50);
        horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);

        setShowGrid(false);

        _qsshelper.setProperty("QTableWidget", "border", "none")
                  .setProperty("QTableWidget", "background-color", "white")
                  .setProperty("QTableWidget", "alternate-background-color", "white")
                  .setProperty("QTableWidget", "selection-background-color", Color::lightFill())
                  .setProperty("QTableWidget", "selection-color", Color::regularText())
                  .setProperty("QTableWidget", "outline", "none")
                  .setProperty("QTableWidget", "gridline-color", "transparent");
        _qsshelper.setProperty("QHeaderView::section", "background-color", "white")
                  .setProperty("QHeaderView::section", "color", Color::secondaryText())
                  .setProperty("QHeaderView::section", "padding", "0px 12px")
                  .setProperty("QHeaderView::section", "border", "none")
                  .setProperty("QHeaderView::section", "border-bottom", "1px solid " + Color::lighterBorder());
        _qsshelper.setProperty("QTableWidget::item", "color", Color::regularText())
                  .setProperty("QTableWidget::item", "padding", "0px 12px")
                  .setProperty("QTableWidget::item", "border", "none")
                  .setProperty("QTableWidget::item", "border-bottom", "1px solid " + Color::lighterBorder())
                  .setProperty("QTableWidget::item:hover", "background-color", Color::lightFill())
                  .setProperty("QTableWidget::item:alternate", "background-color", Color::lighterFill());
        setStyleSheet(_qsshelper.generate());

        setSelectionBehavior(QAbstractItemView::SelectRows);
        setSelectionMode(QAbstractItemView::SingleSelection);

        QFont font = horizontalHeader()->font();
        font.setFamilies(Comm::fontFmailies);
        font.setBold(true);
        font.setPointSize(9);
        horizontalHeader()->setFont(font);

        font = QTableWidget::font();
        font.setFamilies(Comm::fontFmailies);
        font.setPointSize(Comm::defaultFontSize);
        setFont(font);

        viewport()->installEventFilter(this);
    }

    Table& Table::setWidth(const QList<int>& widths)
    {
        int cols = columnCount();

        for (int j = 0; j < cols - 1; ++j) {
            horizontalHeader()->setSectionResizeMode(j, QHeaderView::ResizeToContents);
        }

        if (cols > 0) {
            horizontalHeader()->setSectionResizeMode(cols - 1, QHeaderView::Stretch);
        }

        if (!widths.isEmpty()) {
            for (int j = 0; j < widths.size() && j < cols; j++) {
                horizontalHeader()->setSectionResizeMode(j, QHeaderView::Interactive);
                setColumnWidth(j, widths.at(j));
            }
        }

        return *this;
    }

    Table& Table::setStripe(bool stripe)
    {
        setAlternatingRowColors(stripe);
        return *this;
    }

    Table& Table::setBorder(bool )
    {

        return *this;
    }

    Table& Table::setHightlight(int row, Highlight type)
    {
        if (row < 0 || row > rowCount())
            return *this;

        static auto getHightlightColor = [&]() -> QString {
            switch (type) {
            case Highlight::Primary: return Color::primaryL5();
            case Highlight::Success: return Color::successL5();
            case Highlight::Info:    return Color::infoL5();
            case Highlight::Warning: return Color::warningL5();
            case Highlight::Danger:  return Color::dangerL5();
            }
            return "#000000";
        };

        for (int col = 0; col < columnCount(); ++col)
            item(row, col)->setData(Qt::BackgroundRole, QColor(getHightlightColor()));
        return *this;
    }

    bool Table::eventFilter(QObject* watched, QEvent* event)
    {
        if (watched == viewport() && event->type() == QEvent::HoverMove)
        {
            QTableWidgetItem* item = itemAt(static_cast<QMouseEvent*>(event)->pos());
            int newHoverRow = item ? item->row() : -1;

            if (newHoverRow != _currentHoverRow)
            {
                clearHighlight();

                if (newHoverRow != -1)
                    highlightRow(newHoverRow);

                _currentHoverRow = newHoverRow;
            }
        }
        else if (watched == viewport() && event->type() == QEvent::Leave)
        {
            clearHighlight();
            _currentHoverRow = -1;
        }

        return QTableWidget::eventFilter(watched, event);
    }

    void Table::paintEvent(QPaintEvent* event)
    {

        QTableWidget::paintEvent(event);
    }

    void Table::highlightRow(int row)
    {
        for (int col = 0; col < columnCount(); ++col) {
            item(row, col)->setData(Qt::BackgroundRole, QColor(Color::lightFill()));
        }
    }

    void Table::clearHighlight()
    {
        if (_currentHoverRow == -1)
            return;
        for (int col = 0; col < columnCount(); ++col) {
            item(_currentHoverRow, col)->setData(Qt::BackgroundRole, QVariant());
        }

    }

//    CustomHeaderView::CustomHeaderView(Qt::Orientation orientation, QWidget* parent)
//        : QHeaderView(orientation, parent)
//    {}

//    void CustomHeaderView::paintSection(QPainter* painter, const QRect& rect, int logicalIndex) const
//    {
//        QStyleOptionHeader opt;
//        initStyleOption(&opt);
//        opt.rect = rect;
//        opt.section = logicalIndex;
//        opt.textAlignment = Qt::AlignLeft | Qt::AlignVCenter;
//        opt.text = model()->headerData(logicalIndex, orientation(), Qt::DisplayRole).toString();

//        // 设置背景色为白色
//        painter->save();
//        painter->fillRect(rect, QColor(255, 255, 255));

//        // 绘制下边框 (1px 实线)
//        painter->setPen(QPen(QColor(220, 220, 220), 1));
//        painter->drawLine(rect.bottomLeft(), rect.bottomRight());

//        // 绘制文本 (次要文本颜色，padding: 0px 12px)
//        QFont font = painter->font();
//        painter->setPen(QColor(100, 100, 100)); // secondaryText
//        QRect textRect = rect.adjusted(12, 0, -12, 0); // 左右 padding 12px
//        painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, opt.text);

//        painter->restore();
//    }


}
