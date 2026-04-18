// #pragma once

// #include "tooltip.h"

// #include <QWidget>

// namespace Element
// {
//     class Popover : public QWidget
//     {
//     Q_OBJECT

//     public:
//         enum class Placement
//         {
//             Top, TopStart, TopEnd,
//             Left, LeftStart, LeftEnd,
//             Right, RightStart, RightEnd,
//             Bottom, BottomStart, BottomEnd,
//         };

//         enum class Effect { Dark, Light, };

//         enum class Trigger { Hover, Click, Focus, ContextMenu };

//     public:
//         Popover& setPlacement(Placement placement);
//         Popover& setEffect(Effect effect);
//         Popover& setTrigger(Trigger trigger);
//         Popover& setText(const QString& text);
//         Popover& setDisabled(bool disabled);
//         Popover& setOffset(int offset);
//         Popover& setShowAfter(int msec);
//         Popover& setHideAfter(int msec);
//         Popover& setShowArrow(bool showArrow);
//         Popover& setAutoClose(int duration);
//         Popover& setEnterable(bool enterable);

//         Placement getPlacement();

//         bool isDisabled();

//         Popover& setMoveable(bool moveable);
//         Popover& setPosition(const QPoint& start);

//     public:
//         void show();
//         void hide();
//         void setVisible(bool visible) override;

//     public:
//         Popover(const QString& text, QWidget* target);
//         Popover(const QString& text, Effect effect, QWidget* target);
//         Popover(const QString& text, Placement placement, QWidget* target);
//         Popover(const QString& text, Placement placement, Effect effect, QWidget* target);

//     protected:
//         void showEvent(QShowEvent* event) override;
//         void hideEvent(QHideEvent* event) override;
//         void paintEvent(QPaintEvent* event) override;
//         bool eventFilter(QObject* obj, QEvent* event) override;

//     private:
//         void updatePosition();
//         Placement checkPlacement();

//     private:
//         Placement _placement = Placement::Top;
//         Effect _effect = Effect::Dark;
//         Trigger _trigger = Trigger::Hover;

//         int _offset = 15;
//         int _showAfter = 0;
//         int _hideAfter = 200;
//         bool _showArrow = true;
//         bool _duration = 0;
//         bool _enterable = true;

//         bool _moveable = false;

//     private:
//         QWidget* _target = nullptr;
//         QWidget* _content = nullptr;
//         Arrow* _arrow = nullptr;

//         QTimer* _showTimer = nullptr;
//         QTimer* _hideTimer = nullptr;
//         QTimer* _autoCloseTimer = nullptr;

//         QSSHelper _qsshelper;
//     };

// }
