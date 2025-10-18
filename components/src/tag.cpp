#include "tag.h"

#include "color.h"
#include "icon.h"
#include "base.h"

#include <QEvent>


namespace Element
{

    Tag::Tag(QWidget* parent) : Tag("Tag 1", Type::Info, parent)
    {}

    Tag::Tag(const QString& text, QWidget* parent) : Tag(text, Type::Info, parent)
    {}

    Tag::Tag(const QString& text, Type type, QWidget* parent)
        : QLabel(parent)
        , _type(type)
        , _textLabel(new QLabel(text, this))
        , _closeIcon(new QLabel(this))
        , _layout(new QHBoxLayout(this))
    {
        QFont font = _textLabel->font();
        font.setFamilies(Comm::fontFmailies);
        font.setPointSize(9);

        _textLabel->setFont(font);
        _textLabel->setAlignment(Qt::AlignCenter);

        _closeIcon->setFixedSize(16, 16);
        _closeIcon->setScaledContents(true);
        _closeIcon->setVisible(false);
        _closeIcon->installEventFilter(this);

        _layout->setContentsMargins(0, 0, 0, 0);
        _layout->setSpacing(4);
        _layout->addWidget(_textLabel);
        _layout->addWidget(_closeIcon);

        setLayout(_layout);

        setStyleSheet(_qsshelper.setProperty("QLabel", "border-radius", "4px")
                                .setProperty("QLabel", "padding", "0px 9px")
                                .generate());
        adjustSize();
        setEffect(_effect);
        setType(_type);
        setSize(_size);
    }

    Tag& Tag::setEffect(Effect effect)
    {
        _effect = effect;
        setType(_type);
        return *this;
    }

    Tag& Tag::setType(Type type)
    {
        _type = type;
        setStyleSheet(_qsshelper.setProperty("QLabel", "color", getColor())
                                .setProperty("QLabel", "background-color", getBackgroundColor())
                                .setProperty("QLabel", "border", "1px solid " + getBorderColor())
                                .generate());

        _internalQsshelper.setProperty("QLabel", "border", "none")
                          .setProperty("QLabel", "padding", "0px");
        _textLabel->setStyleSheet(_internalQsshelper.generate());
        _closeIcon->setStyleSheet(_internalQsshelper.generate());

        _textLabel->adjustSize();
        return *this;
    }

    Tag& Tag::setSize(Size size)
    {
        _size = size;
        if (_size == Size::Default)    setFixedHeight(30), setMinimumWidth(60);
        else if (_size == Size::Large) setFixedHeight(40), setMinimumWidth(70);
        else if (_size == Size::Small) setFixedHeight(25), setMinimumWidth(50);
        return *this;
    }

    Tag& Tag::setCloseable(bool closeable)
    {
        _closeable = closeable;
        _closeIcon->setPixmap(Icon::instance().getPixmap(Icon::Close, getColor(), 16));
        _closeIcon->setVisible(closeable);
        return *this;
    }

    Tag& Tag::setRound(bool round)
    {
        _round = round;
        if (_round)
            setStyleSheet(_qsshelper.setProperty("QLabel", "border-radius", "15px")
                                    .generate());
        else
            setStyleSheet(_qsshelper.setProperty("QLabel", "border-radius", "4px")
                                    .generate());
        return *this;
    }

    Tag& Tag::setText(const QString& text)
    {
        _textLabel->setText(text);
        return *this;
    }

    bool Tag::eventFilter(QObject* obj, QEvent* event)
    {
        if (obj == _closeIcon && _closeable)
        {
            if (event->type() == QEvent::MouseButtonPress)
            {
                deleteLater();
                return true;
            }
            else if (event->type() == QEvent::Enter)
            {
                _closeIcon->setPixmap(Icon::instance().getPixmap(Icon::CircleCloseFilled, getColor(), 16));
            }
            else if (event->type() == QEvent::Leave)
            {
                _closeIcon->setPixmap(Icon::instance().getPixmap(Icon::Close, getColor(), 16));
            }
        }
        return QWidget::eventFilter(obj, event);
    }

    QString Tag::getColor()
    {
        switch (_effect)
        {
        case Effect::Light:
        case Effect::Plain:
            switch (_type) {
                case Type::Primary: return Color::primary();
                case Type::Success: return Color::success();
                case Type::Warning: return Color::warning();
                case Type::Info:    return Color::info();
                case Type::Danger:  return Color::danger();
            }
        case Effect::Dark:
            return Color::basicWhite();
        }

        return "#000000";
    }

    QString Tag::getBorderColor()
    {
        switch (_effect)
        {
        case Effect::Light:
            switch (_type) {
                case Type::Primary: return Color::primaryL4();
                case Type::Success: return Color::successL4();
                case Type::Warning: return Color::warningL4();
                case Type::Info:    return Color::infoL4();
                case Type::Danger:  return Color::dangerL4();
            }
        case Effect::Plain:
            switch (_type) {
                case Type::Primary: return Color::primaryL2();
                case Type::Success: return Color::successL2();
                case Type::Warning: return Color::warningL2();
                case Type::Info:    return Color::infoL2();
                case Type::Danger:  return Color::dangerL2();
            }
        case Effect::Dark:
            switch (_type) {
                case Type::Primary: return Color::primary();
                case Type::Success: return Color::success();
                case Type::Warning: return Color::warning();
                case Type::Info:    return Color::info();
                case Type::Danger:  return Color::danger();
            }
        }
        return "#000000";
    }

    QString Tag::getBackgroundColor()
    {
        switch (_effect)
        {
        case Effect::Light:
            switch (_type) {
                case Type::Primary: return Color::primaryL5();
                case Type::Success: return Color::successL5();
                case Type::Warning: return Color::warningL5();
                case Type::Info:    return Color::infoL5();
                case Type::Danger:  return Color::dangerL5();
            }
        case Effect::Dark:
            switch (_type) {
                case Type::Primary: return Color::primary();
                case Type::Success: return Color::success();
                case Type::Warning: return Color::warning();
                case Type::Info:    return Color::info();
                case Type::Danger:  return Color::danger();
            }
        case Effect::Plain:
               return Color::basicWhite();
        }
        return "#000000";
    }

}
