#pragma once

#include "base.h"

#include <QSpinBox>

namespace Element
{
    class InputNumber : public QSpinBox
    {
    Q_OBJECT

    public:
        enum class Size
        {
            Large = 0,
            Default,
            Small,
        };

        enum class ControlsPosition
        {
            Default = 0,
            Right,
        };

    public:
        Size getSize();
        InputNumber& setSize(Size size);

        bool isDisabled();
        InputNumber& setDisabled(bool disabled);

        bool getReadOnly();
        InputNumber& setReadOnly(bool readonly);

        ControlsPosition getControlsPosition();
        InputNumber& setControlsPosition(ControlsPosition size);

        int getValue();
        InputNumber& setValue(int value);

        QString getPrefix();
        InputNumber& setPrefix(const QString &prefix);

        QString getSuffix();
        InputNumber& setSuffix(const QString &suffix);

        int getStep();
        InputNumber& setStep(int val);

        int getMin();
        InputNumber& setMin(int min);

        int getMax();
        InputNumber& setMax(int max);

        InputNumber& setRange(int min, int max);

    public:
        InputNumber(QWidget* parent = nullptr);
        InputNumber(int value, QWidget* parent = nullptr);

        void onvalueChanged(int) ;

    private:
        Size _size = Size::Default;
        ControlsPosition _controlsPosition = ControlsPosition::Default;

    private:
        QSSHelper _qssHelper;
    };
}
