#include "tag.h"

#include "color.h"
#include "tools/commvar.h"

namespace Element
{

    Tag::Tag(QWidget* parent) : Tag("Tag 1", Type::Info, parent)
    {}

    Tag::Tag(const QString& text, QWidget* parent) : Tag(text, Type::Info, parent)
    {}

    Tag::Tag(const QString& text, Type type, QWidget* parent)
        : QLabel(text, parent)
        , _text(text)
        , _type(type)
    {
        setMinimumSize(60, 30);
        setAlignment(Qt::AlignCenter);

        QFont font = QLabel::font();
        font.setFamilies(CommonVar::baseFontFmailies);
        font.setPointSize(9);
        QLabel::setFont(font);

        _qsshelper.setProperty("QLabel", "color", getColor())
                  .setProperty("QLabel", "background-color", getBackgroundColor())
                  .setProperty("QLabel", "border", "1px solid " + getBorderColor())
                  .setProperty("QLabel", "border-radius", "4px")
                  .setProperty("QLabel", "padding", "0px 9px");

        setStyleSheet(_qsshelper.generate());
        adjustSize();
    }

    void Tag::setEffect(Effect effect)
    {
        _effect = effect;
    }

    void Tag::setType(Type type)
    {
        _type = type;
    }

    void Tag::setSize(Size size)
    {
        _size = size;
    }

    void Tag::setCloseable(bool closeable)
    {
        _closeable = closeable;
    }

    void Tag::setRound(bool round)
    {
        _round = round;
    }

    void Tag::setText(const QString& text)
    {
        QLabel::setText(text);
    }

    QString Tag::getColor()
    {
        switch (_type)
        {
        case Type::Primary: return Color::primary();
        case Type::Success: return Color::success();
        case Type::Warning: return Color::warning();
        case Type::Info: return Color::info();
        case Type::Danger: return Color::danger();
        }
        return "#000000";
    }

    QString Tag::getBorderColor()
    {
        switch (_type)
        {
        case Type::Primary: return Color::primaryL4();
        case Type::Success: return Color::successL4();
        case Type::Warning: return Color::warningL4();
        case Type::Info: return Color::infoL4();
        case Type::Danger: return Color::dangerL4();
        }
        return "#000000";
    }

    QString Tag::getBackgroundColor()
    {
        switch (_type)
        {
        case Type::Primary: return Color::primaryL5();
        case Type::Success: return Color::successL5();
        case Type::Warning: return Color::warningL5();
        case Type::Info: return Color::infoL5();
        case Type::Danger: return Color::dangerL5();
        }
        return "#000000";
    }

}
