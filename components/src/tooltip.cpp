#include "tooltip.h"

#include "base.h"
#include "color.h"

#include <QPainter>
#include <QEvent>
#include <QMouseEvent>

namespace Element
{

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

        QFont font = _label->font();
        font.setFamilies(Comm::fontFmailies);
        font.setPointSize(Comm::defaultFontSize);
        _label->setFont(font);

        setPlacement(placement);
        setEffect(effect);
        setShowArrow(true);

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
            _qsshelper.setProperty("QLabel", "background-color", Color::primaryText());
            _arrow->setColor(Color::primaryText());
        }
        else
        {
            _qsshelper.setProperty("QLabel", "color", Color::basicBlack());
            _qsshelper.setProperty("QLabel", "background-color", Color::basicWhite());
            _qsshelper.setProperty("QLabel", "border", "1px solid " + Color::lightBorder());
            _arrow->setColor(Color::basicWhite());
            _arrow->setBorder(Color::lightBorder());
        }

        _qsshelper.setProperty("QLabel", "border-radius", "4px");
        _qsshelper.setProperty("QLabel", "padding", "7px 11px");

        _label->setStyleSheet(_qsshelper.generate());
        adjustSize();

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
        adjustSize();
        return *this;
    }

    Tooltip& Tooltip::setDisabled(bool disabled)
    {
        if (disabled) hide();
        else show();
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

    void Tooltip::show()
    {
        QWidget::show();
        if (_showArrow) _arrow->show();
    }

    void Tooltip::hide()
    {
        QWidget::hide();
        if (_showArrow) _arrow->hide();
    }

    void Tooltip::setVisible(bool visible)
    {
        QWidget::setVisible(visible);
        _arrow->setVisible(visible);
    }

    void Tooltip::showEvent(QShowEvent* event)
    {
        adjustSize();
        updatePosition();

        if (_duration > 0)
            _autoCloseTimer->start(_duration);

        QWidget::showEvent(event);
    }

    void Tooltip::hideEvent(QHideEvent* event)
    {
        _autoCloseTimer->stop();
        QWidget::hideEvent(event);
    }

    bool Tooltip::eventFilter(QObject* obj, QEvent* event)
    {
        if (obj == _target)
        {
            auto time2show = [&]
            {
                _hideTimer->stop();
                if (_showAfter > 0)
                    _showTimer->start(_showAfter);
                else
                    show();
            };
            auto time2hide = [&]
            {
                _showTimer->stop();
                if (_hideAfter > 0)
                    _hideTimer->start(_hideAfter);
                else
                    hide();
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
        }

        return QWidget::eventFilter(obj, event);
    }

    void Tooltip::updatePosition()
    {
        if (!_target) return;

        QPoint pos;

        if (_placement == Placement::Top
         || _placement == Placement::TopStart
         || _placement == Placement::TopEnd)
        {
            _arrow->setDirection(Arrow::Direction::Down);
            int y = _target->y() - height() - _offset;

            if (_placement == Placement::Top) {
                pos = QPoint(_target->x() + (_target->width() - width()) / 2, y);
            }
            else if (_placement == Placement::TopStart) {
                pos = QPoint(_target->x(), y);
            }
            else if (_placement == Placement::TopEnd) {
                pos = QPoint(_target->x() + _target->width() - width(), y);
            }
        }
        else if (_placement == Placement::Left
              || _placement == Placement::LeftStart
              || _placement == Placement::LeftEnd)
        {
            _arrow->setDirection(Arrow::Direction::Right);
            int x = _target->x() - width() - _offset;

            if (_placement == Placement::Left) {
                pos = QPoint(x, _target->y() + (_target->height() - height()) / 2);
            }
            else if (_placement == Placement::LeftStart) {
                pos = QPoint(x, _target->y());
            }
            else if (_placement == Placement::LeftEnd) {
                pos = QPoint(x, _target->y() + _target->height() - height());
            }
        }
        else if (_placement == Placement::Right
              || _placement == Placement::RightStart
              || _placement == Placement::RightEnd)
        {
            _arrow->setDirection(Arrow::Direction::Left);
            int x = _target->x() + _target->width() + _offset;

            if (_placement == Placement::Right) {
                pos = QPoint(x, _target->y() + (_target->height() - height()) / 2);
            }
            else if (_placement == Placement::RightStart) {
                pos = QPoint(x, _target->y());
            }
            else if (_placement == Placement::RightEnd) {
                pos = QPoint(x, _target->y() + _target->height() - height());
            }
        }
        else if (_placement == Placement::Bottom
              || _placement == Placement::BottomStart
              || _placement == Placement::BottomEnd)
        {
            _arrow->setDirection(Arrow::Direction::Up);
            int y = _target->y() + _target->height() + _offset;

            if (_placement == Placement::Bottom) {
                pos = QPoint(_target->x() + (_target->width() - width()) / 2, y);
            }
            else if (_placement == Placement::BottomStart) {
                pos = QPoint(_target->x(), y);
            }
            else if (_placement == Placement::BottomEnd) {
                pos = QPoint(_target->x() + _target->width() - width(), y);
            }
        }

        move(pos);
        adjustSize();
    }

}
