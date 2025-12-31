#include "checkbox.h"

#include "color.h"
#include "private/utils.h"

#include <QApplication>


namespace Element
{
    Checkbox::Checkbox(QWidget* parent)
        : Checkbox("", false,  parent)
    {}

    Checkbox::Checkbox(const QString& text, QWidget* parent)
        : Checkbox(text, false, parent)
    {}

    Checkbox::Checkbox(const QString& text, bool checked, QWidget* parent)
        : QCheckBox(text, parent)
    {
        QCheckBox::setFont(FontHelper()
                .setPixelSize(16)
                .getFont());

        _qsshelper.setProperty("QCheckBox", "spacing", "10px");
        _qsshelper.setProperty("QCheckBox", "color", Color::regularText());
        _qsshelper.setProperty("QCheckBox:checked", "color", Color::primary());
        _qsshelper.setProperty("QCheckBox:disabled", "color", Color::placeholderText());
        _qsshelper.setProperty("QCheckBox:disabled:checked", "color", Color::placeholderText());
        _qsshelper.setProperty("QCheckBox::indicator", "border", "1px solid " + Color::baseBorder());
        _qsshelper.setProperty("QCheckBox::indicator", "border-radius", "2px");
        _qsshelper.setProperty("QCheckBox::indicator", "background-color", "white");
        _qsshelper.setProperty("QCheckBox::indicator:hover", "border-color", Color::primary());
        _qsshelper.setProperty("QCheckBox::indicator:checked", "border-color", Color::primary());
        _qsshelper.setProperty("QCheckBox::indicator:checked", "background-color", Color::primary());
        _qsshelper.setProperty("QCheckBox::indicator:indeterminate", "border-color", Color::primary());
        _qsshelper.setProperty("QCheckBox::indicator:indeterminate", "background-color", Color::primary());
        _qsshelper.setProperty("QCheckBox::indicator:disabled", "background-color", Color::lightFill());
        _qsshelper.setProperty("QCheckBox::indicator:disabled:checked", "background-color", Color::lightFill());
        _qsshelper.setProperty("QCheckBox::indicator:disabled:checked", "border-color", Color::baseBorder());
        _qsshelper.setProperty("QCheckBox::indicator:disabled:indeterminate", "background-color", Color::lightFill());
        _qsshelper.setProperty("QCheckBox::indicator:disabled:indeterminate", "border-color", Color::baseBorder());
        setStyleSheet(_qsshelper.generate());

        setSize(_size);
        setChecked(checked);
        setCursor(Qt::PointingHandCursor);
    }

    Checkbox& Checkbox::setValue(const QVariant& value)
    {
        _value = value;
        return *this;
    }

    QVariant Checkbox::getValue()
    {
        return _value;
    }

    Checkbox& Checkbox::setText(const QString& text)
    {
        QCheckBox::setText(text);
        return *this;
    }

    QString Checkbox::getText()
    {
        return QCheckBox::text();
    }

    Checkbox& Checkbox::setDisabled(bool disabled)
    {
        QCheckBox::setEnabled(!disabled);
        return *this;
    }

    bool Checkbox::isDisabled()
    {
        return !QCheckBox::isEnabled();
    }

    Checkbox& Checkbox::setSize(Size size)
    {
        _size = size;

        QCheckBox::setFont(FontHelper()
                .setFont(QCheckBox::font())
                .setPixelSize(size == Size::Small ? 14 : 16)
                .getFont());

        if (size == Size::Small)
        {
            _qsshelper.setProperty("QCheckBox::indicator", "width", "14px");
            _qsshelper.setProperty("QCheckBox::indicator", "height", "14px");
            _qsshelper.setProperty("QCheckBox::indicator:checked", "image", "url(:/icons/special/select-basic-white-10.png)");
            _qsshelper.setProperty("QCheckBox::indicator:indeterminate", "image", "url(:/icons/special/semi-select-basic-white-10.png)");
            _qsshelper.setProperty("QCheckBox::indicator:disabled:checked", "image", "url(:/icons/special/select-placeholder-text-10.png)");
            _qsshelper.setProperty("QCheckBox::indicator:disabled:indeterminate", "image", "url(:/icons/special/semi-select-placeholder-text-10.png)");
        }
        else
        {
            _qsshelper.setProperty("QCheckBox::indicator", "width", "16px");
            _qsshelper.setProperty("QCheckBox::indicator", "height", "16px");
            _qsshelper.setProperty("QCheckBox::indicator:checked", "image", "url(:/icons/special/select-basic-white-12.png)");
            _qsshelper.setProperty("QCheckBox::indicator:indeterminate", "image", "url(:/icons/special/semi-select-basic-white-12.png)");
            _qsshelper.setProperty("QCheckBox::indicator:disabled:checked", "image", "url(:/icons/special/select-placeholder-text-12.png)");
            _qsshelper.setProperty("QCheckBox::indicator:disabled:indeterminate", "image", "url(:/icons/special/semi-select-placeholder-text-12.png)");
        }
        setStyleSheet(_qsshelper.generate());

        setFixedHeight(size == Size::Large ? 50 : size == Size::Default ? 40 : 30);
        adjustSize();
        return *this;
    }

