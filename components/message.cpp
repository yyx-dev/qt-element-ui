#include "message.h"
#include "base.h"
#include "icon.h"

#include <QBoxLayout>
#include <QPainter>
#include <QTimer>
#include <QHash>



namespace Element
{
    Message::Message(const QString& message, QWidget* parent)
        : Message(message, "", Type::Info, parent)
    {}

    Message::Message(const QString& message, const QString& paramater, QWidget* parent)
        : Message(message, paramater, Type::Info, parent)
    {}

    Message::Message(const QString& message, Message::Type type, QWidget* parent)
        : Message(message, "", type, parent)
    {}

    Message::Message(const QString& message, const QString& paramater, Type type, QWidget* parent)
        : QWidget(parent)
        , _message(message)
        , _paramater(paramater)
        , _type(type)
        , _icon(new QLabel(this))
        , _text(new QLabel(this))
        , _timer(new QTimer(this))
    {
        setWindowFlags(Qt::FramelessWindowHint);
        setAttribute(Qt::WA_DeleteOnClose);

        _text->setFont(FontHelper(_text->font())
                .setPointSize(Comm::defaultFontSize)
                .getFont());

        QHBoxLayout *layout = new QHBoxLayout(this);
        layout->setContentsMargins(10, 10, 10, 10);
        layout->setSpacing(10);
        layout->addWidget(_icon);
        layout->addWidget(_text);

        setLayout(layout);

        setType(_type);
        connect(_timer, &QTimer::timeout, this, &Message::onTimeout);
    }

    void Message::show()
    {
        updatePosition();
        QWidget::show();
        _timer->start(_duration);
    }

    Message& Message::setMessage(const QString& message)
    {
        _message = message;
        updateTextAndIcon();
        adjustSize();

        return *this;
    }

    Message& Message::setParamater(const QString& paramater)
    {
        _paramater = paramater;
        updateTextAndIcon();
        adjustSize();
        return *this;
    }

    Message& Message::setType(Message::Type type)
    {
        _type = type;
        updateTextAndIcon();
        adjustSize();
        return *this;
    }

    Message& Message::setPlain(bool plain)
    {
        _plain = plain;
        return *this;
    }

    Message& Message::setShowClose(bool showClose, bool autoClose)
    {
        _showClose = showClose;
        if (!autoClose)
        {}
        return *this;
    }

    Message& Message::setPlacement(Message::Place placement)
    {
        _placement = placement;
        return *this;
    }

    Message& Message::setDuration(int msec)
    {
        _duration = msec;
        return *this;
    }

    void Message::updateTextAndIcon()
    {
        QString coloredMessage = QString("<span style='color:%1'>%2</span>")
            .arg(getColor())
            .arg(_message);

        QString coloredParameter = QString("<span style='color:#008080'>%2</span>")
            .arg(_paramater);

        _text->setText(coloredMessage + coloredParameter);

        _icon->setPixmap(getIcon());
    }

    void Message::updatePosition()
    {
        QRect parentRect = parentWidget()->geometry();
        QSize widgetSize = size();

        int x = 0, y = 0;

        if (_placement == Place::Top) {
            x = (parentRect.width() - widgetSize.width()) / 2;
            y = 10 + (10 + widgetSize.height()) * _count[Place::Top]++;
        }
        else if (_placement == Place::TopLeft) {
            x = 10;
            y = 10 + (10 + widgetSize.height()) * _count[Place::TopLeft]++;
        }
        else if (_placement == Place::TopRight) {
            x = parentRect.width() - widgetSize.width() - 10;
            y = 10 + (10 + widgetSize.height()) * _count[Place::TopRight]++;
        }
        else if (_placement == Place::Bottom) {
            x = (parentRect.width() - widgetSize.width()) / 2;
            y = parentRect.height() - (widgetSize.height() + 10) * ++_count[Place::Bottom];
        }
        else if (_placement == Place::BottomLeft) {
            x = 10;
            y = parentRect.height() - (widgetSize.height() + 10) * ++_count[Place::BottomLeft];
        }
        else if (_placement == Place::BottomRight) {
            x = parentRect.width() - widgetSize.width() - 10;
            y = parentRect.height() - (widgetSize.height() + 10) * ++_count[Place::BottomRight];
        }

        move(x, y);
    }

    QString Message::getColor()
    {
        switch (_type)
        {
        case Type::Primary: return Color::primary();
        case Type::Success: return Color::success();
        case Type::Warning: return Color::warning();
        case Type::Info: return Color::info();
        case Type::Error: return Color::danger();
        }
        return "#000000";
    }

    QString Message::getBorderColor()
    {
        switch (_type)
        {
        case Type::Primary: return Color::primaryL4();
        case Type::Success: return Color::successL4();
        case Type::Warning: return Color::warningL4();
        case Type::Info: return Color::infoL4();
        case Type::Error: return Color::dangerL4();
        }
        return "#000000";
    }

    QString Message::getBackgroundColor()
    {
        switch (_type)
        {
        case Type::Primary: return Color::primaryL5();
        case Type::Success: return Color::successL5();
        case Type::Warning: return Color::warningL5();
        case Type::Info: return Color::infoL5();
        case Type::Error: return Color::dangerL5();
        }
        return "#000000";
    }

    QPixmap Message::getIcon()
    {
        switch (_type)
        {
        case Type::Primary: return Icon::instance().getPixmap(Icon::InfoFilled, Color::primary(), 20);
        case Type::Success: return Icon::instance().getPixmap(Icon::SuccessFilled, Color::success(), 20);
        case Type::Warning: return Icon::instance().getPixmap(Icon::WarningFilled, Color::warning(), 20);
        case Type::Info:    return Icon::instance().getPixmap(Icon::InfoFilled, Color::info(), 20);
        case Type::Error:   return Icon::instance().getPixmap(Icon::CircleCloseFilled, Color::danger(), 20);
        }
        return QPixmap();
    }

    void Message::onTimeout()
    {
        _count[_placement]--;
        QWidget::close();
    }

    void Message::paintEvent(QPaintEvent *event)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // 绘制圆角背景
        QPainterPath path;
        path.addRoundedRect(rect().adjusted(0, 0, 0, 0), 4, 4, Qt::AbsoluteSize);
        painter.setClipPath(path);

        // 填充背景
        painter.fillPath(path, QColor(getBackgroundColor()));

        // 绘制边框
        painter.setPen(QPen(QColor(getBorderColor()), 2));
        painter.drawRoundedRect(rect().adjusted(0, 0, 0, 0), 4, 4, Qt::AbsoluteSize);

        QWidget::paintEvent(event);
    }
}
