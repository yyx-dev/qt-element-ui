#include "stack.h"
#include "private/utils.h"
#include "scrollbar.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QCoreApplication>

namespace Element
{
    Stack::Stack(QWidget* parent)
        : QStackedWidget(parent)
    {
        setMouseTracking(true);
        setContentsMargins(0, 0, 4, 0); // remaing space for dragging width
    }

    Stack& Stack::setFooter(QWidget* footer)
    {
        _footer = footer;
        return *this;
    }

    Stack& Stack::addWidget(Menu::Item* item, QWidget* widget)
    {
        widget->setContentsMargins(40, 40, 40, 80);
        setMouseTrackingRec(widget);

        ScrollArea* area = new ScrollArea(this);
        area->setMouseTracking(true);
        area->setWidget(widget);

        int i = QStackedWidget::addWidget(area);
        _item2index.insert(item, i);
        return *this;
    }

    void Stack::showWidget(Menu::Item* item)
    {
        if (!_item2index.contains(item))
        {
            _item2index.insert(item, count());
            addWidget(item, defaultWidget(item));
        }

        setCurrentIndex(_item2index.value(item));
    }

    QWidget* Stack::defaultWidget(Menu::Item* item)
    {
        QWidget* widget = new QWidget;

        QLabel* label = new QLabel(widget);
        label->setText("Default Widget");
        label->setFont(FontHelper().setBold().getFont());
        label->setStyleSheet("QLabel{ font-size: 32px; color: #6B778C; }");

        QVBoxLayout* layout = new QVBoxLayout(widget);
        layout->addWidget(label, 0, Qt::AlignTop);
        return widget;
    }

    void Stack::setMouseTrackingRec(QWidget* widget, bool enable)
    {
        if (!widget) return;

        widget->setMouseTracking(enable);

        for (QObject* child : widget->children())
            setMouseTrackingRec(qobject_cast<QWidget*>(child), enable);
    }


    ScrollArea::ScrollArea(QWidget* parent)
        : QScrollArea(parent)
    {
        setVerticalScrollBar(new ScrollBar(Qt::Vertical, viewport()));
        setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        setWidgetResizable(true);
        setFrameStyle(QFrame::NoFrame);
    }

    void ScrollArea::mousePressEvent(QMouseEvent* event)
    {
        QMouseEvent newEvent(
            QEvent::MouseButtonPress,
            mapFromGlobal(mapToGlobal(event->pos())),
            event->globalPos(),
            event->button(),
            event->buttons(),
            event->modifiers()
        );
        QCoreApplication::sendEvent(parentWidget(), &newEvent);
    }

    void ScrollArea::mouseMoveEvent(QMouseEvent* event)
    {
        QMouseEvent newEvent(
            QEvent::MouseMove,
            mapFromGlobal(mapToGlobal(event->pos())),
            event->globalPos(),
            event->button(),
            event->buttons(),
            event->modifiers()
        );
        QCoreApplication::sendEvent(parentWidget(), &newEvent);
    }

    void ScrollArea::mouseReleaseEvent(QMouseEvent* event)
    {
        QMouseEvent newEvent(
            QEvent::MouseButtonRelease,
            mapFromGlobal(mapToGlobal(event->pos())),
            event->globalPos(),
            event->button(),
            event->buttons(),
            event->modifiers()
        );
        QCoreApplication::sendEvent(parentWidget(), &newEvent);
    }

}