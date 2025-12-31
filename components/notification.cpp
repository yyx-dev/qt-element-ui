#include "icon.h"
#include "notification.h"
#include "private/utils.h"
#include "shadow.h"

#include <QBoxLayout>
#include <QPainter>

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#    include <QPainterPath>
#endif
#include <QEvent>
#include <QHash>
#include <QTimer>


namespace Element
{
    Notification::Notification(const QString& title, const QString& content, QWidget* parent)
        : Notification(title, content, Type::Primary, parent)
    {
    }

    Notification::Notification(const QString& title, const QString& content, Type type, QWidget* parent)
        : QWidget(parent)
        , _icon(new QLabel(this))
        , _title(new QLabel(title, this))
        , _close(new QLabel(this))
        , _content(new QLabel(content, this))
        , _type(type)
        , _timer(new QTimer(this))
    {
        setWindowFlags(Qt::FramelessWindowHint);
        setAttribute(Qt::WA_DeleteOnClose);
        setMinimumSize(250, 100);

        QVBoxLayout* mainLayout = new QVBoxLayout(this);
        mainLayout->setContentsMargins(20, 15, 20, 15);
        mainLayout->setSpacing(10);

        QHBoxLayout* layout1 = new QHBoxLayout;
        layout1->addWidget(_icon);
        layout1->addWidget(_title);
        layout1->addStretch();
        layout1->addWidget(_close);

        QHBoxLayout* layout2 = new QHBoxLayout;
        layout2->addSpacing(34);
        layout2->addWidget(_content);
        layout2->addSpacing(30);

        mainLayout->addLayout(layout1);
        mainLayout->addLayout(layout2);
        setLayout(mainLayout);

        setupUI();

        setType(_type);
        connect(_timer, &QTimer::timeout, this, &Notification::onTimeout);
        connect(_close, &QLabel::linkActivated, this, &Notification::onTimeout);
    }

    void Notification::setupUI()
    {
        _title->setFont(FontHelper(_title->font())
                            .setPointSize(Comm::largeFontSize)
                            .setBold(true)
                            .getFont());

        _content->setFont(FontHelper(_content->font())
                              .setPointSize(Comm::defaultFontSize)
                              .getFont());

        _title->adjustSize();
        _content->setWordWrap(true);
        _content->adjustSize();

        _close->setPixmap(Icon::instance().getPixmap(Icon::Close, Color::secondaryText(), 16));

        _close->setAttribute(Qt::WA_Hover);
        _close->installEventFilter(this);

        QPalette palette = _title->palette();
        palette.setColor(QPalette::WindowText, Color::primaryText());
        _title->setPalette(palette);

        palette = _content->palette();
        palette.setColor(QPalette::WindowText, Color::regularText());
        _content->setPalette(palette);

        ShadowEf::setShadow(this, ShadowEf::Type::Dark);
    }

    void Notification::show()
    {
        updatePosition();
        QWidget::show();
        _timer->start(_duration);
    }

    Notification& Notification::setTitle(const QString& title)
    {
        _title->setText(title);
        adjustSize();
        return *this;
    }

    Notification& Notification::setContent(const QString& content)
    {
        _content->setText(content);
        adjustSize();
        return *this;
    }

    Notification& Notification::setType(Notification::Type type)
    {
        _type = type;
        _icon->setPixmap(getIcon());
        adjustSize();
        return *this;
    }

    Notification& Notification::setShowClose(bool showClose, bool autoClose)
    {
        _showClose = showClose;
        if (!autoClose)
        {
        }
        return *this;
    }

    Notification& Notification::setPosition(Notification::Position position)
    {
        _positon = position;
        return *this;
    }

    Notification& Notification::setDuration(int msec)
    {
        _duration = msec;
        return *this;
    }

    void Notification::updatePosition()
    {
        QRect parentRect = parentWidget()->geometry();
        QSize widgetSize = size();

        int x = 0, y = 0;

        if (_positon == Position::TopLeft)
        {
            x = 15;
            y = 10 + (10 + widgetSize.height()) * _count[Position::TopLeft]++;
        }
        else if (_positon == Position::TopRight)
        {
            x = parentRect.width() - widgetSize.width() - 15;
            y = 10 + (10 + widgetSize.height()) * _count[Position::TopRight]++;
        }
        else if (_positon == Position::BottomLeft)
        {
            x = 15;
            y = parentRect.height() - (widgetSize.height() + 10) * ++_count[Position::BottomLeft];
        }
        else if (_positon == Position::BottomRight)
        {
            x = parentRect.width() - widgetSize.width() - 15;
            y = parentRect.height() - (widgetSize.height() + 10) * ++_count[Position::BottomRight];
        }

        move(x, y);
    }

    QPixmap Notification::getIcon()
    {
        switch (_type)
        {
        case Type::Defualt: return QPixmap();
        case Type::Primary: return Icon::instance().getPixmap(Icon::InfoFilled, Color::primary(), 24);
        case Type::Success: return Icon::instance().getPixmap(Icon::SuccessFilled, Color::success(), 24);
        case Type::Warning: return Icon::instance().getPixmap(Icon::WarningFilled, Color::warning(), 24);
        case Type::Info: return Icon::instance().getPixmap(Icon::InfoFilled, Color::info(), 24);
        case Type::Error: return Icon::instance().getPixmap(Icon::CircleCloseFilled, Color::danger(), 24);
        }
        return QPixmap();
    }

    void Notification::onTimeout()
    {
        _count[_positon]--;
        QWidget::close();
    }

    void Notification::paintEvent(QPaintEvent* event)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // 绘制圆角背景
        QPainterPath path;
        path.addRoundedRect(rect().adjusted(1, 1, -1, -1), 8, 8, Qt::AbsoluteSize);
        painter.setClipPath(path);

        // 填充背景
        painter.fillPath(path, QColor(Qt::white));

        QWidget::paintEvent(event);
    }

    bool Notification::eventFilter(QObject* watched, QEvent* event)
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
}
