#include "message.h"
#include "messagemanager.h"
#include "private/utils.h"
#include "private/animation.h"
#include "icon.h"
#include "color.h"

#include <QBoxLayout>
#include <QPainter>
#include <QTimer>
#include <QHash>
#include <QPainterPath>

namespace Element
{
    QHash<QWidget*, MessageManager*> Message::_managersHash;

    Message::Message(const QString& message, QWidget* parent)
        : Message(message, "", Type::Info, parent)
    {}

    Message::Message(const QString& message, const QString& paramater, QWidget* parent)
        : Message(message, paramater, Type::Info, parent)
    {}

    Message::Message(const QString& message, Type type, QWidget* parent)
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
            _manager = getManager(parent);

            setWindowFlags(Qt::FramelessWindowHint);

            _text->setFont(FontHelper(_text->font())
                               .setPointSize(Comm::defaultFontSize)
                               .getFont());

            QHBoxLayout *layout = new QHBoxLayout(this);
            layout->setContentsMargins(10, 10, 10, 10);
            layout->setSpacing(10);
            layout->addWidget(_icon);
            layout->addWidget(_text);

            _close = new QLabel(this);
            _close->setPixmap(Icon::instance().getPixmap(Icon::Close, Color::secondaryText(), 16));
            _close->setAttribute(Qt::WA_Hover);
            _close->installEventFilter(this);
            this->layout()->addWidget(_close);
            _close->hide();
            connect(_close, &QLabel::linkActivated, this, &Message::onTimeout);

            setLayout(layout);

            setType(_type);
            connect(_timer, &QTimer::timeout, this, &Message::onTimeout);
        }

    void Message::show()
    {
        if(_manager)
            _manager->addMessage(this);

        updatePosition();

        if(_duration>0&&_autoClose)
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

    Message& Message::setShowClose(bool showClose)
    {
        if(showClose)
            _close->show();
        else
            _close->hide();

        adjustSize();
        return *this;
    }

    Message& Message::setAutoClose(bool autoClose)
    {
        _autoClose = autoClose;
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

    Message& Message::setOnClose(bool onClose)
    {
        _onClose = onClose;
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
        int offset = 0;

        switch (_placement)
        {
        case Place::Top:
        case Place::TopLeft:
        case Place::TopRight:
            offset = -(this->geometry().height());
            break;

        case Place::Bottom:
        case Place::BottomLeft:
        case Place::BottomRight:
            offset = this->geometry().height();
            break;
        }

        QWidget::show();

        _fadeInAnim = Animation::fadeInMove(this, Animation::OpacityType::GraphicsEffect, offset, 300);
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

    Message::Place Message::getPlacement()
    {
        return _placement;
    }

    void Message::onTimeout()
    {
        int offset = 0;

        switch(_placement)
        {
        case Place::Top:
        case Place::TopLeft:
        case Place::TopRight:
            offset = -(this->geometry().height());
            break;

        case Place::Bottom:
        case Place::BottomLeft:
        case Place::BottomRight:
            offset = this->geometry().height();
            break;
        }

        Animation::fadeOutMove(this, Animation::OpacityType::GraphicsEffect, offset, 300, [this]() {
            if(_onClose)
                emit close();

            this->deleteLater();
        });

        if (_manager)
            _manager->removeMessage(this);
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

    void Message::stopFadeIn()
    {
        if (_fadeInAnim)
        {
            _fadeInAnim->stop();

            if (auto effect = qobject_cast<QGraphicsOpacityEffect*>(graphicsEffect()))
                effect->setOpacity(1.0);

            _fadeInAnim->deleteLater();
            _fadeInAnim = nullptr;
        }
    }

    bool Message::eventFilter(QObject* watched, QEvent* event)
    {
        if (watched == _close)
        {
            if (event->type() == QEvent::HoverEnter)
            {
                _close->setPixmap(Icon::instance().getPixmap(Icon::Close, Color::regularText(), 16));
                _close->setCursor(Qt::PointingHandCursor);
                return true;
            }
            else if (event->type() == QEvent::HoverLeave)
            {
                _close->setPixmap(Icon::instance().getPixmap(Icon::Close, Color::secondaryText(), 16));
                _close->setCursor(Qt::ArrowCursor);
                return true;
            }
            else if (event->type() == QEvent::MouseButtonPress)
            {
                emit _close->linkActivated("");
            }
        }
        return QWidget::eventFilter(watched, event);
    }

    MessageManager* Message::getManager(QWidget* parent)
    {
        auto it = _managersHash.find(parent);
        if (it != _managersHash.end())
            return it.value();

        MessageManager* mgr = new MessageManager(parent);
        _managersHash.insert(parent, mgr);

        QObject::connect(parent, &QWidget::destroyed, [parent](){
            _managersHash.remove(parent);
        });

        return mgr;
    }
}
