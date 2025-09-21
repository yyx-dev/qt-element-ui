#include "dropdown.h"
#include "icon.h"
#include "color.h"

#include <QBoxLayout>
#include <QDebug>

namespace Element
{

    Dropdown::Dropdown(QWidget* parent)
        : Dropdown("Dropdown List", parent)
    {}

    Dropdown::Dropdown(const QString& text, QWidget* parent)
        : QWidget(parent)
        , _text(new Text(text, Text::Type::Primary, this))
        , _icon(new QLabel(this))
        , _menu(new Menu(this))
        , _actions(new QHash<QString, QAction*>())
    {
        _icon->setPixmap(Icon::instance().getPixmap(Icon::ArrowDown, Color::primary(), 18));

        QHBoxLayout* layout = new QHBoxLayout(this);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(5);
        layout->addWidget(_text);
        layout->addWidget(_icon);

        setLayout(layout);
        adjustSize();

        setMouseTracking(true);
    }

    void Dropdown::setText(const QString& text)
    {
        _text->setText(text);
        adjustSize();
    }

    void Dropdown::addItem(const QString& name)
    {
        if (_actions->contains(name))
            return;
        _actions->insert(name, _menu->addAction(name));
    }

    void Dropdown::addSeparator()
    {
        _menu->addSeparator();
    }

    void Dropdown::enterEvent(QEvent* event)
    {
        QPoint menuPos = _text->mapToGlobal(QPoint(5, _text->height() + 10));
        _menu->popup(menuPos);
        QWidget::enterEvent(event);
    }

    void Dropdown::leaveEvent(QEvent* event)
    {
        _menu->hide();
        QWidget::leaveEvent(event);
    }

    Menu::Menu(QWidget* parent) : QMenu(parent)
    {
        setStyleSheet(R"(
            QMenu {
                background-color: white;
                border: 1px solid #E4E7ED;
                padding: 0;
                border-radius: 4px;
            }
            QMenu::item {
                min-width: 100px;
                min-height: 40px;
                padding: 0 10px;
                margin: 0;
                color: #606266;

            }
            QMenu::item:selected {
                background-color: #ECF5FF;
                color: #409EFF;
            }
            QMenu::item:disabled {
                color: #C0C4CC;
            }
            QMenu::separator {
                height: 1px;
                background-color: #EBEEF5;
                margin: 6px 0;
            })");

        QFont menuFont;
        menuFont.setFamilies(CommonVar::baseFontFmailies);
        menuFont.setPointSize(10);
        setFont(menuFont);

        setAttribute(Qt::WA_Hover);

        setWindowFlags(windowFlags() | Qt::NoDropShadowWindowHint);
    }

    bool Menu::event(QEvent* e)
    {
        if (e->type() == QEvent::HoverMove || e->type() == QEvent::HoverEnter)
        {
            QHoverEvent *hoverEvent = static_cast<QHoverEvent*>(e);
            QAction* action = actionAt(hoverEvent->pos());

            if (action)
            {
                if (action->isEnabled())
                    setCursor(Qt::PointingHandCursor);
                else
                    setCursor(Qt::ForbiddenCursor);
            }
            else
            {
                unsetCursor();
            }
        }
        else if (e->type() == QEvent::HoverLeave)
        {
            hide();
            unsetCursor();
        }

        return QMenu::event(e);
    }

}
