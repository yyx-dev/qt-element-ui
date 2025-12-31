#pragma once

#include "private/utils.h"
#include "icon.h"

#include <QLineEdit>
#include <QLabel>

#include <functional>

namespace Element
{
    class InputLine : public QLineEdit
    {
    Q_OBJECT

    public:
        enum class Size
        {
            Large = 0,
            Default,
            Small,
        };

    public:
        QString getPlaceholder();
        InputLine& setPlaceholder(const QString& placeholder);

        int getWidth();
        InputLine& setWidth(int width);

        bool isDisabled();
        InputLine& setDisabled(bool disabled);

        Size getSize();
        InputLine& setSize(Size size);

        Icon::Name getSuffixIcon();
        InputLine& setSuffixIcon(Icon::Name icon);
        InputLine& setSuffixIcon(Icon::Name icon, const std::function<void()>& callback);

        Icon::Name getPrefixIcon();
        InputLine& setPrefixIcon(Icon::Name icon);
        InputLine& setPrefixIcon(Icon::Name icon, const std::function<void()>& callback);

        int getMaxLength();
        InputLine& setMaxLength(int maxLength);

        bool getClearable();
        InputLine& setClearable(bool clearable);

        bool getShowPassword();
        InputLine& setShowPassword(bool showPassword);

        bool getReadOnly();
        InputLine& setReadOnly(bool readonly);

        InputLine& setAutoFocus();

        // TODO: validate

    public:
        InputLine(QWidget* parent = nullptr);
        InputLine(const QString& placeholder, QWidget* parent = nullptr);

    protected:
        void onTextChanged(const QString &text);

        void focusInEvent(QFocusEvent *event) override;
        void focusOutEvent(QFocusEvent *event) override;
        #if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    void enterEvent(QEnterEvent* event) override;
#else
    void enterEvent(QEvent* event) override;
#endif
        void leaveEvent(QEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;

    private:
        void clearableChecker();
        void showPasswordChecker();
        void maxLengthChecker();
        QString placeholderText();

    private:
        Size _size = Size::Default;

        Icon::Name _suffixIcon = Icon::None;
        Icon::Name _prefixIcon = Icon::None;

        bool _clearable = false;
        bool _showPassword = false;

        int _maxLength = 0;

    private:
        QSSHelper _qssHelper;

        QAction* _prefixAction = nullptr;
        QAction* _suffixAction = nullptr;

        QLabel* _maxLengthLabel = nullptr;

        bool _isPrefixHovered = false;
        bool _isSuffixHovered = false;

        int _iconSize = 20;
    };
}
