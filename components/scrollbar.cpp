#include "scrollbar.h"

#include <QApplication>
#include <QDateTime>
#include <QDebug>
#include <QQueue>
#include <QtMath>


namespace Element
{

    ScrollBar::ScrollBar(Qt::Orientation orientation, QWidget* parent)
        : QScrollBar(orientation, parent)
        , lastWheelEvent(nullptr)
        , stepsTotal(0)
    {
        setMouseTracking(true);
        setStyleSheet(R"(
            QScrollBar { background-color: transparent; border: none; }
            QScrollBar:vertical { width: 10px; }
            QScrollBar:horizontal { height: 10px; }
            QScrollBar::handle { background: rgba(144, 147, 153, 0.3); border-radius: 5px; }
            QScrollBar::handle:hover { background: rgba(144, 147, 153, 0.5); }
            QScrollBar::handle:pressed { background: rgba(144, 147, 153, 0.5); }
            QScrollBar::add-page, QScrollBar::sub-page { background: none; }
            QScrollBar::add-line:vertical { height: 0px; subcontrol-position: bottom; subcontrol-origin: margin; }
            QScrollBar::sub-line:vertical { height: 0px; subcontrol-position: top; subcontrol-origin: margin; }
            QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical { height: 0px; width: 0px; }
            QScrollBar::add-line:horizontal { width: 0px; subcontrol-position: right; subcontrol-origin: margin; }
            QScrollBar::sub-line:horizontal { width: 0px; subcontrol-position: left; subcontrol-origin: margin; }
            QScrollBar::left-arrow:horizontal, QScrollBar::right-arrow:horizontal { width: 0px; height: 0px; } )");

        smoothMoveTimer = new QTimer(this);
        connect(smoothMoveTimer, &QTimer::timeout, this, &ScrollBar::slotSmoothMove);
    }

    void ScrollBar::wheelEvent(QWheelEvent* e)
    {
        static QQueue<qint64> scrollStamps;
        qint64 now = QDateTime::currentDateTime().toMSecsSinceEpoch();
        scrollStamps.enqueue(now);
        while (now - scrollStamps.front() > 500)
            scrollStamps.dequeue();
        double accRatio = qMin(scrollStamps.size() / 15.0, 1.0);
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        if (!lastWheelEvent)
        {
            // Qt 6 使用 clone() 方法创建一个新的副本
            lastWheelEvent = e->clone();
        }
        else
        {
            // 如果已经存在旧的事件对象，先删除旧的再克隆新的
            delete lastWheelEvent;
            lastWheelEvent = e->clone();
        }
#else
        if (!lastWheelEvent)
            lastWheelEvent = new QWheelEvent(*e);
        else
            *lastWheelEvent = *e;
#endif
        stepsTotal = 60 * 400 / 1000;
        double multiplier = 1.0;
        if (QApplication::keyboardModifiers() & Qt::ALT)
            multiplier *= 5.0;
        auto delta = e->angleDelta() * multiplier;
        delta += delta * 2.5 * accRatio;

        stepsLeftQueue.push_back(qMakePair(delta, stepsTotal));
        smoothMoveTimer->start(1000 / 60);

        bool isTop = delta.y() > 0 && value() == minimum();
        bool isBottom = delta.y() < 0 && value() == maximum();
        if (!isTop && !isBottom)
        {
            e->accept();
        }
    }

    QPointF ScrollBar::subDelta(QPoint delta, int stepsLeft) const
    {
        double m = stepsTotal / 2.0;
        double x = abs(stepsTotal - stepsLeft - m);
        return (cos(x * M_PI / m) + 1.0) / (2.0 * m) * delta;
    }

    void ScrollBar::slotSmoothMove()
    {
        QPointF totalDelta;

        for (auto& it : stepsLeftQueue)
        {
            totalDelta += subDelta(it.first, it.second);
            --(it.second);
        }
        while (!stepsLeftQueue.empty() && stepsLeftQueue.begin()->second == 0)
            stepsLeftQueue.pop_front();

        QWheelEvent e(
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
            lastWheelEvent->position(),
            lastWheelEvent->globalPosition(),
#else
            lastWheelEvent->pos(),
            lastWheelEvent->globalPos(),
#endif
            QPoint(),
            totalDelta.toPoint(),
            lastWheelEvent->buttons(),
            lastWheelEvent->modifiers(),
            lastWheelEvent->phase(),
            lastWheelEvent->inverted());
        QScrollBar::wheelEvent(&e);
        if (stepsLeftQueue.empty())
        {
            smoothMoveTimer->stop();
        }
    }
}
