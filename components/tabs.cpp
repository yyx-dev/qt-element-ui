#include "color.h"
#include "private/utils.h"
#include "qcolor.h"
#include "qglobal.h"
#include "qline.h"
#include "qnamespace.h"
#include "qpaintdevice.h"
#include "qpainter.h"
#include "tabs.h"

#include <QStyleOptionTab>
#include <QStylePainter>

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#    include <QPainterPath>
#endif

namespace Element
{

    Tabs::Tabs(QWidget* parent)
        : Tabs(Type::Default, TabPosition::Top, parent)
    {
    }

    Tabs::Tabs(Type type, QWidget* parent)
        : Tabs(type, TabPosition::Top, parent)
    {
    }

    Tabs::Tabs(TabPosition position, QWidget* parent)
        : Tabs(Type::Default, position, parent)
    {
    }

    Tabs::Tabs(Type type, TabPosition position, QWidget* parent)
        : QTabWidget(parent)
        , _type(type)
        , _position(position)
        , _bar(new TabBar(type, position, this))
    {
        setType(_type);
        setTabPosition(_position);
        setTabBar(_bar);

        // setTabsClosable(_closable);
        // setMovable(_editable);
    }

    Tabs& Tabs::setType(Type type)
    {
        _type = type;
        _bar->setType(type);
        return *this;
    }

    Tabs& Tabs::setTabPosition(TabPosition pos)
    {
        _position = pos;
        QTabWidget::setTabPosition(
            pos == TabPosition::Top    ? QTabWidget::North :
            pos == TabPosition::Bottom ? QTabWidget::South :
            pos == TabPosition::Left   ? QTabWidget::West :
                                         QTabWidget::East);

        _bar->setTabPosition(pos);
        return *this;
    }

    Tabs& Tabs::setCloseable(bool closable)
    {
        _closable = closable;
        setTabsClosable(closable);
        return *this;
    }

    Tabs& Tabs::setAddable(bool addable)
    {
        _addable = addable;
        return *this;
    }

    Tabs& Tabs::setEditable(bool editable)
    {
        _editable = editable;
        setMovable(editable);
        return *this;
    }

    Tabs& Tabs::setStretch(bool stretch)
    {
        _stretch = stretch;
        _bar->setExpanding(_stretch);
        return *this;
    }

    QHash<int, int>& Tabs::getTabWidths()
    {
        return _tabWidths;
    }

    void Tabs::paintEvent(QPaintEvent*)
    {
        switch (_type)
        {
        case Type::Default: paintDefaultStyle(); break;
        case Type::Card: paintCardStyle(); break;
        case Type::BorderCard: paintBorderCardStyle(); break;
        }
    }

    void Tabs::paintDefaultStyle()
    {
        QStylePainter painter(this);

        // 绘制分割线
        QRect lineRect = _position == TabPosition::Top    ? QRect(0, _bar->height(), width(), 2) :
                         _position == TabPosition::Bottom ? QRect(0, height() - _bar->height() - 2, width(), 2) :
                         _position == TabPosition::Left   ? QRect(_bar->width(), 0, 2, height()) :
                                                            QRect(width() - _bar->width() - 2, 0, 2, height());
        painter.fillRect(lineRect, Color::lightBorder());

        // 绘制选中标签蓝色线段
        int cur = currentIndex();
        if (cur >= 0)
        {
            QRect tabR = _bar->tabRect(cur);
            QRect selLine = lineRect;

            if (_position == TabPosition::Top || _position == TabPosition::Bottom)
            {
                selLine.setLeft(tabR.left());
                selLine.setWidth(tabR.width() - 40);
            }
            else
            {
                selLine.setTop(tabR.top());
                selLine.setHeight(tabR.height());
            }

            painter.fillRect(selLine, Color::primary());
        }
    }

    void Tabs::paintCardStyle()
    {
        QStylePainter painter(this);

        if (_position == TabPosition::Top)
        {
            QRect lineRect = QRect(0, _bar->height() - 1, width(), 1);
            painter.fillRect(lineRect, Color::lightBorder());
        }
        else if (_position == TabPosition::Bottom)
        {
            QRect lineRect = QRect(0, height() - _bar->height() - 1, width(), 1);
            painter.fillRect(lineRect, Color::lightBorder());
        }
    }

    void Tabs::paintBorderCardStyle()
    {
        QStylePainter painter(this);

        painter.setBrush(Qt::NoBrush);
        painter.setPen(Color::baseBorder());
        painter.drawRect(rect().adjusted(0, 0, -1, -1));

        if (_position == TabPosition::Top)
        {
            QRect tabRect = QRect(1, 1, width() - 2, _bar->height() - 2);
            painter.fillRect(tabRect, Color::lightFill());
            QLine line = QLine(0, _bar->height() - 1, width(), _bar->height() - 1);
            painter.drawLine(line);
        }
        else if (_position == TabPosition::Bottom)
        {
            QLine line = QLine(0, height() - _bar->height() - 1, width(), height() - _bar->height() - 1);
            painter.drawLine(line);
        }
    }


    TabBar::TabBar(Tabs::Type type, Tabs::TabPosition pos, Tabs* tabs, QWidget* parent)
        : QTabBar(parent)
        , _tabs(tabs)
    {
        setType(type);
        setTabPosition(pos);
        setFont(FontHelper().setPointSize(10).getFont());
        setStyleSheet("QTabBar {background: transparent; border: none;}");

        setExpanding(false);
        setTabsClosable(false);
        setUsesScrollButtons(false);
    }

