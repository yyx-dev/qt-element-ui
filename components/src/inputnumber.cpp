#include "inputnumber.h"

#include "base.h"
#include "color.h"

#include <QLineEdit>


namespace Element
{

    InputNumber::InputNumber(int value, QWidget* parent)
        : InputNumber(parent)
    {
        QSpinBox::setValue(value);
    }

    InputNumber::InputNumber(QWidget* parent)
        : QSpinBox(parent)
    {
        setSize(Size::Default);
        setAlignment(Qt::AlignCenter);
        connect(this, QOverload<int>::of(&QSpinBox::valueChanged), this, &InputNumber::onvalueChanged);
    }

    InputNumber::Size InputNumber::getSize()
    {
        return _size;
    }

    InputNumber& InputNumber::setSize(Size size)
    {
        _size = size;

        int width;
        int height;
        QString fontSize;
        QString buttonWidth;
        QString buttonHeight;

        if (size == Size::Large)
        {
            fontSize = "16px";
            width = 220, height = 52;
            buttonWidth = "52px", buttonHeight = "50px";
        }
        else if (size == Size::Default)
        {
            fontSize = "16px";
            width = 200, height = 42;
            buttonWidth = "42px", buttonHeight = "40px";
        }
        else
        {
            fontSize = "12px";
            width = 180, height = 32;
            buttonWidth = "32px", buttonHeight = "30px";
        }

        _qssHelper.setProperty("QSpinBox", "font-family", Comm::fontFmaily)
            .setProperty("QSpinBox", "font-size", fontSize)
            .setProperty("QSpinBox", "color", Color::regularText())
            .setProperty("QSpinBox", "background", Color::baseBackground())
            .setProperty("QSpinBox", "border-radius", "4px")
            .setProperty("QSpinBox", "border", "1px solid " + Color::baseBorder())
            .setProperty("QSpinBox", "min-height", QString::number(height) + "px")
            .setProperty("QSpinBox:hover", "border", "1px solid " + Color::disabledText())
            .setProperty("QSpinBox:focus", "border", "1px solid " + Color::primary())
            .setProperty("QSpinBox:disabled", "border", "1px solid " + Color::lightBorder())
            .setProperty("QSpinBox:disabled", "background", Color::lightFill())
            .setProperty("QSpinBox:disabled", "color", Color::placeholderText())

            .setProperty("QSpinBox:down-button", "subcontrol-origin", "margin")
            .setProperty("QSpinBox:down-button", "subcontrol-position", "center left")
            .setProperty("QSpinBox:down-button", "background-color", Color::lightFill())
            .setProperty("QSpinBox:down-button", "left", "1px")
            .setProperty("QSpinBox:down-button", "width", buttonWidth)
            .setProperty("QSpinBox:down-button", "height", buttonHeight)

            .setProperty("QSpinBox:up-button", "subcontrol-origin", "margin")
            .setProperty("QSpinBox:up-button", "subcontrol-position", "center right")
            .setProperty("QSpinBox:up-button", "background-color", Color::lightFill())
            .setProperty("QSpinBox:up-button", "right", "1px")
            .setProperty("QSpinBox:up-button", "width", buttonWidth)
            .setProperty("QSpinBox:up-button", "height", buttonHeight);

        if (size == Size::Large || size == Size::Default)
        {
            _qssHelper.setProperty("QSpinBox:down-button", "image", "url(:/icons/special/minus-regular-text-20.png)")
                .setProperty("QSpinBox:down-button:hover", "image", "url(:/icons/special/minus-primary-20.png)")
                .setProperty("QSpinBox:down-button:disabled", "image", "url(:/icons/special/minus-light-border-20.png)")
                .setProperty("QSpinBox:up-button", "image", "url(:/icons/special/plus-regular-text-20.png)")
                .setProperty("QSpinBox:up-button:hover", "image", "url(:/icons/special/plus-primary-20.png)")
                .setProperty("QSpinBox:up-button:disabled", "image", "url(:/icons/special/plus-light-border-20.png)");
        }
        else
        {
            _qssHelper.setProperty("QSpinBox:down-button", "image", "url(:/icons/special/minus-regular-text-16.png)")
                .setProperty("QSpinBox:down-button:hover", "image", "url(:/icons/special/minus-primary-16.png)")
                .setProperty("QSpinBox:down-button:disabled", "image", "url(:/icons/special/minus-light-border-16.png)")
                .setProperty("QSpinBox:up-button", "image", "url(:/icons/special/plus-regular-text-16.png)")
                .setProperty("QSpinBox:up-button:hover", "image", "url(:/icons/special/plus-primary-16.png)")
                .setProperty("QSpinBox:up-button:disabled", "image", "url(:/icons/special/plus-light-border-16.png)");
        }

        setStyleSheet(_qssHelper.generate());
        setFixedSize(width, height);

        return *this;
    }

    bool InputNumber::isDisabled()
    {
        return !QSpinBox::isEnabled();
    }

    InputNumber& InputNumber::setDisabled(bool disabled)
    {
        QSpinBox::setDisabled(disabled);
        return *this;
    }

    bool InputNumber::getReadOnly()
    {
        return QSpinBox::isReadOnly();
    }

    InputNumber& InputNumber::setReadOnly(bool readonly)
    {
        QSpinBox::setReadOnly(readonly);
        return *this;
    }

    InputNumber::ControlsPosition InputNumber::getControlsPosition()
    {
        return _controlsPosition;
    }

    InputNumber& InputNumber::setControlsPosition(ControlsPosition controlsPosition)
    {
        _controlsPosition = controlsPosition;
        return *this;
    }

    int InputNumber::getValue()
    {
        return QSpinBox::value();
    }

    InputNumber& InputNumber::setValue(int value)
    {
        QSpinBox::setValue(value);
        return *this;
    }

    QString InputNumber::getPrefix()
    {
        return QSpinBox::prefix();
    }

    InputNumber& InputNumber::setPrefix(const QString &prefix)
    {
        QSpinBox::setPrefix(prefix + " ");
        return *this;
    }

    QString InputNumber::getSuffix()
    {
        return QSpinBox::suffix();
    }

    InputNumber& InputNumber::setSuffix(const QString &suffix)
    {
        QSpinBox::setSuffix(" " + suffix);
        return *this;
    }

    int InputNumber::getStep()
    {
        return QSpinBox::singleStep();
    }

    InputNumber& InputNumber::setStep(int val)
    {
        QSpinBox::setSingleStep(val);
        return *this;
    }

    int InputNumber::getMin()
    {
        return QSpinBox::minimum();
    }

    InputNumber& InputNumber::setMin(int min)
    {
        QSpinBox::setMinimum(min);
        return *this;
    }

    int InputNumber::getMax()
    {
        return QSpinBox::maximum();
    }

    InputNumber& InputNumber::setMax(int max)
    {
        QSpinBox::setMaximum(max);
        return *this;
    }

    InputNumber& InputNumber::setRange(int min, int max)
    {
        QSpinBox::setRange(min, max);
        return *this;
    }

    void InputNumber::onvalueChanged(int)
    {
        QSpinBox::lineEdit()->deselect();
    }

}
