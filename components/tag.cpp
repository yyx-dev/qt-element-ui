#include "tag.h"
#include "color.h"
#include "icon.h"
#include "private/utils.h"
#include "private/animation.h"

#include <QPainter>
#include <QMouseEvent>
#include <QFontMetrics>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QPainterPath>

namespace Element
{

    Tag::Tag(QWidget* parent) : Tag("Tag 1", Type::Info, parent)
    {}

    Tag::Tag(const QString& text, QWidget* parent) : Tag(text, Type::Info, parent)
    {}

    Tag::Tag(const QString& text, Type type, QWidget* parent)
        : QWidget(parent)
        , _text(text)
        , _type(type)
    {
        setAttribute(Qt::WA_OpaquePaintEvent, false);
        setAttribute(Qt::WA_Hover, true);
        setMouseTracking(true);
        setSize(Size::Default);
        updateCachedColors();
        setFont(FontHelper().setPointSize(9).getFont());
    }

    Tag& Tag::setEffect(Effect effect)
    {
        if (_effect == effect) return *this;

        _effect = effect;
        updateCachedColors();
        update();
        return *this;
    }

    Tag& Tag::setType(Type type)
    {
        if (_type == type) return *this;

        _type = type;
        updateCachedColors();
        update();
        return *this;
    }

    Tag& Tag::setSize(Size size)
    {
        _size = size;
        if (_size == Size::Default)
            setFixedHeight(30), setMinimumWidth(60);
        else if (_size == Size::Small)
            setFixedHeight(25), setMinimumWidth(50);
        else if (_size == Size::Large)
            setFixedHeight(40), setMinimumWidth(70);
        adjustSize();
        return *this;
    }

    Tag& Tag::setCloseable(bool closeable)
    {
        _closeable = closeable;
        update();
        return *this;
    }

    Tag& Tag::setRound(bool round)
    {
        if (_round == round) return *this;
        _round = round;
        update();
        return *this;
    }

    Tag& Tag::setDisableTransitions(bool disabled)
    {
        _disTrans = disabled;
        return *this;
    }

    Tag& Tag::setText(const QString& text)
    {
        _text = text;
        update();
        return *this;
    }

    void Tag::startClose()
    {
        if (_disTrans)
        {
            deleteLater();
            return;
        }

        Animation::shrinkFadeOut(this, Animation::Direction::Horizontal, 300, [this](){
            emit closed();
            this->deleteLater();
        });
    }

    double Tag::xScale() const
    {
        return _xScale;
    }

    void Tag::setXScale(double scale)
    {
        _xScale = scale;
        update();
    }

    double Tag::opacity() const
    {
        return _opacity;
    }

    void Tag::setOpacity(double opa)
    {
        _opacity = opa;
        update();
    }

    QString Tag::getColor()
    {
        switch (_effect)
        {
        case Effect::Light:
        case Effect::Plain:
            switch (_type) {
            case Type::Primary: return Color::primary();
            case Type::Success: return Color::success();
            case Type::Warning: return Color::warning();
            case Type::Info:    return Color::info();
            case Type::Danger:  return Color::danger();
            }
        case Effect::Dark:
            return Color::basicWhite();
        }

        return "#000000";
    }

    QString Tag::getBorderColor()
    {
        switch (_effect)
        {
        case Effect::Light:
            switch (_type) {
            case Type::Primary: return Color::primaryL4();
            case Type::Success: return Color::successL4();
            case Type::Warning: return Color::warningL4();
            case Type::Info:    return Color::infoL4();
            case Type::Danger:  return Color::dangerL4();
            }
        case Effect::Plain:
            switch (_type) {
            case Type::Primary: return Color::primaryL2();
            case Type::Success: return Color::successL2();
            case Type::Warning: return Color::warningL2();
            case Type::Info:    return Color::infoL2();
            case Type::Danger:  return Color::dangerL2();
            }
        case Effect::Dark:
            switch (_type) {
            case Type::Primary: return Color::primary();
            case Type::Success: return Color::success();
            case Type::Warning: return Color::warning();
            case Type::Info:    return Color::info();
            case Type::Danger:  return Color::danger();
            }
        }
        return "#000000";
    }