    void TabBar::setType(Tabs::Type type)
    {
        _type = type;
    }

    void TabBar::setTabPosition(Tabs::TabPosition pos)
    {
        _position = pos;
    }

    void TabBar::paintEvent(QPaintEvent*)
    {
        switch (_type)
        {
        case Tabs::Type::Default: paintDefaultStyle(); break;
        case Tabs::Type::Card:
            paintCardStyle();
            break;
        case Tabs::Type::BorderCard: paintBorderCardStyle(); break;
        }
    }

    QSize TabBar::tabSizeHint(int i) const
    {
        auto& tabWidths = _tabs->getTabWidths();

        if (!tabWidths.contains(i))
        {
            int textWidth = FontHelper(font()).getTextWidth(tabText(i));
            tabWidths[i] = qMax(50, textWidth + 2 * 20);
        }

        return QSize(tabWidths[i], 50);
    }

    void TabBar::paintDefaultStyle()
    {
        drawTextDefaultStyle();
    }

    void TabBar::paintCardStyle()
    {
        QStylePainter painter(this);

        for (int i = 0; i < count(); ++i)
        {
            QRect rect = tabRect(i);

            painter.setPen(QPen(QColor(Color::lightBorder()), 1));
            painter.setBrush(Qt::NoBrush);

            const int radius = 6;
            if (i == 0)
            {
                QPainterPath path;
                path.moveTo(rect.left() + radius, rect.top());
                path.lineTo(rect.right() + 1, rect.top());
                path.lineTo(rect.right() + 1, rect.bottom() + 1);
                path.lineTo(rect.left(), rect.bottom());
                path.arcTo(rect.left(), rect.top(), radius * 2, radius * 2, 180, -90);
                path.closeSubpath();
                painter.drawPath(path);
            }
            else if (i == count() - 1)
            {
                QPainterPath path;
                path.moveTo(rect.left(), rect.top());
                path.lineTo(rect.right() - radius, rect.top());
                path.arcTo(rect.right() - radius * 2, rect.top(), radius * 2, radius * 2, 90, -90);
                path.lineTo(rect.right(), rect.bottom());
                path.lineTo(rect.left(), rect.bottom());
                path.closeSubpath();
                painter.drawPath(path);
            }
            else
            {
                painter.drawLine(rect.topLeft(), rect.topRight());
                painter.drawLine(rect.topLeft(), rect.bottomLeft());
                painter.drawLine(rect.bottomLeft(), rect.bottomRight());
            }

            if (i == currentIndex())
            {
                painter.setPen(Color::blankFill());
                painter.drawLine(rect.bottomLeft(), rect.bottomRight());
            }
        }

        drawTextCardStyle();
    }

    void TabBar::paintBorderCardStyle()
    {
        QStylePainter painter(this);

        painter.setPen(QPen(QColor(Color::baseBorder()), 1));
        painter.setBrush(Qt::NoBrush);

        for (int i = 0; i < count(); ++i)
        {
            if (i == currentIndex())
            {
                QRect rect = tabRect(i);

                painter.fillRect(rect.adjusted(1, 1, -1, 0), QColor(Color::blankFill()));
                painter.drawLine(rect.topLeft(), rect.bottomLeft());
                painter.drawLine(rect.topRight(), rect.bottomRight());
            }
        }

        drawTextCardStyle();
    }

    void TabBar::drawTextDefaultStyle()
    {
        QStylePainter painter(this);

        for (int i = 0; i < count(); ++i)
        {
            QStyleOptionTab opt;
            initStyleOption(&opt, i);

            bool selected = i == currentIndex();
            bool hovered = i == tabAt(mapFromGlobal(QCursor::pos()));

            opt.palette.setColor(QPalette::ButtonText, selected || hovered ? Color::primary() : Color::primaryText());
            painter.setPen(opt.palette.buttonText().color());

            QRect rect = tabRect(i);
            QRect textRect = _position == Tabs::TabPosition::Top    ? rect.adjusted(0, 0, 0, 0) :
                             _position == Tabs::TabPosition::Bottom ? rect.adjusted(0, 0, 0, 0) :
                             _position == Tabs::TabPosition::Left   ? rect.adjusted(0, 0, -30, 0) :
                                                                      rect.adjusted(30, 0, 0, 0);

            int align = _position == Tabs::TabPosition::Top    ? Qt::AlignVCenter | Qt::AlignLeft :
                        _position == Tabs::TabPosition::Bottom ? Qt::AlignVCenter | Qt::AlignLeft :
                        _position == Tabs::TabPosition::Left   ? Qt::AlignVCenter | Qt::AlignRight :
                                                                 Qt::AlignVCenter | Qt::AlignLeft;

            painter.drawText(textRect, align, tabText(i));
        }
    }

    void TabBar::drawTextCardStyle()
    {
        QStylePainter painter(this);

        for (int i = 0; i < count(); ++i)
        {
            QStyleOptionTab opt;
            initStyleOption(&opt, i);

            bool selected = i == currentIndex();
            bool hovered = i == tabAt(mapFromGlobal(QCursor::pos()));

            opt.palette.setColor(QPalette::ButtonText, selected || hovered ? Color::primary() : Color::primaryText());
            painter.setPen(opt.palette.buttonText().color());

            painter.drawText(tabRect(i), Qt::AlignCenter, tabText(i));
        }
    }

}