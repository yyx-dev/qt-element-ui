#include "text.h"
#include "color.h"
#include "tools/commvar.h"

#include <QDebug>
#include <QFont>

namespace Element
{
    Text::Text(QWidget* parent)
        : Text("", parent)
    {}

    Text::Text(const QString& text, QWidget* parent)
        : QLabel(parent)
    {
        QFont font = QLabel::font();
        font.setFamilies(CommonVar::baseFontFmailies);
        font.setWeight(CommonVar::regularFontWeight);
        QLabel::setFont(font);

        QLabel::setText(text);
        QLabel::setWordWrap(true);
        QLabel::adjustSize();



        setType(_type);
        setSize(_size);
    }

    Text::Type Text::getType()
    {
        return _type;
    }

    Text& Text::setType(Type type)
    {
        _type = type;

        if (type == Type::Default)
            setFontColor(Color::regularText());
        else if (type == Type::Primary)
            setFontColor(Color::primary());
        else if (type == Type::Success)
            setFontColor(Color::success());
        else if (type == Type::Info)
            setFontColor(Color::info());
        else if (type == Type::Warning)
            setFontColor(Color::warning());
        else if (type == Type::Danger)
            setFontColor(Color::danger());

        setSize(_size);

        return *this;
    }

    Text::Size Text::getSize()
    {
        return _size;
    }

    Text& Text::setSize(Size size)
    {
        _size = size;
        if (size == Size::Default)
            setFontSize(10);
        else if (size == Size::Large)
            setFontSize(12);
        else if (size == Size::Small)
            setFontSize(8);

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

        if (tag == Tag::Paragraph)
        {
            QLabel::setWordWrap(true);
            QLabel::setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        }
        else if (tag == Tag::Bold)
             font.setBold(true);
        else if (tag == Tag::Italic)
            font.setItalic(true);
        else if (tag == Tag::Subscript)
            setSubscript();
        else if (tag == Tag::Superscript)
            setSupscript();
        else if (tag == Tag::Inserted)
            font.setUnderline(true);
        else if (tag == Tag::Deleted)
            font.setStrikeOut(true);
        else if (tag == Tag::Marked)
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

    void Text::setColor(const QString& color)
    {
        setFontColor(color);
    }


    void Text::setFontColor(const QString& color)
    {
        QPalette palette = QLabel::palette();
        palette.setColor(QPalette::WindowText, color);
        palette.setColor(QPalette::Window, Color::baseBackground());
        QLabel::setAutoFillBackground(true);
        QLabel::setPalette(palette);
    }

    void Text::setFontColor(int color)
    {
        QPalette palette = QLabel::palette();
        palette.setColor(QPalette::WindowText, color);
        palette.setColor(QPalette::Window, Color::baseBackground());
        QLabel::setAutoFillBackground(true);
        QLabel::setPalette(palette);
    }

    void Text::setFontSize(int size)
    {
        QFont font = QLabel::font();
        font.setPointSize(size);
        QLabel::setFont(font);
        QLabel::adjustSize();
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
