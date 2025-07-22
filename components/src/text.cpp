#include "../include/text.h"
#include "../include/color.h"
#include "../../tools/include/commvar.h"

#include <QDebug>
#include <QFont>

namespace QTElementUI
{
    Text::Text(QWidget* parent)
        : QLabel(parent)
        , _type(Type::default_)
        , _size(Size::default_)
        , _tag(Tag::default_)
        , _truncated(false)
        , _fontFamily(CommonVar::baseFontFmaily)
        , _fontSize(CommonVar::defaultFontSize)
        , _fontWeight(CommonVar::regularFontWeight)
        , _fontColor(Color::regularText())
        , _backgroundColor(Color::baseBackground())

    {
        QFont font = QLabel::font();
        font.setFamily(_fontFamily);
        font.setPointSize(_fontSize);
        font.setWeight(_fontWeight);
        QLabel::setFont(font);
    }

    Text::Text(const QString &text, QWidget* parent)
        : Text(parent)
    {
        QLabel::setText(text);
        QLabel::adjustSize();
    }

    Text::Type Text::getType()
    {
        return _type;
    }

    Text& Text::setType(Type type)
    {
        _type = type;
        switch (_type)
        {
        case Type::default_:
            Text::setFontColor(Color::regularText());
            break;
        case Type::primary:
            Text::setFontColor(Color::primary());
            break;
        case Type::success:
            Text::setFontColor(Color::success());
            break;
        case Type::info:
            Text::setFontColor(Color::info());
            break;
        case Type::warning:
            Text::setFontColor(Color::warning());
            break;
        case Type::danger:
            Text::setFontColor(Color::danger());
            break;
        }

        QLabel::adjustSize();
        return *this;
    }

    Text::Size Text::getSize()
    {
        return _size;
    }

    Text& Text::setSize(Size size)
    {
        _size = size;
        switch (_size)
        {
        case Size::default_:
            setFontSize(CommonVar::defaultFontSize);
            break;
        case Size::large:
            setFontSize(CommonVar::largeFontSize);
            break;
        case Size::small:
            setFontSize(CommonVar::smallFontSize);
            break;
        }

        QLabel::adjustSize();
        return *this;
    }

    Text::Tag Text::getTag()
    {
        return _tag;
    }

    Text& Text::setTag(Tag tag)
    {
        _tag = tag;
        QFont font = QLabel::font();

        switch (_tag)
        {
        case Tag::default_:
            break;
        case Tag::paragraph:
            QLabel::setWordWrap(true); // 启用自动换行
            QLabel::setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            break;
        case Tag::bold:
            font.setBold(true);
            break;
        case Tag::italic:
            font.setItalic(true);
            break;
        case Tag::subscript:
            setSubscript();
            break;
        case Tag::superscript:
            setSupscript();
            break;
        case Tag::inserted:
            font.setUnderline(true);
            break;
        case Tag::deleted:
            font.setStrikeOut(true);
            break;
        case Tag::marked:
            setFontColor(Qt::yellow);
            break;
        }

        QLabel::setFont(font);
        return *this;
    }

    bool Text::getTruncated()
    {
        return _truncated;
    }

    Text& Text::setTruncated(bool truncated)
    {
        _truncated = truncated;
        return *this;
    }


    void Text::setFontColor(const QString& color)
    {
        QPalette palette = QLabel::palette();
        palette.setColor(QPalette::WindowText, color);
        palette.setColor(QPalette::Background, _backgroundColor);
        QLabel::setAutoFillBackground(true); // 必须启用背景填充
        QLabel::setPalette(palette);
    }


    void Text::setFontColor(int color)
    {
        QPalette palette = QLabel::palette();
        palette.setColor(QPalette::WindowText, color);
        QLabel::setPalette(palette);
    }

    void Text::setFontSize(int size)
    {
        QFont font = QLabel::font();
        font.setPointSize(size);
        QLabel::setFont(font);
    }

    void Text::setSubscript()
    {

        QLabel::setTextFormat(Qt::RichText);
        QLabel::setText("<sup>" + QLabel::text() + "</sup>");
    }

    void Text::setSupscript()
    {
        QLabel::setTextFormat(Qt::RichText);
        QLabel::setText("<sub>" + QLabel::text() + "</sub>");
    }
}
