#include "tooltip.h"

#include "private/utils.h"
#include "color.h"

#include <QPainter>
#include <QEvent>
#include <QMouseEvent>
#include <QPainterPath>

namespace Element
{

    Arrow::Arrow(QWidget* partner, QWidget* target)
        : Arrow(Color::primaryText(), Direction::Down, partner, target)
    {}

    Arrow::Arrow(const QString& color, Direction dir, QWidget* partner, QWidget* target)
        : QWidget(target->parentWidget())
        , _partner(partner)
        , _target(target)
    {
        setFixedSize(16, 8);
        setAttribute(Qt::WA_TransparentForMouseEvents);

        setColor(color);
        setDirection(dir);
        updatePosition();
    }

    void Arrow::setAlignMode(Arrow::AlignMode mode)
    {
        _mode = mode;
        updatePosition();
    }

    Arrow::AlignMode Arrow::getAlignMode()
    {
        return _mode;
    }

    void Arrow::setColor(const QString& color)
    {
        _color = color;
        update();
    }

    void Arrow::setDirection(Direction direction)
    {
        _direction = direction;
        update();
    }

    void Arrow::setBorder(const QString& color)
    {
        _borderColor = color;
        update();
    }

    void Arrow::paintEvent(QPaintEvent*)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QPolygon triangle;
        switch (_direction)
        {
        case Direction::Down:
            triangle << QPoint(0, 0) << QPoint(16, 0) << QPoint(8, 8);
            break;
        case Direction::Up:
            triangle << QPoint(0, 8) << QPoint(16, 8) << QPoint(8, 0);
            break;
        case Direction::Left:
            triangle << QPoint(8, 0) << QPoint(8, 16) << QPoint(0, 8);
            break;
        case Direction::Right:
            triangle << QPoint(0, 0) << QPoint(0, 16) << QPoint(8, 8);
            break;
        }

        // 绘制填充
        painter.setBrush(QColor(_color));
        painter.setPen(Qt::NoPen);
        painter.drawPolygon(triangle);

