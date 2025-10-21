#include "switch.h"

#include <QPainter>
#include <QMouseEvent>
#include <QApplication>

namespace Element
{
    Switch::Switch(QWidget* parent)
        : Switch(false, "", "", parent)
    {}

    Switch::Switch(bool active, QWidget* parent)
        : Switch(active, "", "", parent)
    {}

    Switch::Switch(const QString& activeText, const QString& inactiveText, QWidget* parent)
        : Switch(false, activeText, inactiveText, parent)
    {}

    Switch::Switch(bool active, const QString& activeText, const QString& inactiveText, QWidget* parent)
        : QWidget(parent)
    {
        setFont(FontManager::font());
        setCursor(Qt::PointingHandCursor);

        setSize(_size);
        setActive(active);
        setActiveText(activeText);
        setInactiveText(inactiveText);
    }

    Switch& Switch::setSize(Size size)
    {
        ScaleHelper& scaler = ScaleHelper::instance();

        _size = size;
        setFixedSize(scaler.scale(
                size == Size::Large ? 50 : size == Size::Default ? 40 : 30,
                size == Size::Large ? 24 : size == Size::Default ? 20 : 16));
        adjustSize();

        return *this;
    }

    Switch& Switch::setActiveColor(const QString& color)
    {
        _activeColor = color;
        update();
        return *this;
    }

    Switch& Switch::setInactiveColor(const QString& color)
    {
        _inactiveColor = color;
        update();
        return *this;
    }

    Switch& Switch::setDisabled(bool disabled)
    {
        QWidget::setDisabled(disabled);
        return *this;
    }

    bool Switch::isDisabled()
    {
        return !QWidget::isEnabled();
    }

    Switch& Switch::setLoading(bool loading)
    {
        _loading = loading;
        update();
        return *this;
    }

    bool Switch::isLoading()
    {
        return _loading;
    }

    Switch& Switch::setActive(bool active)
    {
        if (_active == active)
            return *this;

        _active = active;
        emit stateChanged(_active);

        update();
        return *this;
    }

    bool Switch::isActive()
    {
        return _active;
    }

    Switch& Switch::setActiveText(const QString& activeText)
    {
        _activeText = activeText;
        return *this;
    }

    Switch& Switch::setInactiveText(const QString& inactiveText)
    {
        _inactiveText = inactiveText;
        return *this;
    }

    Switch& Switch::setActiveIcon(Icon::Name activeIcon)
    {
        _activeIcon = activeIcon;
        return *this;
    }

    Switch& Switch::setInactiveIcon(Icon::Name inactiveIcon)
    {
        _inactiveIcon = inactiveIcon;
        return *this;
    }

    Switch& Switch::setActiveAction(Icon::Name icon)
    {
        _activeActionIcon = icon;
        return *this;
    }

    Switch& Switch::setActiveAction(char ch)
    {
        _activeActionChar = ch;
        return *this;
    }

    Switch& Switch::setInactiveAction(Icon::Name icon)
    {
        _inactiveActionIcon = icon;
        return *this;
    }

    Switch& Switch::setInactiveAction(char ch)
    {
        _inactiveActionChar = ch;
        return *this;
    }

    Switch& Switch::setActiveValue(const QVariant& activeValue)
    {
        _activeValue = activeValue;
        return *this;
    }

    QVariant Switch::getActiveValue()
    {
        return _activeValue;
    }

    Switch& Switch::setInactiveValue(const QVariant& inactiveValue)
    {
        _inactiveValue = inactiveValue;
        return *this;
    }

    QVariant Switch::getInactiveValue()
    {
        return _inactiveValue;
    }

    void Switch::paintEvent(QPaintEvent*)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // background
        painter.setBrush(QColor(_active ? _activeColor : _inactiveColor));
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(rect(), height() / 2, height() / 2);

        // thumb​​
        int diameter = height() * 4 / 5; // Diameter of the thumb​​.
        int gap = height() / 10;  // This gap = (height - diameter) / 2.​

        QRectF thumbRect(_active ? width() - diameter - gap : gap,
                    gap, diameter, diameter);

        painter.setBrush(QColor(Color::blankFill()));
        painter.drawEllipse(thumbRect);

        if (_loading)
        {
            QPixmap pixmap = Icon::instance().getPixmap(Icon::Loading,
                    _active ? _activeColor : _inactiveColor, 18);
            QRectF iconRect = QRectF(0, 0, pixmap.width(), pixmap.height());
            iconRect.moveCenter(thumbRect.center());
            painter.drawPixmap(iconRect, pixmap, pixmap.rect());
        }
        else if (!Icon::isNull(_activeActionIcon) || !Icon::isNull(_inactiveActionIcon))
        {
            Icon::Name icon = _active ? _activeActionIcon : _inactiveActionIcon;
            if (Icon::isNull(icon))
                return;

            QPixmap pixmap = Icon::instance().getPixmap(icon,
                    _active ? _activeColor : _inactiveColor, 18);
            QRectF iconRect = QRectF(0, 0, pixmap.width(), pixmap.height());
            iconRect.moveCenter(thumbRect.center());
            painter.drawPixmap(iconRect, pixmap, pixmap.rect());
        }
        else if (_activeActionChar != 0 || _inactiveActionChar != 0)
        {
            QFont font = QWidget::font();
            font.setPointSize(11);

            painter.setFont(font);
            painter.setPen(_active ? _activeColor : _inactiveColor);

            QString text = QString(_active ? _activeActionChar : _inactiveActionChar);
            painter.drawText(thumbRect, Qt::AlignCenter, text);
        }

        // text / icon
        QRectF spaceRect;
        if (_active)
            spaceRect = QRectF(2 * gap, 0, width() - diameter - 4 * gap, height());
        else
            spaceRect = QRectF(diameter + 2 * gap, 0, width() - diameter - 4 * gap, height());

        if (!_activeText.isEmpty() || !_inactiveText.isEmpty())
        {
            QFont font = QWidget::font();
            font.setPointSize(9); // web : 12px == pointsize : 9 == pixelsize : 15

            painter.setFont(font);
            painter.setPen(Color::blankFill());

            QString text = _active ? _activeText : _inactiveText;
            painter.drawText(spaceRect, Qt::AlignCenter, text);

            int width = qMax(QFontMetrics(font).horizontalAdvance(text) + height() + 2 * gap,
                           _size == Size::Large ? 50 : _size == Size::Default ? 40 : 30);
            setFixedWidth(width);
        }
        else if (!Icon::isNull(_activeIcon) || !Icon::isNull(_inactiveIcon))
        {
            Icon::Name icon = _active ? _activeIcon : _inactiveIcon;
            if (Icon::isNull(icon))
                return;

            QPixmap pixmap = Icon::instance().getPixmap(icon, Color::blankFill(), 18);
            QRectF iconRect = QRectF(0, 0, pixmap.width(), pixmap.height());
            iconRect.moveCenter(spaceRect.center());
            painter.drawPixmap(iconRect, pixmap, pixmap.rect());
        }
    }

    void Switch::mousePressEvent(QMouseEvent* event)
    {
        if (event->button() == Qt::LeftButton)
            setActive(!_active);
        QWidget::mousePressEvent(event);
    }

    void Switch::enterEvent(QEvent *event)
    {
        QWidget::enterEvent(event);
        if (!isEnabled())
            QApplication::setOverrideCursor(Qt::ForbiddenCursor);
    }

    void Switch::leaveEvent(QEvent *event)
    {
        QWidget::leaveEvent(event);
        QApplication::restoreOverrideCursor();
    }
}
