#pragma once

#include "private/utils.h"

#include <QRadioButton>
#include <QGroupBox>
#include <QBoxLayout>

namespace Element
{
    class Radio : public QRadioButton
    {
    Q_OBJECT

    public:
        enum class Size { Large, Default, Small };

    public:
        Radio& setValue(const QVariant& value);
        QVariant getValue();

        Radio& setText(const QString& text);
        QString getText();

        Radio& setDisabled(bool disabled);
        bool isDisabled();

        Radio& setSize(Size size);
        Size getSize();

        Radio& setChecked(bool checked);
        bool getChecked();

        Radio& setBorder(bool border);
        bool getBorder();

    public:
        Radio(QWidget* parent = nullptr);
        Radio(const QString& text, QWidget* parent = nullptr);
        Radio(const QString& text, bool checked, QWidget* parent = nullptr);

    private:
        void onStateChanged();

    protected:
        void enterEvent(QEvent* event) override;
        void leaveEvent(QEvent* event) override;

    private:
        QVariant _value;
        Size _size = Size::Default;
        bool _border = false;

    private:
        QSSHelper _qsshelper;
    };

    class RadioGroup : public QGroupBox
    {
    Q_OBJECT

    public:
        enum class Size { Large, Default, Small };

    public:
        RadioGroup& setSize(Size size);
        Size getSize();

        RadioGroup& setDisabled(bool disabled);
        bool isDisabled();

        RadioGroup& addRadio(Radio* radio);
        RadioGroup& setTitle(const QString&);

    public:
        RadioGroup(QWidget* parent = nullptr);
        RadioGroup(const QList<Radio*>& radios, QWidget* parent = nullptr);

    private:
        Size _size = Size::Default;

    private:
        QList<Radio*> _radios;
        QHBoxLayout* _layout = nullptr;
    };

}