        // 绘制左斜边和右斜边
        if (!_borderColor.isEmpty())
        {
            QColor bc(_borderColor);
            QPen borderPen(bc);

            borderPen.setWidth(1);
            painter.setPen(borderPen);
            painter.setBrush(Qt::NoBrush);

            if (_direction == Direction::Down)
            {
                painter.drawLine(triangle[0], triangle[2]); // 左斜边
                painter.drawLine(triangle[1], triangle[2]); // 右斜边
            }
            else if (_direction == Direction::Up)
            {
                painter.drawLine(triangle[0], triangle[2]); // 左斜边
                painter.drawLine(triangle[1], triangle[2]); // 右斜边
            }
            else if (_direction == Direction::Left)
            {
                painter.drawLine(triangle[0], triangle[2]); // 上斜边
                painter.drawLine(triangle[1], triangle[2]); // 下斜边
            }
            else if (_direction == Direction::Right)
            {
                painter.drawLine(triangle[0], triangle[2]); // 上斜边
                painter.drawLine(triangle[1], triangle[2]); // 下斜边
            }
        }
    }

    void Arrow::showEvent(QShowEvent* event)
    {
        updatePosition();
        QWidget::showEvent(event);
    }

    void Arrow::updatePosition()
    {
        if (!_target) return;

        QWidget* target = _target;
        if (_mode == AlignMode::FollowPopup)
            target = _partner;

        QPoint pos;
        if (_direction == Direction::Up)
        {
            pos = QPoint(target->x() + (target->width() - 16) / 2,
                        _partner->y() - 8);
        }
        else if (_direction == Direction::Down)
        {
            pos = QPoint(target->x() + (target->width() - 16) / 2,
                        _partner->y() + _partner->height());
        }
        else if (_direction == Direction::Left)
        {
            setFixedSize(8, 16);
            pos = QPoint(_partner->x() - 8,
                        target->y() + (target->height() - 16) / 2);
        }
        else if (_direction == Direction::Right)
        {
            setFixedSize(8, 16);
            pos = QPoint(_partner->x() + _partner->width(),
                        target->y() + (target->height() - 16) / 2);
        }

        move(pos);
        update();
    }

    Tooltip::Tooltip(const QString& text, QWidget* target)
        : Tooltip(text, Placement::Top, Effect::Dark, target)
    {}

    Tooltip::Tooltip(const QString& text, Placement placement, QWidget* target)
        : Tooltip(text, placement, Effect::Dark, target)
    {}

    Tooltip::Tooltip(const QString& text, Effect effect, QWidget* target)
        : Tooltip(text, Placement::Top, effect, target)
    {}

    Tooltip::Tooltip(const QString& text, Placement placement, Effect effect, QWidget* target)
        : QWidget(target->parentWidget())
        , _target(target)
        , _label(new QLabel(text, this))
        , _arrow(new Arrow(this, target))
        , _showTimer(new QTimer(this))
        , _hideTimer(new QTimer(this))
        , _autoCloseTimer(new QTimer(this))
    {
        hide();

        _label->setFont(FontHelper(_label->font())
                .setPointSize(Comm::defaultFontSize)
                .getFont());

        setPlacement(placement);
        setEffect(effect);
        setShowArrow(true);

        _label->adjustSize();
        adjustSize();

        _target->installEventFilter(this);

        _showTimer->setSingleShot(true);
        _hideTimer->setSingleShot(true);
        _autoCloseTimer->setSingleShot(true);

        connect(_showTimer, &QTimer::timeout, this, &Tooltip::show);
        connect(_hideTimer, &QTimer::timeout, this, &Tooltip::hide);
        connect(_autoCloseTimer, &QTimer::timeout, this, &Tooltip::hide);
    }

    Tooltip& Tooltip::setPlacement(Placement placement)
    {
        _placement = placement;
        return *this;
    }

    Tooltip& Tooltip::setEffect(Effect effect)
    {
        _effect = effect;

        if (effect == Effect::Dark)
        {
            _qsshelper.setProperty("QLabel", "color", Color::basicWhite());
            _arrow->setColor(Color::primaryText());
            _arrow->setBorder("");
        }
        else
        {
            _qsshelper.setProperty("QLabel", "color", Color::basicBlack());
            _arrow->setColor(Color::basicWhite());
            _arrow->setBorder(Color::darkBorder());
        }

        _qsshelper.setProperty("QLabel", "padding", "7px 11px");

        _label->setStyleSheet(_qsshelper.generate());
        adjustSize();
        update();

        return *this;
    }

    Tooltip& Tooltip::setTrigger(Trigger trigger)
    {
        _trigger = trigger;
        return *this;
    }

    Tooltip& Tooltip::setText(const QString& text)
    {
        _label->setText(text);
        _label->adjustSize();
        adjustSize();
        return *this;
    }

    Tooltip& Tooltip::setDisabled(bool disabled)
    {
        QWidget::setDisabled(disabled);
        return *this;
    }

    Tooltip& Tooltip::setOffset(int offset)
    {
        _offset = offset;
        return *this;
    }

    Tooltip& Tooltip::setShowAfter(int msec)
    {
        _showAfter = msec;
        return *this;
    }

    Tooltip& Tooltip::setHideAfter(int msec)
    {
        _hideAfter = msec;
        return *this;
    }

    Tooltip& Tooltip::setShowArrow(bool showArrow)
    {
        _showArrow = showArrow;
        return *this;
    }

    Tooltip& Tooltip::setAutoClose(int duration)
    {
        _duration = duration;
        return *this;
    }

    Tooltip& Tooltip::setEnterable(bool enterable)
    {
        _enterable = enterable;
        return *this;
    }

    Tooltip::Placement Tooltip::getPlacement()
    {
        return _placement;
    }

    bool Tooltip::isDisabled()
    {
        return !QWidget::isEnabled();
    }

    void Tooltip::show()
    {
        if (isDisabled())
            return;

        QWidget::show();
        if (_showArrow) _arrow->show();
    }

    void Tooltip::hide()
    {
        if (isDisabled())
            return;

        QWidget::hide();
        if (_showArrow) _arrow->hide();
    }

    void Tooltip::setVisible(bool visible)
    {
        if (isDisabled())
            return;

        QWidget::setVisible(visible);
        _arrow->setVisible(visible);
    }

    void Tooltip::showEvent(QShowEvent* event)
    {
        if (!_moveable)
            updatePosition();
        QWidget::showEvent(event);

        if (_duration > 0)
            _autoCloseTimer->start(_duration);
    }

    void Tooltip::hideEvent(QHideEvent* event)
    {
        _autoCloseTimer->stop();
        QWidget::hideEvent(event);
    }

    void Tooltip::paintEvent(QPaintEvent* event)
    {
        QWidget::paintEvent(event);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // 绘制圆角背景
        QPainterPath path;
        path.addRoundedRect(rect().adjusted(0, 0, 0, 0), 4, 4, Qt::AbsoluteSize);
        painter.setClipPath(path);

        // 填充背景
        painter.fillPath(path, QColor(_effect == Effect::Dark ?
                                        Color::primaryText() : Color::basicWhite()));

        // 绘制边框以及空白线
        if (_effect == Effect::Light)
        {
            painter.setPen(QPen(QColor(Color::darkerBorder()), 1));
            painter.drawRoundedRect(rect().adjusted(0, 0, 0, 0), 4, 4, Qt::AbsoluteSize);

            QWidget* target = _target;
            if (_arrow->getAlignMode() == Arrow::AlignMode::FollowPopup)
                target = this;

            QPoint bgn, end;

            if (_placement == Placement::Top
             || _placement == Placement::TopStart
             || _placement == Placement::TopEnd)
            {
                bgn = QPoint(target->x() + (target->width() - _arrow->width()) / 2 + 2, y() + height());
                end = QPoint(target->x() + (target->width() + _arrow->width()) / 2 - 2, y() + height());
            }
            else if (_placement == Placement::Bottom
                  || _placement == Placement::BottomStart
                  || _placement == Placement::BottomEnd)
            {
                bgn = QPoint(target->x() + (target->width() - _arrow->width()) / 2 + 2, y());
                end = QPoint(target->x() + (target->width() + _arrow->width()) / 2 - 2, y());
            }
            else if (_placement == Placement::Left
                  || _placement == Placement::LeftStart
                  || _placement == Placement::LeftEnd)
            {
                bgn = QPoint(x() + width(), target->y() + (target->height() - _arrow->height()) / 2 + 2);
                end = QPoint(x() + width(), target->y() + (target->height() + _arrow->height()) / 2 - 2);
            }
            else if (_placement == Placement::Right
                  || _placement == Placement::RightStart
                  || _placement == Placement::RightEnd)
            {
                bgn = QPoint(x(), target->y() + (target->height() - _arrow->height()) / 2 + 2);
                end = QPoint(x(), target->y() + (target->height() + _arrow->height()) / 2 - 2);
            }

            painter.setPen(QPen(QColor(Color::basicWhite()), 2));
            painter.drawLine(mapFromParent(bgn), mapFromParent(end));
        }
    }

    bool Tooltip::eventFilter(QObject* obj, QEvent* event)
    {
        if (obj == _target)
        {
            auto time2show = [&] {
                _hideTimer->stop();
                if (_showAfter > 0) _showTimer->start(_showAfter);
                else show();
            };
            auto time2hide = [&] {
                _showTimer->stop();
                if (_hideAfter > 0) _hideTimer->start(_hideAfter);
                else hide();
            };

            if (_trigger == Trigger::Hover)
            {
                if (event->type() == QEvent::Enter)
                    time2show();
                else if (event->type() == QEvent::Leave)
                    time2hide();
            }
            else if (_trigger == Trigger::Click)
            {
                if (event->type() == QEvent::MouseButtonPress
                 && static_cast<QMouseEvent*>(event)->button() == Qt::LeftButton)
                    time2show();
                else if (event->type() == QEvent::FocusOut)
                    time2hide();
            }
            else if (_trigger == Trigger::Focus)
            {
                if (event->type() == QEvent::FocusIn)
                    time2show();
                else if (event->type() == QEvent::FocusOut)
                    time2hide();
            }
            else if (_trigger == Trigger::ContextMenu)
            {
                if (event->type() == QEvent::ContextMenu)
                    time2show();
                else if (event->type() == QEvent::FocusOut)
                    time2hide();
            }
            else if (event->type() == QEvent::Move || event->type() == QEvent::Resize)
            {
                if (isEnabled())
                {
                    updatePosition();
                    _arrow->updatePosition();
                }
            }
        }

        return QWidget::eventFilter(obj, event);
    }

    Tooltip& Tooltip::setMoveable(bool moveable)
    {
        _moveable = moveable;
        _arrow->setAlignMode(moveable ?
                Arrow::AlignMode::FollowPopup : Arrow::AlignMode::FollowPointing);
        return *this;
    }

    Tooltip& Tooltip::setPosition(const QPoint& start)
    {
        QPoint pos;
        if (checkPlacement() == Placement::Top)
        {
            pos.setX(start.x() - width() / 2);
            pos.setY(start.y() - height() - _offset);
        }
        else if (checkPlacement() == Placement::Left)
        {
            pos.setX(start.x() - width() - _offset);
            pos.setY(start.y() - height() / 2);
        }
        else if (checkPlacement() == Placement::Right)
        {
            pos.setX(start.x() + _offset);
            pos.setY(start.y() - height() / 2);
        }
        else if (checkPlacement() == Placement::Bottom)
        {
            pos.setX(start.x() - width() / 2);
            pos.setY(start.y() + height() / 2);
        }

        move(pos);
        _arrow->updatePosition();
        return *this;
    }

    void Tooltip::updatePosition()
    {
        if (!_target || _moveable) return;

        QPoint pos;

        if (checkPlacement() == Placement::Top)
        {
            _arrow->setDirection(Arrow::Direction::Down);
            int y = _target->y() - height() - _offset;

            if (_placement == Placement::Top)
                pos = QPoint(_target->x() + (_target->width() - width()) / 2, y);
            else if (_placement == Placement::TopStart)
                pos = QPoint(_target->x(), y);
            else if (_placement == Placement::TopEnd)
                pos = QPoint(_target->x() + _target->width() - width(), y);
        }
        else if (checkPlacement() == Placement::Left)
        {
            _arrow->setDirection(Arrow::Direction::Right);
            int x = _target->x() - width() - _offset;

            if (_placement == Placement::Left)
                pos = QPoint(x, _target->y() + (_target->height() - height()) / 2);
            else if (_placement == Placement::LeftStart)
                pos = QPoint(x, _target->y());
            else if (_placement == Placement::LeftEnd)
                pos = QPoint(x, _target->y() + _target->height() - height());
        }
        else if (checkPlacement() == Placement::Right)
        {
            _arrow->setDirection(Arrow::Direction::Left);
            int x = _target->x() + _target->width() + _offset;

            if (_placement == Placement::Right)
                pos = QPoint(x, _target->y() + (_target->height() - height()) / 2);
            else if (_placement == Placement::RightStart)
                pos = QPoint(x, _target->y());
            else if (_placement == Placement::RightEnd)
                pos = QPoint(x, _target->y() + _target->height() - height());
        }
        else if (checkPlacement() == Placement::Bottom)
        {
            _arrow->setDirection(Arrow::Direction::Up);
            int y = _target->y() + _target->height() + _offset;

            if (_placement == Placement::Bottom)
                pos = QPoint(_target->x() + (_target->width() - width()) / 2, y);
            else if (_placement == Placement::BottomStart)
                pos = QPoint(_target->x(), y);
            else if (_placement == Placement::BottomEnd)
                pos = QPoint(_target->x() + _target->width() - width(), y);
        }

        move(pos);
        _arrow->updatePosition();
    }

    Tooltip::Placement Tooltip::checkPlacement()
    {
        if (_placement == Placement::Top
         || _placement == Placement::TopStart
         || _placement == Placement::TopEnd)
            return Placement::Top;
        else if (_placement == Placement::Left
              || _placement == Placement::LeftStart
              || _placement == Placement::LeftEnd)
            return Placement::Left;
        else if (_placement == Placement::Right
              || _placement == Placement::RightStart
              || _placement == Placement::RightEnd)
            return Placement::Right;
        else if (_placement == Placement::Bottom
              || _placement == Placement::BottomStart
              || _placement == Placement::BottomEnd)
            return Placement::Bottom;
        return _placement;
    }

}
