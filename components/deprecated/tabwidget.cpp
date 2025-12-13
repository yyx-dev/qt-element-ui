#include "tabwidget.h"
#include "color.h"
#include "base.h"
#include "qglobal.h"

#include <QPainter>

#include <QStyleOptionTab>
#include <QMouseEvent>

namespace Element
{
    SideBar::SideBar(QWidget* parent)
        : QTabBar(parent)
    {
        setObjectName("SideBar");
        setFont(FontHelper().setPointSize(9).getFont());
        setMouseTracking(true);
        setStyleSheet(R"(QTabBar::scroller { width: 0px; }
                         QTabBar::down-arrow, QTabBar::up-arrow { width: 0px; })");
    }

    void SideBar::paintEvent(QPaintEvent*)
    {
        QPainter painter(this);
        QStyleOptionTab opt;

        for (int i = 0; i < count(); ++i)
        {
            initStyleOption(&opt, i);
            QRect rect = tabRect(i);
            bool selected = i == currentIndex();
            bool hovered = tabAt(mapFromGlobal(QCursor::pos())) == i;

            // 绘制背景
            if (hovered || selected)
                painter.fillRect(rect, Color::primaryL5());

            // 绘制边框
            painter.setPen(Color::baseBorder()) ;
            painter.drawLine(rect.right(), rect.top(), rect.right(), rect.bottom());

            const MenuItem& menuItem = static_cast<TabWidget*>(parent())->menus()[i];

            // 绘制图标
            if (menuItem.icon != Icon::None)
            {
                QIcon icon = Icon::instance().getIcon(menuItem.icon,
                                                                selected ? Color::primary() : Color::primaryText(), 20);
                icon.paint(&painter, rect.adjusted(30, 0, 0, 0), Qt::AlignLeft | Qt::AlignVCenter, QIcon::Normal);
            }

            // 绘制文本
            painter.setPen(selected ? Color::primary() : Color::primaryText());
            painter.drawText(rect.adjusted(menuItem.icon == Icon::None ? 60 : 70, 0, -20, 0), Qt::AlignLeft | Qt::AlignVCenter, opt.text);
        }
    }

    void SideBar::mousePressEvent(QMouseEvent* event)
    {
        QTabBar::mousePressEvent(event);
    }

    TabWidget::TabWidget(QWidget* parent)
        : QTabWidget(parent)
    {
        setObjectName("tabWidget");

        setTabBar(new SideBar(this));
        setTabPosition(QTabWidget::West);
        setMovable(false);
        setDocumentMode(true);

        _qsshelper.setProperty("QTabWidget#tabWidget:pane", "border", "none");
        _qsshelper.setProperty("QTabBar#SideBar::tab", "padding", "10px 20px");
        _qsshelper.setProperty("QTabBar#SideBar::tab", "width", "130px");
        _qsshelper.setProperty("QTabBar#SideBar::tab", "height", "50px");

        setStyleSheet(_qsshelper.generate());

        connect(this, &QTabWidget::currentChanged, this, &TabWidget::handleTabClicked);
    }

    TabWidget& TabWidget::setTabIcon(int index, Icon::Name icon)
    {
        if (index < 0 || index >= _menus.size())
            return *this;

        _menus[index].icon = icon;
        return *this;
    }

    void TabWidget::handleTabClicked(int index)
    {
        if (index < 0 || index >= _menus.size())
            return;

        MenuItem& item = _menus[index];

        if (_checkedAction)
            _checkedAction->setChecked(false);
        _checkedAction = item.action;
        item.action->setChecked(true);
        emit actionTriggered(item.action);
    }

    QVector<MenuItem>& TabWidget::menus()
    {
        return _menus;
    }

    QAction* TabWidget::checkedAction()
    {
        return _checkedAction;
    }

    int TabWidget::addTab(QWidget* page, const QString& text)
    {
        int index = QTabWidget::addTab(page, text);
        QAction* action = new QAction(text, this);
        action->setCheckable(true);

        MenuItem item(action, page);
        _menus.push_back(item);

        return index;
    }

}
