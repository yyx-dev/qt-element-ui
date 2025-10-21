#include "radio.h"

#include "color.h"
#include "base.h"

#include <QApplication>


namespace Element
{

    Radio::Radio(QWidget* parent)
        : Radio("", false,  parent)
    {}

    Radio::Radio(const QString& text, QWidget* parent)
        : Radio(text, false, parent)
    {}

    Radio::Radio(const QString& text, bool checked, QWidget* parent)
        : QRadioButton(text, parent)
    {
        QFont font = FontManager::font();
        font.setPixelSize(16);
        QRadioButton::setFont(font);

        _qsshelper.setProperty("QRadioButton", "spacing", "10px");
        _qsshelper.setProperty("QRadioButton", "color", Color::regularText());
        _qsshelper.setProperty("QRadioButton:checked", "color", Color::primary());
        _qsshelper.setProperty("QRadioButton:disabled", "color", Color::placeholderText());
        _qsshelper.setProperty("QRadioButton:disabled:checked", "color", Color::placeholderText());
        _qsshelper.setProperty("QRadioButton::indicator", "border", "1px solid " + Color::baseBorder());

        _qsshelper.setProperty("QRadioButton::indicator", "background-color", "white");
        _qsshelper.setProperty("QRadioButton::indicator:checked", "border-color", Color::primary());
        _qsshelper.setProperty("QRadioButton::indicator:checked", "background-color", Color::primary());
        _qsshelper.setProperty("QRadioButton::indicator:disabled", "background-color", Color::lightFill());
        _qsshelper.setProperty("QRadioButton::indicator:disabled:checked", "background-color", Color::lightFill());
        _qsshelper.setProperty("QRadioButton::indicator:disabled:checked", "border-color", Color::baseBorder());
        setStyleSheet(_qsshelper.generate());

        setSize(_size);
        setChecked(checked);
        setCursor(Qt::PointingHandCursor);
    }

    Radio& Radio::setValue(const QVariant& value)
    {
        _value = value;
        return *this;
    }

    QVariant Radio::getValue()
    {
        return _value;
    }

    Radio& Radio::setText(const QString& text)
    {
        QRadioButton::setText(text);
        return *this;
    }

    QString Radio::getText()
    {
        return QRadioButton::text();
    }

    Radio& Radio::setDisabled(bool disabled)
    {
        QRadioButton::setEnabled(!disabled);
        return *this;
    }

    bool Radio::isDisabled()
    {
        return !QRadioButton::isEnabled();
    }

    Radio& Radio::setSize(Size size)
    {
        _size = size;

        QFont font = QRadioButton::font();
        font.setPixelSize(size == Size::Small ? 14 : 16);
        QRadioButton::setFont(font);

        if (size == Size::Small)
        {
            _qsshelper.setProperty("QRadioButton::indicator", "border-radius", "8px");
            _qsshelper.setProperty("QRadioButton::indicator", "width", "14px");
            _qsshelper.setProperty("QRadioButton::indicator", "height", "14px");
        }
        else
        {
            _qsshelper.setProperty("QRadioButton::indicator", "border-radius", "9px");
            _qsshelper.setProperty("QRadioButton::indicator", "width", "16px");
            _qsshelper.setProperty("QRadioButton::indicator", "height", "16px");
        }
        _qsshelper.setProperty("QRadioButton::indicator:checked", "image", "url(:/icons/special/radio-basic-white-6.png)");
        _qsshelper.setProperty("QRadioButton::indicator:disabled:checked", "image", "url(:/icons/special/radio-placeholder-text-6.png)");

        setStyleSheet(_qsshelper.generate());
        setFixedHeight(size == Size::Large ? 50 : size == Size::Default ? 40 : 30);

        adjustSize();
        return *this;
    }

    Radio::Size Radio::getSize()
    {
        return _size;
    }

    Radio& Radio::setChecked(bool checked)
    {
        QRadioButton::setChecked(checked);
        return *this;
    }

    bool Radio::getChecked()
    {
        return QRadioButton::isChecked();
    }

    Radio& Radio::setBorder(bool border)
    {
        _border = border;

        if (border)
        {
            if (_size == Size::Large)
                _qsshelper.setProperty("QRadioButton", "padding", "0px 20px 0px 15px");
            else if (_size == Size::Default)
                _qsshelper.setProperty("QRadioButton", "padding", "0px 18px 0px 12px");
            else
                _qsshelper.setProperty("QRadioButton", "padding", "0px 15px 0px 10px");

            _qsshelper.setProperty("QRadioButton", "border-radius", "4px");
            _qsshelper.setProperty("QRadioButton", "border", "1px solid " + Color::baseBorder());
            _qsshelper.setProperty("QRadioButton:checked", "border-color", Color::primary());
        }
        else
        {
            _qsshelper.setProperty("QRadioButton", "padding", "0px");
            _qsshelper.setProperty("QRadioButton", "border", "none");
        }

        setStyleSheet(_qsshelper.generate());
        adjustSize();
        return *this;
    }

    bool Radio::getBorder()
    {
        return _border;
    }

    void Radio::enterEvent(QEvent* event)
    {
        if (!isEnabled())
            QApplication::setOverrideCursor(Qt::ForbiddenCursor);
        QRadioButton::enterEvent(event);
    }

    void Radio::leaveEvent(QEvent* event)
    {
        if (!isEnabled())
            QApplication::restoreOverrideCursor();
        QRadioButton::leaveEvent(event);
    }


    RadioGroup::RadioGroup(QWidget* parent)
        : RadioGroup({}, parent)
    {}

    RadioGroup::RadioGroup(const QList<Radio*>& radios, QWidget* parent)
        : QGroupBox(parent)
        , _radios(radios)
        , _layout(new QHBoxLayout(this))
    {
        setTitle("");

        _layout->setContentsMargins(15, 5, 15, 5);
        _layout->setSpacing(20);

        for (auto* radio : radios)
            addRadio(radio);

        setStyleSheet("QGroupBox { border: none; }");
    }

    RadioGroup& RadioGroup::addRadio(Radio* checkbox)
    {
        _radios.append(checkbox);
        _layout->addWidget(checkbox);
        adjustSize();
        return *this;
    }

    RadioGroup& RadioGroup::setTitle(const QString&)
    {
        QGroupBox::setTitle("");
        return *this;
    }

    RadioGroup& RadioGroup::setSize(Size size)
    {
        _size = size;

        for (auto* radio : _radios)
            radio->setSize(static_cast<Radio::Size>(_size));

        adjustSize();
        return *this;
    }

    RadioGroup::Size RadioGroup::getSize()
    {
        return _size;
    }

    RadioGroup& RadioGroup::setDisabled(bool disabled)
    {
        QGroupBox::setEnabled(!disabled);
        return *this;
    }

    bool RadioGroup::isDisabled()
    {
        return !QGroupBox::isEnabled();
    }

}
