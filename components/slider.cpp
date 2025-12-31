#include "color.h"
#include "private/utils.h"
#include "slider.h"

#include <QPainter>

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#    include <QPainterPath>
#endif
#include <QApplication>
#include <QMouseEvent>
#include <QStyleOptionSlider>


namespace Element
{
    Slider::Slider(QWidget* parent)
        : Slider(0, Orientation::Horizontal, parent)
    {
    }

    Slider::Slider(int value, QWidget* parent)
        : Slider(value, Orientation::Horizontal, parent)
    {
    }

    Slider::Slider(Orientation orient, QWidget* parent)
        : Slider(0, orient, parent)
    {
    }

    Slider::Slider(int value, Orientation orient, QWidget* parent)
        : QSlider(parent)
        , _tooltip(new Tooltip("", this))
    {
        _tooltip->setMoveable(true);

        setMouseTracking(true);
        setCursor(Qt::PointingHandCursor);

        setOrientation(orient);
        setSize(200);

        setMin(0);
        setMax(100);
        setStep(1);
        setValue(value);
    }

    void Slider::paintEvent(QPaintEvent*)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QRect grvRect;
        if (_orientation == Orientation::Horizontal)
            grvRect = QRect((width() - _grvsize) / 2, (height() - 6) / 2, _grvsize, 6);
        else
            grvRect = QRect((width() - 6) / 2, (height() - _grvsize) / 2, 6, _grvsize);

        QPoint hdlCenter = getHandleCenter();

        // groove
        painter.setPen(Qt::NoPen);

        if (_orientation == Orientation::Horizontal)
        {
            QRect leftRect(grvRect.left(), grvRect.top(), hdlCenter.x() - grvRect.left(), grvRect.height());
            QRect rightRect(hdlCenter.x(), grvRect.top(), grvRect.right() - hdlCenter.x(), grvRect.height());

            painter.setBrush(QColor(isEnabled() ? Color::primary() : Color::placeholderText()));
            painter.drawRoundedRect(leftRect, 2, 2);

            painter.setBrush(QColor(Color::lightBorder()));
            painter.drawRoundedRect(rightRect, 2, 2);
        }
        else
        {
            QRect bottomRect(grvRect.left(), hdlCenter.y(), grvRect.width(), grvRect.bottom() - hdlCenter.y());
            QRect topRect(grvRect.left(), grvRect.top(), grvRect.width(), hdlCenter.y() - grvRect.top());

            painter.setBrush(QColor(isEnabled() ? Color::primary() : Color::placeholderText()));
            painter.drawRoundedRect(bottomRect, 2, 2);

            painter.setBrush(QColor(Color::lightBorder()));
            painter.drawRoundedRect(topRect, 2, 2);
        }

        // handle
        int hdlSize = _isHovered ? 24 : 20;
        QRect hdlRect(hdlCenter - QPoint(hdlSize / 2, hdlSize / 2), QSize(hdlSize, hdlSize));

        painter.setBrush(Qt::white);
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(hdlRect);

        QPen ringPen(QColor(isEnabled() ? Color::primary() : Color::placeholderText()), 2);
        painter.setPen(ringPen);
        painter.setBrush(Qt::NoBrush);
        painter.drawEllipse(hdlRect);
    }

    void Slider::mouseMoveEvent(QMouseEvent* event)
    {
        if (!isEnabled())
            return;

        bool wasHovered = _isHovered;
        _isHovered = getHandleRect().contains(event->pos());

        if (wasHovered != _isHovered)
        {
            setCursor(_isHovered ? Qt::OpenHandCursor : Qt::PointingHandCursor);
            update();
        }

        if (_isDragging)
        {
            setValue(posToValue(event->pos()));
        }
    }

    void Slider::mousePressEvent(QMouseEvent* event)
    {
        if (!isEnabled())
            return;

        if (event->button() == Qt::LeftButton)
        {
            if (getHandleRect().contains(event->pos()))
            {
                setCursor(Qt::ClosedHandCursor);
                _isDragging = true;
            }
            else
            {
                setValue(posToValue(event->pos()));
                _isDragging = true;
            }

            event->accept();
        }
        else
        {
            QSlider::mousePressEvent(event);
        }
    }

    void Slider::mouseReleaseEvent(QMouseEvent* event)
    {
        if (event->button() == Qt::LeftButton)
        {
            setCursor(Qt::OpenHandCursor);
            _isDragging = false;
            event->accept();
        }
        else
        {
            QSlider::mouseReleaseEvent(event);
        }
    }

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    void Slider::enterEvent(QEnterEvent* event)
#else
    void Slider::enterEvent(QEvent* event)
