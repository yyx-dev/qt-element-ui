#include "button.h"
#include "color.h"
#include "icon.h"
#include "base.h"



#include <QApplication>

using namespace std;

namespace Element
{

    Button::Button(QWidget* parent)
        : QPushButton(parent)
    {
        QPalette palette = QPushButton::palette();
        palette.setColor(QPalette::ButtonText, Color::regularText());

        _qsshelper = QString(R"(
             QPushButton {
                 padding: 8px 15px;
                 font-size: 16px;
                 font-weight: bold;
             }
         )");
        _qsshelper.setProperty("QPushButton", "font-family", Comm::fontFmaily);
        QPushButton::setStyleSheet(_qsshelper.generate());

        setStyle(Button::Style::Default);
        setType(Button::Type::Default);
        setSize(Button::Size::Default);

        setCursor(Qt::PointingHandCursor);
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

        if (style == Style::Default)
        {
            _qsshelper.setProperty("QPushButton", "border-radius", "4px");
            _qsshelper.setProperty("QPushButton", "border", "1px solid");
            _qsshelper.setProperty("QPushButton", "color", Color::regularText());
        }
        else if (style == Style::Plain)
        {
            ;
        }
        else if (style == Style::Round)
        {
            _qsshelper.setProperty("QPushButton", "border-radius", "20px");
        }
        else if (style == Style::Circle)
        {
            _qsshelper.setProperty("QPushButton", "border-radius", "20px");
            _qsshelper.setProperty("QPushButton", "padding", "8px");

            setMinimumSize(40, 40);
            setMaximumSize(40, 40);
        }
        else if (style == Style::Link)
        {
            _qsshelper.setProperty("QPushButton", "padding", "0px");
            _qsshelper.setProperty("QPushButton", "border", "none");
            _qsshelper.setProperty("QPushButton", "background", "transparent");
            _qsshelper.setProperty("QPushButton:hover", "border", "none");
            _qsshelper.setProperty("QPushButton:hover", "background", "transparent");
            _qsshelper.setProperty("QPushButton:hover", "text-decoration", "underline");
        }
        else if (style == Style::Text)
        {
            _qsshelper.setProperty("QPushButton", "border", "none");
            _qsshelper.setProperty("QPushButton:hover", "background", Color::lightFill());
            _qsshelper.setProperty("QPushButton:pressed", "background", Color::pageBackground());
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

        if (_style == Style::Default)
        {
            if (_type == Type::Default)
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
            else if (_type == Type::Primary)
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
            else if (_type == Type::Success)
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
            else if (_type == Type::Info)
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
            else if (_type == Type::Warning)
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
            else if (_type == Type::Danger)
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
        else if (_style == Style::Plain)
        {
            if (_type == Type::Default)
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
            else if (_type == Type::Primary)
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
            else if (_type == Type::Success)
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
            else if (_type == Type::Info)
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
            else if (_type == Type::Warning)
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
            else if (_type == Type::Danger)
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
        else if (_style == Style::Round || _style == Style::Circle)
        {
            if (_type == Type::Default)
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
            else if (_type == Type::Primary)
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
            else if (_type == Type::Success)
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
            else if (_type == Type::Info)
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
            else if (_type == Type::Warning)
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
            else if (_type == Type::Danger)
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
        else if (_style == Style::Link)
        {
            _qsshelper.clearGroup("QPushButton:pressed");

            if (_type == Type::Default)
            {
                _qsshelper.setProperty("QPushButton", "color", Color::regularText());
                _qsshelper.setProperty("QPushButton:hover", "color", Color::secondaryText());
                _qsshelper.setProperty("QPushButton:pressed", "color", Color::primaryText());
                _qsshelper.setProperty("QPushButton:disabled", "color", Color::placeholderText());
            }
            else if (_type == Type::Primary)
            {
                _qsshelper.setProperty("QPushButton", "color", Color::primary());
                _qsshelper.setProperty("QPushButton:hover", "color", Color::primaryL1());
                _qsshelper.setProperty("QPushButton:pressed", "color", Color::primaryD1());
                _qsshelper.setProperty("QPushButton:disabled", "color", Color::primaryL2());
            }
            else if (_type == Type::Success)
            {
                _qsshelper.setProperty("QPushButton", "color", Color::success());
                _qsshelper.setProperty("QPushButton:hover", "color", Color::successL1());
                _qsshelper.setProperty("QPushButton:pressed", "color", Color::successD1());
                _qsshelper.setProperty("QPushButton:disabled", "color", Color::successL2());
            }
            else if (_type == Type::Info)
            {
                _qsshelper.setProperty("QPushButton", "color", Color::info());
                _qsshelper.setProperty("QPushButton:hover", "color", Color::infoL1());
                _qsshelper.setProperty("QPushButton:pressed", "color", Color::infoD1());
                _qsshelper.setProperty("QPushButton:disabled", "color", Color::infoL2());
            }
            else if (_type == Type::Warning)
            {
                _qsshelper.setProperty("QPushButton", "color", Color::warning());
                _qsshelper.setProperty("QPushButton:hover", "color", Color::warningL1());
                _qsshelper.setProperty("QPushButton:pressed", "color", Color::warningD1());
                _qsshelper.setProperty("QPushButton:disabled", "color", Color::warningL2());
            }
            else if (_type == Type::Danger)
            {
                _qsshelper.setProperty("QPushButton", "color", Color::danger());
                _qsshelper.setProperty("QPushButton:hover", "color", Color::dangerL1());
                _qsshelper.setProperty("QPushButton:pressed", "color", Color::dangerD1());
                _qsshelper.setProperty("QPushButton:disabled", "color", Color::dangerL2());
            }
        }
        else if (_style == Style::Text)
        {
            _qsshelper.setProperty("QPushButton:hover", "border", "none");
            _qsshelper.setProperty("QPushButton:pressed", "border", "none");

            if (_type == Type::Default)
            {
                _qsshelper.setProperty("QPushButton", "color", Color::regularText());
                _qsshelper.setProperty("QPushButton:hover", "color", Color::regularText());
                _qsshelper.setProperty("QPushButton:pressed", "color", Color::regularText());
                _qsshelper.setProperty("QPushButton:disabled", "color", Color::placeholderText());
            }
            else if (_type == Type::Primary)
            {
                _qsshelper.setProperty("QPushButton", "color", Color::primary());
                _qsshelper.setProperty("QPushButton:hover", "color", Color::primary());
                _qsshelper.setProperty("QPushButton:pressed", "color", Color::primary());
                _qsshelper.setProperty("QPushButton:disabled", "color", Color::primaryL2());
            }
            else if (_type == Type::Success)
            {
                _qsshelper.setProperty("QPushButton", "color", Color::success());
                _qsshelper.setProperty("QPushButton:hover", "color", Color::success());
                _qsshelper.setProperty("QPushButton:pressed", "color", Color::success());
                _qsshelper.setProperty("QPushButton:disabled", "color", Color::successL2());
            }
            else if (_type == Type::Info)
            {
                _qsshelper.setProperty("QPushButton", "color", Color::info());
                _qsshelper.setProperty("QPushButton:hover", "color", Color::info());
                _qsshelper.setProperty("QPushButton:pressed", "color", Color::info());
                _qsshelper.setProperty("QPushButton:disabled", "color", Color::infoL2());
            }
            else if (_type == Type::Warning)
            {
                _qsshelper.setProperty("QPushButton", "color", Color::warning());
                _qsshelper.setProperty("QPushButton:hover", "color", Color::warning());
                _qsshelper.setProperty("QPushButton:pressed", "color", Color::warning());
                _qsshelper.setProperty("QPushButton:disabled", "color", Color::warningL2());
            }
            else if (_type == Type::Danger)
            {
                _qsshelper.setProperty("QPushButton", "color", Color::danger());
                _qsshelper.setProperty("QPushButton:hover", "color", Color::danger());
                _qsshelper.setProperty("QPushButton:pressed", "color", Color::danger());
                _qsshelper.setProperty("QPushButton:disabled", "color", Color::dangerL2());
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

        if (_size == Size::Large)
        {
            _qsshelper.setProperty("QPushButton", "padding", "12px 19px");

            setMinimumHeight(50);
        }
        else if (_size == Size::Small)
        {
            _qsshelper.setProperty("QPushButton", "border-radius", "2px");
            _qsshelper.setProperty("QPushButton", "padding", "5px 11px");
            _qsshelper.setProperty("QPushButton", "font-size", "14px");

            if (!Icon::isNone(_icon))
                QPushButton::setIconSize(QSize(_smallIconSize, _smallIconSize));

            setMinimumHeight(30);
        }

        QPushButton::setStyleSheet(_qsshelper.generate());
        return *this;
    }


    bool Button::isDisabled()
    {
        return !QPushButton::isEnabled();
    }

    Button& Button::setDisabled(bool disabled)
    {
        QPushButton::setDisabled(disabled);
        return *this;
    }

    bool Button::isLoading()
    {
        return _loading;
    }

    Button& Button::setLoading(bool loading)
    {
        _loading = loading;
        return *this;
    }

    QPair<Icon::Name, Button::IconPosition> Button::getIcon()
    {
        return QPair<Icon::Name, Button::IconPosition>(_icon, _iconPostion);
    }

    Button& Button::setIcon(Icon::Name name, IconPosition pos)
    {
        _icon = name;
        _iconPostion = pos;

        if (_type == Type::Default)
        {
            QIcon icon = Icon::instance().getIcon(name, Color::regularText(), _iconSize);
            QPushButton::setIcon(icon);
            QPushButton::setIconSize(QSize(_iconSize, _iconSize));
        }
        else
        {
            QIcon icon = Icon::instance().getIcon(name, Color::blankFill(), _iconSize);
            QPushButton::setIcon(icon);
            QPushButton::setIconSize(QSize(_iconSize, _iconSize));
        }

        if (pos == IconPosition::Only)
        {
            QPushButton::setText("");
        }
        else if (pos == IconPosition::Left)
        {
            ;
        }
        else if (pos == IconPosition::Right)
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
