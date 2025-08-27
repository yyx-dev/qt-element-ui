#include "text.h"
#include "color.h"
#include "commvar.h"

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
    {
        QFont font = QLabel::font();
        font.setFamilies(CommonVar::baseFontFmailies);
        font.setPointSize(CommonVar::defaultFontSize);
        font.setWeight(CommonVar::regularFontWeight);
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

        if (type == Type::default_)
            setFontColor(Color::regularText());
        else if (type == Type::primary)
            setFontColor(Color::primary());
        else if (type == Type::success)
            setFontColor(Color::success());
        else if (type == Type::info)
            setFontColor(Color::info());
        else if (type == Type::warning)
            setFontColor(Color::warning());
        else if (type == Type::danger)
            setFontColor(Color::danger());

        return *this;
    }

    Text::Size Text::getSize()
    {
        return _size;
    }

    Text& Text::setSize(Size size)
    {
        _size = size;
        if (size == Size::default_)
            setFontSize(CommonVar::defaultFontSize);
        else if (size == Size::large)
            setFontSize(CommonVar::largeFontSize);
        else if (size == Size::small)
            setFontSize(CommonVar::smallFontSize);

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

        if (tag == Tag::paragraph)
        {
            QLabel::setWordWrap(true); // 启用自动换行
            QLabel::setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        }
        else if (tag == Tag::bold)
             font.setBold(true);
        else if (tag == Tag::italic)
            font.setItalic(true);
        else if (tag == Tag::subscript)
            setSubscript();
        else if (tag == Tag::superscript)
            setSupscript();
        else if (tag == Tag::inserted)
            font.setUnderline(true);
        else if (tag == Tag::deleted)
            font.setStrikeOut(true);
        else if (tag == Tag::marked)
            setFontColor(Qt::yellow);

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
        palette.setColor(QPalette::Background, Color::baseBackground());
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