#endif
    {
        if (!isEnabled())
            QApplication::setOverrideCursor(Qt::ForbiddenCursor);
        QSlider::enterEvent(event);
    }

    void Slider::leaveEvent(QEvent* event)
    {
        if (_isHovered)
        {
            _isHovered = false;
            update();
        }
        if (!isEnabled())
            QApplication::restoreOverrideCursor();

        QSlider::leaveEvent(event);
    }

    void Slider::moveEvent(QMoveEvent* event)
    {
        QSlider::moveEvent(event);

        QPoint pos = mapToParent(getHandleCenter());
        _tooltip->setPosition(QPoint(pos.x(), pos.y() - 10));
    }

    Slider& Slider::setMin(int min)
    {
        setMinimum(min);
        return *this;
    }

    Slider& Slider::setMax(int max)
    {
        setMaximum(max);
        return *this;
    }

    Slider& Slider::setStep(int step)
    {
        setSingleStep(step);
        setPageStep(step);
        return *this;
    }

    Slider& Slider::setValue(int value)
    {
        QSlider::setValue(value);
        _tooltip->setText(QString::number(value));

        QPoint pos = mapToParent(getHandleCenter());
        _tooltip->setPosition(QPoint(pos.x(), pos.y() - 10));
        return *this;
    }

    Slider& Slider::setDisabled(bool disabled)
    {
        QSlider::setDisabled(disabled);
        return *this;
    }

    Slider& Slider::setShowStops(bool showStops)
    {
        _showStops = showStops;
        return *this;
    }

    Slider& Slider::setShowTooltip(bool showTooltip)
    {
        _showTooltip = showTooltip;
        _tooltip->setDisabled(!showTooltip);
        return *this;
    }

    Slider& Slider::setRange(bool range)
    {
        _range = range;
        return *this;
    }

    Slider& Slider::setPlacement(Tooltip::Placement placement)
    {
        _tooltip->setPlacement(placement);
        return *this;
    }

    Slider& Slider::setMarks(const QList<QPair<int, QString>>& marks)
    {
        for (const auto& mark : marks)
        {
            int scale = mark.first;
            QString text = mark.second;
        }
        return *this;
    }

    Slider& Slider::setOrientation(Orientation orient)
    {
        _orientation = orient;
        QSlider::setOrientation(orient == Orientation::Horizontal ? Qt::Horizontal : Qt::Vertical);
        setSize(200);
        return *this;
    }

    Slider& Slider::setSize(int size)
    {
        if (_orientation == Orientation::Horizontal)
        {
            setFixedWidth(size + 30);
            setFixedHeight(40);
        }
        else
        {
            setFixedHeight(size + 30);
            setFixedWidth(40);
        }
        return *this;
    }


    Slider& Slider::setOrientation(Qt::Orientation orient)
    {
        setOrientation(orient == Qt::Orientation::Horizontal ? Orientation::Horizontal : Orientation::Vertical);
        _tooltip->setPlacement(Tooltip::Placement::Top);
        return *this;
    }

    QRect Slider::getHandleRect()
    {
        int min = minimum();
        int max = maximum();
        int val = value();
        float ratio = (val - min) / static_cast<float>(max - min);

        QPoint center;
        if (_orientation == Orientation::Horizontal)
        {
            int x = (width() - _grvsize) / 2 + static_cast<int>(ratio * _grvsize);
            center = QPoint(x, height() / 2);
        }
        else
        {
            int y = (height() - _grvsize) / 2 + _grvsize - static_cast<int>(ratio * _grvsize);
            center = QPoint(width() / 2, y);
        }

        int size = _isHovered ? 24 + 2 : 20 + 2;
        return QRect(center - QPoint(size / 2, size / 2), QSize(size, size));
    }

    QPoint Slider::getHandleCenter()
    {
        int min = minimum();
        int max = maximum();
        int val = value();
        float ratio = (val - min) / static_cast<float>(max - min);

        QPoint center;
        if (_orientation == Orientation::Horizontal)
        {
            int x = (width() - _grvsize) / 2 + static_cast<int>(ratio * _grvsize);
            center = QPoint(x, height() / 2);
        }
        else
        {
            int y = (height() - _grvsize) / 2 + _grvsize - static_cast<int>(ratio * _grvsize);
            center = QPoint(width() / 2, y);
        }

        return center;
    }

    int Slider::posToValue(const QPoint& pos)
    {
        int min = minimum();
        int max = maximum();
        float ratio;

        if (_orientation == Orientation::Horizontal)
        {
            int grvleft = (width() - _grvsize) / 2;
            int x = qBound(grvleft, pos.x(), grvleft + _grvsize);
            ratio = (x - grvleft) / static_cast<float>(_grvsize);
        }
        else
        {
            int grvtop = (height() - _grvsize) / 2;
            int y = qBound(grvtop, pos.y(), grvtop + _grvsize);
            ratio = 1.0f - (y - grvtop) / static_cast<float>(_grvsize);
        }

        return min + static_cast<int>(ratio * (max - min));
    }

}
