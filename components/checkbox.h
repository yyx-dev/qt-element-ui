#pragma once

#include "private/utils.h"

#include <QCheckBox>
#include <QGroupBox>
#include <QBoxLayout>

namespace Element
{
    class CheckboxGroup;

    class Checkbox : public QCheckBox
    {
    Q_OBJECT

    public:
        enum class Size { Large, Default, Small };

    public:
        Checkbox& setValue(const QVariant& value);
        QVariant getValue();

        Checkbox& setText(const QString& text);
        QString getText();

        Checkbox& setDisabled(bool disabled);
        bool isDisabled();

        Checkbox& setSize(Size size);
        Size getSize();

        Checkbox& setChecked(bool checked);
        bool getChecked();

        Checkbox& setBorder(bool border);
        bool getBorder();

        Checkbox& setIndeterminate(bool indeterminate);
        bool getIndeterminate();

    public:
        Checkbox(QWidget* parent = nullptr);
        Checkbox(const QString& text, QWidget* parent = nullptr);
        Checkbox(const QString& text, bool checked, QWidget* parent = nullptr);

    private:
        void onStateChanged();

    protected:
        #if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    void enterEvent(QEnterEvent* event) override;
#else
    void enterEvent(QEvent* event) override;
#endif
        void leaveEvent(QEvent* event) override;

    private:
        QVariant _value;
        Size _size = Size::Default;
        bool _border = false;

    private:
        CheckboxGroup* _controlGroup = nullptr;
        QSSHelper _qsshelper;
    };

    class CheckboxGroup : public QGroupBox
    {
    Q_OBJECT

    public:
        enum class Size { Large, Default, Small };

    public:
        CheckboxGroup& setSize(Size size);
        Size getSize();

        CheckboxGroup& setDisabled(bool disabled);
        bool isDisabled();

        CheckboxGroup& setMin(int min);
        int getMin();

        CheckboxGroup& setMax(int max);
        int getMax();

        CheckboxGroup& addCheckbox(Checkbox* checkbox);
        CheckboxGroup& setTitle(const QString& text);

    public:
        CheckboxGroup(QWidget* parent = nullptr);
        CheckboxGroup(const QList<Checkbox*>& checkboxs, QWidget* parent = nullptr);

    private:
        void onStateChanged();
        int countChecked();

    private:
        Size _size = Size::Default;
        int _min = 0, _max = 0;

    private:
        QList<Checkbox*> _checkboxs;
        QHBoxLayout* _layout = nullptr;
    };

}
