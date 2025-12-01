#include "mask.h"

#include <QPainter>
#include <QEvent>

namespace Element
{
    Mask* MaskEf::setMask(QWidget* partner, QWidget* covered)
    {
        return new Mask(partner, covered);
    }


    Mask::Mask(QWidget* partner, QWidget* covered)
        : QWidget(covered)
        , _partner(partner)
        , _covered(covered)
    {
        setGeometry(covered->rect());
        setVisible(partner->isVisible());
        partner->installEventFilter(this);
    }

    bool Mask::eventFilter(QObject* watched, QEvent* event)
    {
        if (watched == _partner)
        {
            if (event->type() == QEvent::Show)
            {
                show();
                stackUnder(_partner);
            }
            else if (event->type() == QEvent::Hide)
            {
                hide();
            }
            else if (event->type() == QEvent::Destroy)
            {
                deleteLater();
            }
        }
        else if (watched == _covered)
        {
            if (event->type() == QEvent::Resize)
            {
                setGeometry(_covered->rect());
            }
        }

        return QWidget::eventFilter(watched, event);
    }

    void Mask::paintEvent(QPaintEvent*)
    {
        QPainter painter(this);
        painter.fillRect(rect(), QColor(0, 0, 0, 128));
    }

    void Mask::mousePressEvent(QMouseEvent*)
    {
        emit clicked();
    }
}