    Checkbox::Size Checkbox::getSize()
    {
        return _size;
    }

    Checkbox& Checkbox::setChecked(bool checked)
    {
        QCheckBox::setChecked(checked);
        return *this;
    }

    bool Checkbox::getChecked()
    {
        return QCheckBox::isChecked();
    }

    Checkbox& Checkbox::setBorder(bool border)
    {
        _border = border;

        if (border)
        {
            if (_size == Size::Large)
                _qsshelper.setProperty("QCheckBox", "padding", "0px 20px 0px 15px");
            else if (_size == Size::Default)
                _qsshelper.setProperty("QCheckBox", "padding", "0px 18px 0px 12px");
            else
                _qsshelper.setProperty("QCheckBox", "padding", "0px 15px 0px 10px");

            _qsshelper.setProperty("QCheckBox", "border-radius", "4px");
            _qsshelper.setProperty("QCheckBox", "border", "1px solid " + Color::baseBorder());
            _qsshelper.setProperty("QCheckBox:checked", "border-color", Color::primary());
        }
        else
        {
            _qsshelper.setProperty("QCheckBox", "padding", "0px");
            _qsshelper.setProperty("QCheckBox", "border", "none");
        }

        setStyleSheet(_qsshelper.generate());
        adjustSize();
        return *this;
    }

    bool Checkbox::getBorder()
    {
        return _border;
    }

    Checkbox& Checkbox::setIndeterminate(bool indeterminate)
    {
        QCheckBox::setCheckState(indeterminate ?
                Qt::CheckState::PartiallyChecked : Qt::CheckState::Unchecked);
        return *this;
    }

    bool Checkbox::getIndeterminate()
    {
        return QCheckBox::checkState() == Qt::CheckState::PartiallyChecked;
    }

    #if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
void Checkbox::enterEvent(QEnterEvent* event)
#else
void Checkbox::enterEvent(QEvent* event)
#endif
    {
        if (!isEnabled())
            QApplication::setOverrideCursor(Qt::ForbiddenCursor);
        QCheckBox::enterEvent(event);
    }

    void Checkbox::leaveEvent(QEvent* event)
    {
        if (!isEnabled())
            QApplication::restoreOverrideCursor();
        QCheckBox::leaveEvent(event);
    }


    CheckboxGroup::CheckboxGroup(QWidget* parent)
        : CheckboxGroup({}, parent)
    {}

    CheckboxGroup::CheckboxGroup(const QList<Checkbox*>& checkboxs, QWidget* parent)
        : QGroupBox(parent)
        , _checkboxs(checkboxs)
        , _layout(new QHBoxLayout(this))
    {
        setTitle("");

        _layout->setContentsMargins(15, 5, 15, 5);
        _layout->setSpacing(20);

        for (auto* checkbox : checkboxs)
            addCheckbox(checkbox);

        setStyleSheet("QGroupBox { border: none; }");
    }

    CheckboxGroup& CheckboxGroup::addCheckbox(Checkbox* checkbox)
    {
        _checkboxs.append(checkbox);
        connect(checkbox, &QCheckBox::stateChanged, this, &CheckboxGroup::onStateChanged);

        _layout->addWidget(checkbox);
        adjustSize();
        return *this;
    }

    CheckboxGroup& CheckboxGroup::setTitle(const QString&)
    {
        QGroupBox::setTitle("");
        return *this;
    }

    CheckboxGroup& CheckboxGroup::setSize(Size size)
    {
        _size = size;

        for (auto* checkbox : _checkboxs)
            checkbox->setSize(static_cast<Checkbox::Size>(_size));

        adjustSize();
        return *this;
    }

    CheckboxGroup::Size CheckboxGroup::getSize()
    {
        return _size;
    }

    CheckboxGroup& CheckboxGroup::setDisabled(bool disabled)
    {
        QGroupBox::setEnabled(!disabled);
        return *this;
    }

    bool CheckboxGroup::isDisabled()
    {
        return !QGroupBox::isEnabled();
    }

    CheckboxGroup& CheckboxGroup::setMin(int min)
    {
        _min = qMax(0, min);
        onStateChanged();
        return *this;
    }

    int CheckboxGroup::getMin()
    {
        return _min;
    }

    CheckboxGroup& CheckboxGroup::setMax(int max)
    {
        _max = qMax(0, max);
        onStateChanged();
        return *this;
    }

    int CheckboxGroup::getMax()
    {
        return _max;
    }

    void CheckboxGroup::onStateChanged()
    {
        if (_min == 0 && _max == 0)
            return;

        int checkedCount = countChecked();

        if (_max > 0 && checkedCount == _max)
        {
            for (auto* checkbox : _checkboxs)
                checkbox->setDisabled(!checkbox->isChecked());
        }

        if (_min > 0 && checkedCount == _min)
        {
            for (auto* checkbox : _checkboxs)
                checkbox->setDisabled(checkbox->isChecked());
        }
    }

    int CheckboxGroup::countChecked()
    {
        int cnt = 0;
        for (auto* checkbox : _checkboxs)
        {
            if (checkbox->isChecked())
                cnt++;
        }
        return cnt;
    }

}
