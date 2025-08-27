#pragma once

#include "iconmanager.h"
#include "qsshelper.h"

#include <QLineEdit>
#include <functional>
#include <QLabel>

namespace QTElementUI
{
    class Input : public QLineEdit
    {
    Q_OBJECT

    public:
        enum class Size
        {
            default_ = 0,
            large,
            small,
        };

    public:
        QString getPlaceholder();
        Input& setPlaceholder(const QString& placeholder);

        int getWidth();
        Input& setWidth(int width);

        bool getDisabled();
        Input& setDisabled(bool disabled);

        Size getSize();
        Input& setSize(Size size);

        Icon getSuffixIcon();
        Input& setSuffixIcon(Icon icon);
        Input& setSuffixIcon(Icon icon, const std::function<void()>& callback);

        Icon getPrefixIcon();
        Input& setPrefixIcon(Icon icon);
        Input& setPrefixIcon(Icon icon, const std::function<void()>& callback);

        int getMaxLength();
        Input& setMaxLength(int maxLength);

        bool getClearable();
        Input& setClearable(bool clearable);

        bool getShowPassword();
        Input& setShowPassword(bool showPassword);

        bool getReadonly();
        Input& setReadonly(bool readonly);

        bool getResize();
        Input& setResize(bool resize);

        bool getAutofocus();
        Input& setAutofocus(bool autofocus);

        // TODO: validate

    public:
        Input(QWidget* parent = nullptr);
        Input(const QString& placeholder, QWidget* parent = nullptr);

    private:
        Size _size = Size::default_;

        Icon _suffixIcon = Icon::None;
        Icon _prefixIcon = Icon::None;

        bool _clearable = false;
        bool _showPassword = false;
        bool _readonly = false;
        bool _resize = false;
        bool _autofocus = false;

        int _maxLength = 0;

    private:
        QSSHelper _qssHelper;

        QAction* _prefixAction = nullptr;
        QAction* _suffixAction = nullptr;

        QLabel* _maxLengthLabel = nullptr;

        bool _isPrefixHovered = false;
        bool _isSuffixHovered = false;

    private:
        void clearableChecker();
        void showPasswordChecker();
        void maxLengthChecker();

    protected:
        void onTextChanged(const QString &text);

        void focusInEvent(QFocusEvent *event) override;
        void focusOutEvent(QFocusEvent *event) override;
        void enterEvent(QEvent *event) override;
        void leaveEvent(QEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;
    };
}
