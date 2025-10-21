#pragma once

#include "base.h"

#include <QLabel>
#include <QBoxLayout>
#include <QTimer>

namespace Element
{

    class Tooltip : public QWidget
    {

    Q_OBJECT

    public:
        enum class Placement
        {
            Top, TopStart, TopEnd,
            Left, LeftStart, LeftEnd,
            Right, RightStart, RightEnd,
            Bottom, BottomStart, BottomEnd,
        };

        enum class Effect
        {
            Dark,
            Light,
        };

        enum class Trigger
        {
            Hover,
            Click,
            Focus,
            ContextMenu
        };

    public:
        Tooltip& setPlacement(Placement placement);
        Tooltip& setEffect(Effect effect);
        Tooltip& setTrigger(Trigger trigger);
        Tooltip& setText(const QString& text);
        Tooltip& setDisabled(bool disabled);
        Tooltip& setOffset(int offset);
        Tooltip& setShowAfter(int msec);
        Tooltip& setHideAfter(int msec);
        Tooltip& setShowArrow(bool showArrow);
        Tooltip& setAutoClose(int duration);
        Tooltip& setEnterable(bool enterable);

        void show();
        void hide();
        void setVisible(bool visible) override;

    public:
        Tooltip(const QString& text, QWidget* target);
        Tooltip(const QString& text, Effect effect, QWidget* target);
        Tooltip(const QString& text, Placement placement, QWidget* target);
        Tooltip(const QString& text, Placement placement, Effect effect, QWidget* target);

    protected:
        void showEvent(QShowEvent* event) override;
        void hideEvent(QHideEvent* event) override;
        void paintEvent(QPaintEvent* event) override;
        bool eventFilter(QObject* obj, QEvent* event) override;

    private:
        void updatePosition();

    private:
        Placement _placement = Placement::Top;
        Effect _effect = Effect::Dark;
        Trigger _trigger = Trigger::Hover;

        int _offset = 15;
        int _showAfter = 0;
        int _hideAfter = 200;
        bool _showArrow = true;
        bool _duration = 0;
        bool _enterable = true;

    private:
        QWidget* _target = nullptr;
        QLabel* _label = nullptr;
        Arrow* _arrow = nullptr;

        QTimer* _showTimer = nullptr;
        QTimer* _hideTimer = nullptr;
        QTimer* _autoCloseTimer = nullptr;

        QSSHelper _qsshelper;
    };

}
