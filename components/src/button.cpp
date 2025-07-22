#include "../include/button.h"
#include "../../tools/include/commvar.h"
#include "../../tools/include/iconmanager.h"

namespace QTElementUI
{

    Button::Button(QWidget* parent)
        : QPushButton(parent)
    {
        QFont font;
        font.setStyleStrategy(QFont::PreferAntialias);
        font.setFamily(CommonVar::baseFontFmaily);
        font.setPointSize(CommonVar::defaultFontSize);
        QPushButton::setFont(font);

        QPalette palette = QPushButton::palette();
        palette.setColor(QPalette::ButtonText, Color::regularText());

        QString defaultButtonQSS = R"(
            QPushButton {
                padding: 8px 15px;
                font-size: 16px;
                font-weight: bold;
            }
        )";

        _qsshelper = defaultButtonQSS;
        QPushButton::setStyleSheet(defaultButtonQSS);

        setStyle(Button::Style::default_);
        setType(Button::Type::default_);
        setSize(Button::Size::default_);

        setMinimumHeight(40);
    }

    Button::Button(const QString& text, QWidget* parent)
        : Button(parent)
    {
        QPushButton::setText(text);
    }

    Button::Style Button::getStyle()
    {
        return _style;
    }

    Button& Button::setStyle(Style style)
    {
        _style = style;
        if (_style == Style::default_)
        {
            _qsshelper.setProperty("QPushButton", "border-radius", "4px");
            _qsshelper.setProperty("QPushButton", "border", "1px solid");
            _qsshelper.setProperty("QPushButton", "color", Color::regularText());
        }
        else if (_style == Style::plain)
        {
            ;
        }
        else if (_style == Style::round)
        {
            _qsshelper.setProperty("QPushButton", "border-radius", "20px");
        }
        else if (_style == Style::circle)
        {
            _qsshelper.setProperty("QPushButton", "border-radius", "20px");
            _qsshelper.setProperty("QPushButton", "padding", "8px");

            setMinimumSize(40, 40);
            setMaximumSize(40, 40);
        }

        QPushButton::setStyleSheet(_qsshelper.generate());
        return *this;
    }

    Button::Type Button::getType()
    {
        return _type;
    }

    Button& Button::setType(Type type)
    {
        _type = type;

        if (_style == Style::default_)
        {
            if (_type == Type::default_)
            {
                _qsshelper.setProperty("QPushButton", "background-color", Color::baseBackground());
                _qsshelper.setProperty("QPushButton", "border", "1px solid " + Color::baseBorder());
                _qsshelper.setProperty("QPushButton", "color", Color::regularText());
                _qsshelper.setProperty("QPushButton:hover", "background-color", Color::primaryL5());
                _qsshelper.setProperty("QPushButton:hover", "border", "1px solid " + Color::primaryL3());
                _qsshelper.setProperty("QPushButton:hover", "color", Color::primary());
                _qsshelper.setProperty("QPushButton:pressed", "border", "1px solid " + Color::primary());
                _qsshelper.setProperty("QPushButton:disabled", "background-color", Color::baseBackground());
                _qsshelper.setProperty("QPushButton:disabled", "border", "1px solid " + Color::lightBorder());
                _qsshelper.setProperty("QPushButton:disabled", "color", Color::placeholderText());
            }
            else if (_type == Type::primary)
            {
                _qsshelper.setProperty("QPushButton", "background-color", Color::primary());
                _qsshelper.setProperty("QPushButton", "border", "1px solid " + Color::primary());
                _qsshelper.setProperty("QPushButton", "color", Color::blankFill());
                _qsshelper.setProperty("QPushButton:hover", "background-color", Color::primaryL1());
                _qsshelper.setProperty("QPushButton:hover", "border", "1px solid " + Color::primaryL1());
                _qsshelper.setProperty("QPushButton:hover", "color", Color::blankFill());
                _qsshelper.setProperty("QPushButton:pressed", "background-color", Color::primaryD1());
                _qsshelper.setProperty("QPushButton:pressed", "border", "1px solid " + Color::primaryD1());
                _qsshelper.setProperty("QPushButton:pressed", "color", Color::blankFill());
                _qsshelper.setProperty("QPushButton:disabled", "background-color", Color::primaryL2());
                _qsshelper.setProperty("QPushButton:disabled", "border", "1px solid " + Color::primaryL2());
                _qsshelper.setProperty("QPushButton:disabled", "color", Color::blankFill());
            }
            else if (_type == Type::success)
            {
                _qsshelper.setProperty("QPushButton", "background-color", Color::success());
                _qsshelper.setProperty("QPushButton", "border", "1px solid " + Color::success());
                _qsshelper.setProperty("QPushButton", "color", Color::blankFill());
                _qsshelper.setProperty("QPushButton:hover", "background-color", Color::successL1());
                _qsshelper.setProperty("QPushButton:hover", "border", "1px solid " + Color::successL1());
                _qsshelper.setProperty("QPushButton:hover", "color", Color::blankFill());
                _qsshelper.setProperty("QPushButton:pressed", "background-color", Color::successD1());
                _qsshelper.setProperty("QPushButton:pressed", "border", "1px solid " + Color::successD1());
                _qsshelper.setProperty("QPushButton:pressed", "color", Color::blankFill());
                _qsshelper.setProperty("QPushButton:disabled", "background-color", Color::successL2());
                _qsshelper.setProperty("QPushButton:disabled", "border", "1px solid " + Color::successL2());
                _qsshelper.setProperty("QPushButton:disabled", "color", Color::blankFill());
            }
            else if (_type == Type::info)
            {
                _qsshelper.setProperty("QPushButton", "background-color", Color::info());
                _qsshelper.setProperty("QPushButton", "border", "1px solid " + Color::info());
                _qsshelper.setProperty("QPushButton", "color", Color::blankFill());
                _qsshelper.setProperty("QPushButton:hover", "background-color", Color::infoL1());
                _qsshelper.setProperty("QPushButton:hover", "border", "1px solid " + Color::infoL1());
                _qsshelper.setProperty("QPushButton:hover", "color", Color::blankFill());
                _qsshelper.setProperty("QPushButton:pressed", "background-color", Color::infoD1());
                _qsshelper.setProperty("QPushButton:pressed", "border", "1px solid " + Color::infoD1());
                _qsshelper.setProperty("QPushButton:pressed", "color", Color::blankFill());
                _qsshelper.setProperty("QPushButton:disabled", "background-color", Color::infoL2());
                _qsshelper.setProperty("QPushButton:disabled", "border", "1px solid " + Color::infoL2());
                _qsshelper.setProperty("QPushButton:disabled", "color", Color::blankFill());
            }
            else if (_type == Type::warning)
            {
                _qsshelper.setProperty("QPushButton", "background-color", Color::warning());
                _qsshelper.setProperty("QPushButton", "border", "1px solid " + Color::warning());
                _qsshelper.setProperty("QPushButton", "color", Color::blankFill());
                _qsshelper.setProperty("QPushButton:hover", "background-color", Color::warningL1());
                _qsshelper.setProperty("QPushButton:hover", "border", "1px solid " + Color::warningL1());
                _qsshelper.setProperty("QPushButton:hover", "color", Color::blankFill());
                _qsshelper.setProperty("QPushButton:pressed", "background-color", Color::warningD1());
                _qsshelper.setProperty("QPushButton:pressed", "border", "1px solid " + Color::warningD1());
                _qsshelper.setProperty("QPushButton:pressed", "color", Color::blankFill());
                _qsshelper.setProperty("QPushButton:disabled", "background-color", Color::warningL2());
                _qsshelper.setProperty("QPushButton:disabled", "border", "1px solid " + Color::warningL2());
                _qsshelper.setProperty("QPushButton:disabled", "color", Color::blankFill());
            }
            else if (_type == Type::danger)
            {
                _qsshelper.setProperty("QPushButton", "background-color", Color::danger());
                _qsshelper.setProperty("QPushButton", "border", "1px solid " + Color::danger());
                _qsshelper.setProperty("QPushButton", "color", Color::blankFill());
                _qsshelper.setProperty("QPushButton:hover", "background-color", Color::dangerL1());
                _qsshelper.setProperty("QPushButton:hover", "border", "1px solid " + Color::dangerL1());
                _qsshelper.setProperty("QPushButton:hover", "color", Color::blankFill());
                _qsshelper.setProperty("QPushButton:pressed", "background-color", Color::dangerD1());
                _qsshelper.setProperty("QPushButton:pressed", "border", "1px solid " + Color::dangerD1());
                _qsshelper.setProperty("QPushButton:pressed", "color", Color::blankFill());
                _qsshelper.setProperty("QPushButton:disabled", "background-color", Color::dangerL2());
                _qsshelper.setProperty("QPushButton:disabled", "border", "1px solid " + Color::dangerL2());
                _qsshelper.setProperty("QPushButton:disabled", "color", Color::blankFill());
            }
        }
        else if (_style == Style::plain)
        {
            if (_type == Type::default_)
            {
                _qsshelper.setProperty("QPushButton", "background-color", Color::baseBackground());
                _qsshelper.setProperty("QPushButton", "border", "1px solid " + Color::baseBorder());
                _qsshelper.setProperty("QPushButton", "color", Color::regularText());
                _qsshelper.setProperty("QPushButton:hover", "background-color", Color::baseBackground());
                _qsshelper.setProperty("QPushButton:hover", "border", "1px solid " + Color::primary());
                _qsshelper.setProperty("QPushButton:hover", "color", Color::primary());
                _qsshelper.setProperty("QPushButton:pressed", "background-color", Color::baseBackground());
                _qsshelper.setProperty("QPushButton:pressed", "border", "1px solid " + Color::primary());
                _qsshelper.setProperty("QPushButton:pressed", "color", Color::primary());
                _qsshelper.setProperty("QPushButton:disabled", "background-color", Color::baseBackground());
                _qsshelper.setProperty("QPushButton:disabled", "border", "1px solid " + Color::lightBorder());
                _qsshelper.setProperty("QPushButton:disabled", "color", Color::placeholderText());
            }
            else if (_type == Type::primary)
            {
                _qsshelper.setProperty("QPushButton", "background-color", Color::primaryL5());
                _qsshelper.setProperty("QPushButton", "border", "1px solid " + Color::primaryL2());
                _qsshelper.setProperty("QPushButton", "color", Color::primary());
                _qsshelper.setProperty("QPushButton:hover", "background-color", Color::primary());
                _qsshelper.setProperty("QPushButton:hover", "border", "1px solid " + Color::primary());
                _qsshelper.setProperty("QPushButton:hover", "color", Color::blankFill());
                _qsshelper.setProperty("QPushButton:pressed", "background-color", Color::primaryD1());
                _qsshelper.setProperty("QPushButton:pressed", "border", "1px solid " + Color::primaryD1());
                _qsshelper.setProperty("QPushButton:pressed", "color", Color::blankFill());
                _qsshelper.setProperty("QPushButton:disabled", "background-color", Color::primaryL5());
                _qsshelper.setProperty("QPushButton:disabled", "border", "1px solid " + Color::primaryL4());
                _qsshelper.setProperty("QPushButton:disabled", "color", Color::primaryL2());
            }
            else if (_type == Type::success)
            {
                _qsshelper.setProperty("QPushButton", "background-color", Color::successL5());
                _qsshelper.setProperty("QPushButton", "border", "1px solid " + Color::successL2());
                _qsshelper.setProperty("QPushButton", "color", Color::success());
                _qsshelper.setProperty("QPushButton:hover", "background-color", Color::success());
                _qsshelper.setProperty("QPushButton:hover", "border", "1px solid " + Color::success());
                _qsshelper.setProperty("QPushButton:hover", "color", Color::blankFill());
                _qsshelper.setProperty("QPushButton:pressed", "background-color", Color::successD1());
                _qsshelper.setProperty("QPushButton:pressed", "border", "1px solid " + Color::successD1());
                _qsshelper.setProperty("QPushButton:pressed", "color", Color::blankFill());
                _qsshelper.setProperty("QPushButton:disabled", "background-color", Color::successL5());
                _qsshelper.setProperty("QPushButton:disabled", "border", "1px solid " + Color::successL4());
                _qsshelper.setProperty("QPushButton:disabled", "color", Color::successL2());
            }
            else if (_type == Type::info)
            {
                _qsshelper.setProperty("QPushButton", "background-color", Color::infoL5());
                _qsshelper.setProperty("QPushButton", "border", "1px solid " + Color::infoL2());
                _qsshelper.setProperty("QPushButton", "color", Color::info());
                _qsshelper.setProperty("QPushButton:hover", "background-color", Color::info());
                _qsshelper.setProperty("QPushButton:hover", "border", "1px solid " + Color::info());
                _qsshelper.setProperty("QPushButton:hover", "color", Color::blankFill());
                _qsshelper.setProperty("QPushButton:pressed", "background-color", Color::infoD1());
                _qsshelper.setProperty("QPushButton:pressed", "border", "1px solid " + Color::infoD1());
                _qsshelper.setProperty("QPushButton:pressed", "color", Color::blankFill());
                _qsshelper.setProperty("QPushButton:disabled", "background-color", Color::infoL5());
                _qsshelper.setProperty("QPushButton:disabled", "border", "1px solid " + Color::infoL4());
                _qsshelper.setProperty("QPushButton:disabled", "color", Color::infoL2());
            }
            else if (_type == Type::warning)
            {
                _qsshelper.setProperty("QPushButton", "background-color", Color::warningL5());
                _qsshelper.setProperty("QPushButton", "border", "1px solid " + Color::warningL2());
                _qsshelper.setProperty("QPushButton", "color", Color::warning());
                _qsshelper.setProperty("QPushButton:hover", "background-color", Color::warning());
                _qsshelper.setProperty("QPushButton:hover", "border", "1px solid " + Color::warning());
                _qsshelper.setProperty("QPushButton:hover", "color", Color::blankFill());
                _qsshelper.setProperty("QPushButton:pressed", "background-color", Color::warningD1());
                _qsshelper.setProperty("QPushButton:pressed", "border", "1px solid " + Color::warningD1());
                _qsshelper.setProperty("QPushButton:pressed", "color", Color::blankFill());
                _qsshelper.setProperty("QPushButton:disabled", "background-color", Color::warningL5());
                _qsshelper.setProperty("QPushButton:disabled", "border", "1px solid " + Color::warningL4());
                _qsshelper.setProperty("QPushButton:disabled", "color", Color::warningL2());
            }
            else if (_type == Type::danger)
            {
                _qsshelper.setProperty("QPushButton", "background-color", Color::dangerL5());
                _qsshelper.setProperty("QPushButton", "border", "1px solid " + Color::dangerL2());
                _qsshelper.setProperty("QPushButton", "color", Color::danger());
                _qsshelper.setProperty("QPushButton:hover", "background-color", Color::danger());
                _qsshelper.setProperty("QPushButton:hover", "border", "1px solid " + Color::danger());
                _qsshelper.setProperty("QPushButton:hover", "color", Color::blankFill());
                _qsshelper.setProperty("QPushButton:pressed", "background-color", Color::dangerD1());
                _qsshelper.setProperty("QPushButton:pressed", "border", "1px solid " + Color::dangerD1());
                _qsshelper.setProperty("QPushButton:pressed", "color", Color::blankFill());
                _qsshelper.setProperty("QPushButton:disabled", "background-color", Color::dangerL5());
                _qsshelper.setProperty("QPushButton:disabled", "border", "1px solid " + Color::dangerL4());
                _qsshelper.setProperty("QPushButton:disabled", "color", Color::dangerL2());
            }
        }
        else if (_style == Style::round || _style == Style::circle)
        {
            if (_type == Type::default_)
            {
                _qsshelper.setProperty("QPushButton", "background-color", Color::baseBackground());
                _qsshelper.setProperty("QPushButton", "border", "1px solid " + Color::baseBorder());
                _qsshelper.setProperty("QPushButton", "color", Color::regularText());
                _qsshelper.setProperty("QPushButton:hover", "background-color", Color::primaryL5());
                _qsshelper.setProperty("QPushButton:hover", "border", "1px solid " + Color::primaryL3());
                _qsshelper.setProperty("QPushButton:hover", "color", Color::primary());
                _qsshelper.setProperty("QPushButton:pressed", "background-color", Color::primaryL5());
                _qsshelper.setProperty("QPushButton:pressed", "border", "1px solid " + Color::primary());
                _qsshelper.setProperty("QPushButton:pressed", "color", Color::primary());
                _qsshelper.setProperty("QPushButton:disabled", "background-color", Color::baseBackground());
                _qsshelper.setProperty("QPushButton:disabled", "border", "1px solid " + Color::lightBorder());
                _qsshelper.setProperty("QPushButton:disabled", "color", Color::placeholderText());
            }
            else if (_type == Type::primary)
            {
                _qsshelper.setProperty("QPushButton", "background-color", Color::primary());
                _qsshelper.setProperty("QPushButton", "border", "1px solid " + Color::primary());
                _qsshelper.setProperty("QPushButton", "color", Color::blankFill());
                _qsshelper.setProperty("QPushButton:hover", "background-color", Color::primaryL1());
                _qsshelper.setProperty("QPushButton:hover", "border", "1px solid " + Color::primaryL1());
                _qsshelper.setProperty("QPushButton:hover", "color", Color::blankFill());
                _qsshelper.setProperty("QPushButton:pressed", "background-color", Color::primaryD1());
                _qsshelper.setProperty("QPushButton:pressed", "border", "1px solid " + Color::primaryD1());
                _qsshelper.setProperty("QPushButton:pressed", "color", Color::blankFill());
                _qsshelper.setProperty("QPushButton:disabled", "background-color", Color::primaryL2());
                _qsshelper.setProperty("QPushButton:disabled", "border", "1px solid " + Color::primaryL2());
                _qsshelper.setProperty("QPushButton:disabled", "color", Color::blankFill());
            }
            else if (_type == Type::success)
            {
                _qsshelper.setProperty("QPushButton", "background-color", Color::success());
                _qsshelper.setProperty("QPushButton", "border", "1px solid " + Color::success());
                _qsshelper.setProperty("QPushButton", "color", Color::blankFill());
                _qsshelper.setProperty("QPushButton:hover", "background-color", Color::successL1());
                _qsshelper.setProperty("QPushButton:hover", "border", "1px solid " + Color::successL1());
                _qsshelper.setProperty("QPushButton:hover", "color", Color::blankFill());
                _qsshelper.setProperty("QPushButton:pressed", "background-color", Color::successD1());
                _qsshelper.setProperty("QPushButton:pressed", "border", "1px solid " + Color::successD1());
                _qsshelper.setProperty("QPushButton:pressed", "color", Color::blankFill());
                _qsshelper.setProperty("QPushButton:disabled", "background-color", Color::successL2());
                _qsshelper.setProperty("QPushButton:disabled", "border", "1px solid " + Color::successL2());
                _qsshelper.setProperty("QPushButton:disabled", "color", Color::blankFill());
            }
            else if (_type == Type::info)
            {
                _qsshelper.setProperty("QPushButton", "background-color", Color::info());
                _qsshelper.setProperty("QPushButton", "border", "1px solid " + Color::info());
                _qsshelper.setProperty("QPushButton", "color", Color::blankFill());
                _qsshelper.setProperty("QPushButton:hover", "background-color", Color::infoL1());
                _qsshelper.setProperty("QPushButton:hover", "border", "1px solid " + Color::infoL1());
                _qsshelper.setProperty("QPushButton:hover", "color", Color::blankFill());
                _qsshelper.setProperty("QPushButton:pressed", "background-color", Color::infoD1());
                _qsshelper.setProperty("QPushButton:pressed", "border", "1px solid " + Color::infoD1());
                _qsshelper.setProperty("QPushButton:pressed", "color", Color::blankFill());
                _qsshelper.setProperty("QPushButton:disabled", "background-color", Color::infoL2());
                _qsshelper.setProperty("QPushButton:disabled", "border", "1px solid " + Color::infoL2());
                _qsshelper.setProperty("QPushButton:disabled", "color", Color::blankFill());
            }
            else if (_type == Type::warning)
            {
                _qsshelper.setProperty("QPushButton", "background-color", Color::warning());
                _qsshelper.setProperty("QPushButton", "border", "1px solid " + Color::warning());
                _qsshelper.setProperty("QPushButton", "color", Color::blankFill());
                _qsshelper.setProperty("QPushButton:hover", "background-color", Color::warningL1());
                _qsshelper.setProperty("QPushButton:hover", "border", "1px solid " + Color::warningL1());
                _qsshelper.setProperty("QPushButton:hover", "color", Color::blankFill());
                _qsshelper.setProperty("QPushButton:pressed", "background-color", Color::warningD1());
                _qsshelper.setProperty("QPushButton:pressed", "border", "1px solid " + Color::warningD1());
                _qsshelper.setProperty("QPushButton:pressed", "color", Color::blankFill());
                _qsshelper.setProperty("QPushButton:disabled", "background-color", Color::warningL2());
                _qsshelper.setProperty("QPushButton:disabled", "border", "1px solid " + Color::warningL2());
                _qsshelper.setProperty("QPushButton:disabled", "color", Color::blankFill());
            }
            else if (_type == Type::danger)
            {
                _qsshelper.setProperty("QPushButton", "background-color", Color::danger());
                _qsshelper.setProperty("QPushButton", "border", "1px solid " + Color::danger());
                _qsshelper.setProperty("QPushButton", "color", Color::blankFill());
                _qsshelper.setProperty("QPushButton:hover", "background-color", Color::dangerL1());
                _qsshelper.setProperty("QPushButton:hover", "border", "1px solid " + Color::dangerL1());
                _qsshelper.setProperty("QPushButton:hover", "color", Color::blankFill());
                _qsshelper.setProperty("QPushButton:pressed", "background-color", Color::dangerD1());
                _qsshelper.setProperty("QPushButton:pressed", "border", "1px solid " + Color::dangerD1());
                _qsshelper.setProperty("QPushButton:pressed", "color", Color::blankFill());
                _qsshelper.setProperty("QPushButton:disabled", "background-color", Color::dangerL2());
                _qsshelper.setProperty("QPushButton:disabled", "border", "1px solid " + Color::dangerL2());
                _qsshelper.setProperty("QPushButton:disabled", "color", Color::blankFill());
            }
        }

        QPushButton::setStyleSheet(_qsshelper.generate());
        return *this;
    }

    Button::Size Button::getSize()
    {
        return _size;
    }

    Button& Button::setSize(Button::Size size)
    {
        _size = size;

        if (_size == Size::large)
        {
            _qsshelper.setProperty("QPushButton", "padding", "12px 19px");

            setMinimumHeight(50);
        }
        else if (_size == Size::small)
        {
            _qsshelper.setProperty("QPushButton", "border-radius", "2px");
            _qsshelper.setProperty("QPushButton", "padding", "5px 11px");
            _qsshelper.setProperty("QPushButton", "font-size", "14px");

            if (!_icon.isEmpty())
                QPushButton::setIconSize(QSize(_smallIconSize, _smallIconSize));

            setMinimumHeight(30);
        }

        QPushButton::setStyleSheet(_qsshelper.generate());
        return *this;
    }


    bool Button::getDisabled()
    {
        return _disabled;
    }

    Button& Button::setDisabled(bool disabled)
    {
        _disabled = disabled;
        QPushButton::setDisabled(disabled);
        return *this;
    }

    bool Button::getLoading()
    {
        return _loading;
    }

    Button& Button::setLoading(bool loading)
    {
        _loading = loading;
        return *this;
    }

    QPair<QString, Button::IconPosition> Button::getIcon()
    {
        return QPair<QString, Button::IconPosition>(_icon, _iconPostion);
    }

    Button& Button::setIcon(const QString& name, IconPosition pos)
    {
        _icon = name;
        _iconPostion = pos;

        if (_type == Type::default_)
        {
            QIcon icon = IconManager::instance().getIcon(name, Color::regularText());
            QPushButton::setIcon(icon);
            QPushButton::setIconSize(QSize(_iconSize, _iconSize));
        }
        else
        {
            QIcon icon = IconManager::instance().getIcon(name, Color::blankFill());
            QPushButton::setIcon(icon);
            QPushButton::setIconSize(QSize(_iconSize, _iconSize));
        }

        if (pos == IconPosition::only)
        {
            QPushButton::setText("");
        }
        else if (pos == IconPosition::left)
        {
            ;
        }
        else if (pos == IconPosition::right)
        {
            QPushButton::setLayoutDirection(Qt::RightToLeft);
        }

        adjustSize();
        return *this;
    }

    Button& Button::setText(const QString& text)
    {
        QPushButton::setText(text);

        adjustSize();
        return *this;
    }


    void Button::enterEvent(QEvent *event)
    {
        if (!isEnabled())
            QApplication::setOverrideCursor(Qt::ForbiddenCursor);

        QPushButton::enterEvent(event);
    }

    void Button::leaveEvent(QEvent *event)
    {
        QApplication::restoreOverrideCursor();
        QPushButton::leaveEvent(event);
    }
}
