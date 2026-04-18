// #include "popover.h"
// #include "color.h"

// namespace Element
// {
//     Popover& Popover::setPlacement(Placement placement)
//     {
//         _placement = placement;
//         return *this;
//     }

//     Popover& Popover::setEffect(Effect effect)
//     {
//         _effect = effect;

//         if (effect == Effect::Dark)
//         {
//             _qsshelper.setProperty("QLabel", "color", Color::basicWhite());
//             _arrow->setColor(Color::primaryText());
//             _arrow->setBorder("");
//         }
//         else
//         {
//             _qsshelper.setProperty("QLabel", "color", Color::basicBlack());
//             _arrow->setColor(Color::basicWhite());
//             _arrow->setBorder(Color::darkBorder());
//         }

//         _qsshelper.setProperty("QLabel", "padding", "7px 11px");

//         //_label->setStyleSheet(_qsshelper.generate());
//         adjustSize();
//         update();

//         return *this;
//     }

//     Popover& Popover::setTrigger(Trigger trigger)
//     {
//         _trigger = trigger;
//         return *this;
//     }

//     Popover& Popover::setText(const QString& text)
//     {
//         //_label->setText(text);
//         //_label->adjustSize();
//         adjustSize();
//         return *this;
//     }

//     Popover& Popover::setDisabled(bool disabled)
//     {
//         QWidget::setDisabled(disabled);
//         return *this;
//     }

//     Popover& Popover::setOffset(int offset)
//     {
//         _offset = offset;
//         return *this;
//     }

//     Popover& Popover::setShowAfter(int msec)
//     {
//         _showAfter = msec;
//         return *this;
//     }

//     Popover& Popover::setHideAfter(int msec)
//     {
//         _hideAfter = msec;
//         return *this;
//     }

//     Popover& Popover::setShowArrow(bool showArrow)
//     {
//         _showArrow = showArrow;
//         return *this;
//     }

//     Popover& Popover::setAutoClose(int duration)
//     {
//         _duration = duration;
//         return *this;
//     }

//     Popover& Popover::setEnterable(bool enterable)
//     {
//         _enterable = enterable;
//         return *this;
//     }
// }