    QString Tag::getBackgroundColor()
    {
        switch (_effect)
        {
        case Effect::Light:
            switch (_type) {
            case Type::Primary: return Color::primaryL5();
            case Type::Success: return Color::successL5();
            case Type::Warning: return Color::warningL5();
            case Type::Info:    return Color::infoL5();
            case Type::Danger:  return Color::dangerL5();
            }
        case Effect::Dark:
            switch (_type) {
            case Type::Primary: return Color::primary();
            case Type::Success: return Color::success();
            case Type::Warning: return Color::warning();
            case Type::Info:    return Color::info();
            case Type::Danger:  return Color::danger();
            }
        case Effect::Plain:
            return Color::basicWhite();
        }
        return "#000000";
    }

    void Tag::paintEvent(QPaintEvent*)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        painter.save();
        painter.translate(width() / 2.0, height() / 2.0);
        painter.scale(_xScale, 1.0);
        painter.translate(-width() / 2.0, -height() / 2.0);
        painter.setOpacity(_opacity);

        int radius = _round ? height() / 2 : 4;
        QPainterPath path;
        path.addRoundedRect(rect(), radius, radius);
        painter.fillPath(path, QColor(_bgColor));
        QPen pen(QColor(_borderColor), 1);
        painter.setPen(pen);
        painter.drawRoundedRect(rect(), radius, radius);

        QFontMetrics fm(font());
        int textWidth = fm.horizontalAdvance(_text);
        int iconSize = _closeable ? 16 : 0;
        int spacing = _closeable ? 4 : 0;
        int startX = (width() - (textWidth + iconSize + spacing)) / 2;

        QRect textRect(startX, 0, textWidth, height());
        painter.setPen(_textColor);
        painter.drawText(textRect, Qt::AlignVCenter, _text);

        if (_closeable)
        {
            int iconX = startX + textWidth + spacing;
            int iconY = (height() - iconSize) / 2;
            QRect iconRect(iconX, iconY, iconSize, iconSize);
            QPixmap pixmap = _closeHover ?
                                 Icon::instance().getPixmap(Icon::CircleCloseFilled, _textColor, iconSize) :
                                 Icon::instance().getPixmap(Icon::Close, _textColor, iconSize);
            painter.drawPixmap(iconRect, pixmap);
        }

        painter.restore();
    }

    void Tag::mouseMoveEvent(QMouseEvent* event)
    {
        if (_closeable)
        {
            bool newHover = closeIconRect().contains(event->pos());
            if (newHover != _closeHover)
            {
                _closeHover = newHover;
                setCursor(_closeHover ? Qt::PointingHandCursor : Qt::ArrowCursor);
                update();
            }
        }
        QWidget::mouseMoveEvent(event);
    }

    void Tag::mouseReleaseEvent(QMouseEvent* event)
    {
        if (_closeable && closeIconRect().contains(event->pos()))
        {
            startClose();
            event->accept();
            return;
        }
        QWidget::mouseReleaseEvent(event);
    }

    void Tag::enterEvent(QEvent* event)
    {
        _hover = true;
        update();
        QWidget::enterEvent(event);
    }

    void Tag::leaveEvent(QEvent* event)
    {
        if (_closeable)
        {
            _closeHover = false;
            setCursor(Qt::ArrowCursor);
            update();
        }
        QWidget::leaveEvent(event);
    }

    QRect Tag::closeIconRect()
    {
        if (!_closeable) return QRect();
        QFontMetrics fm(font());
        int textWidth = fm.horizontalAdvance(_text);
        int iconSize = 16;
        int startX = (width() - (textWidth + iconSize + 4)) / 2;
        int iconX = startX + textWidth + 4;
        int iconY = (height() - iconSize) / 2;
        return QRect(iconX, iconY, iconSize, iconSize);
    }

    void Tag::updateCachedColors()
    {
        _textColor = getColor();
        _borderColor = getBorderColor();
        _bgColor = getBackgroundColor();
    }
}