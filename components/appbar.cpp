#include "appbar.h"
#include "app.h"
#include "icon.h"
#include "color.h"
#include "private/utils.h"

#include <QStyle>
#include <QMouseEvent>
#include <QTimer>

namespace Element
{
    AppBar::AppBar(QWidget* parent)
        : AppBar(8, parent)
    {}

    AppBar::AppBar(int dragMargin, QWidget* parent)
        : QWidget(parent)
        , _layout(new QHBoxLayout(this))
        , _iconLabel(new QLabel(this))
        , _titleLabel(new QLabel(this))
        , _backButton(new _BackButton(this))
        , _minButton(new _CtrlButton(_CtrlButton::Type::Min, this))
        , _maxButton(new _CtrlButton(_CtrlButton::Type::Max, this))
        , _closeButton(new _CtrlButton(_CtrlButton::Type::Close, this))
    {
        setFixedHeight(sc(48));
        setMouseTracking(true);

        _layout->setContentsMargins(0, 0, 0, 0);
        _layout->setSpacing(0);

        _iconLabel->setPixmap(App::getWindowIcon().pixmap(24));
        _titleLabel->setText(App::getApplicationDisplayName());

        _layout->addSpacing(5);
        _layout->addWidget(_backButton);
        _layout->addSpacing(3);
        _layout->addWidget(_iconLabel);
        _layout->addSpacing(10);
        _layout->addWidget(_titleLabel);
        _layout->addStretch();
        _layout->addWidget(_minButton, 0, Qt::AlignTop);
        _layout->addWidget(_maxButton, 0, Qt::AlignTop);
        _layout->addWidget(_closeButton, 0, Qt::AlignTop);

        connect(_backButton, &QLabel::linkActivated, this, &AppBar::backButtonClicked);
        connect(_minButton, &QPushButton::clicked, this, &AppBar::onMinButtonClicked);
        connect(_maxButton, &QPushButton::clicked, this, &AppBar::onMaxButtonClicked);
        connect(_closeButton, &QPushButton::clicked, this, &AppBar::onCloseButtonClicked);

        setDragMargin(_dragMargin);
    }

    void AppBar::setDragMargin(int margin)
    {
        _dragMargin = margin;
    }

    void AppBar::enableBackButton()
    {
        _backButton->setEnabled(true);
        _backButton->setPixmap(Icon::instance().getPixmap(Icon::Back, Color::secondaryText(), 22));
    }

    void AppBar::disableBackButton()
    {
        _backButton->setEnabled(false);
        _backButton->setPixmap(Icon::instance().getPixmap(Icon::Back, Color::placeholderText(), 22));
    }

    void AppBar::changeEvent(QEvent* event)
    {
        if (event->type() == QEvent::ActivationChange)
        {
            _minButton->update();
            _maxButton->update();
            _closeButton->update();
            event->accept();
            return;
        }
        QWidget::changeEvent(event);
    }

    void AppBar::mousePressEvent(QMouseEvent* event)
    {
        if (event->button() == Qt::LeftButton)
        {
            if (event->pos().y() <= _dragMargin)
            {
                QWidget::mousePressEvent(event);
                return;
            }

            QWidget* child = childAt(event->pos());

            if ((!child)
             || (child != _minButton && child != _maxButton && child != _closeButton && child != _backButton))
            {
                _dragging = true;
                _dragStartPos = event->globalPos() - window()->frameGeometry().topLeft();
            }
        }
        QWidget::mousePressEvent(event);
    }

    void AppBar::mouseMoveEvent(QMouseEvent* event)
    {
        if (event->pos().y() > _dragMargin && _dragging && event->buttons() & Qt::LeftButton)
        {
            QPoint newPos = event->globalPos() - _dragStartPos;
            window()->move(newPos);
        }
        QWidget::mouseMoveEvent(event);
    }

    void AppBar::mouseReleaseEvent(QMouseEvent* event)
    {
        if (event->pos().y() > _dragMargin && event->button() == Qt::LeftButton && _dragging)
        {
            _dragging = false;
        }
        QWidget::mouseReleaseEvent(event);
    }

    void AppBar::mouseDoubleClickEvent(QMouseEvent* event)
    {
        QWidget* child = childAt(event->pos());
        if (!child && child != _backButton && event->button() == Qt::LeftButton)
        {
            onMaxButtonClicked();
        }
    }

    void AppBar::paintEvent(QPaintEvent* event)
    {
        QPainter painter(this);
        painter.setPen(QPen(QColor(Color::baseBorder()), 1));
        painter.drawLine(0, height() - 1, width() - 1, height() - 1);

        QWidget::paintEvent(event);
    }

    void AppBar::onMinButtonClicked()
    {
        window()->showMinimized();
    }

    void AppBar::onMaxButtonClicked()
    {
        window()->isMaximized() ? window()->showNormal() : window()->showMaximized();
    }

    void AppBar::onCloseButtonClicked()
    {
        window()->close();
    }


    _BackButton::_BackButton(QWidget* parent)
        : QLabel(parent)
    {
        setPixmap(Icon::instance().getPixmap(Icon::Back, Color::placeholderText(), 22));
        setAlignment(Qt::AlignCenter);
        setFixedSize(sc(40, 36));
        setEnabled(false);
    }

    #if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
void _BackButton::enterEvent(QEnterEvent* event)
#else
void _BackButton::enterEvent(QEvent* event)
#endif
    {
        if (isEnabled())
            setCursor(Qt::PointingHandCursor);
        QLabel::enterEvent(event);
        update();
    }

    void _BackButton::leaveEvent(QEvent* event)
    {
        if (isEnabled())
            setCursor(Qt::ArrowCursor);
        QLabel::leaveEvent(event);
        update();
    }

    void _BackButton::mousePressEvent(QMouseEvent* event)
    {
        _pressed = true;
        QLabel::mousePressEvent(event);
        update();
    }

    void _BackButton::mouseReleaseEvent(QMouseEvent* event)
    {
        _pressed = false;
        emit linkActivated("");
        QLabel::mouseReleaseEvent(event);
        update();
    }

    void _BackButton::paintEvent(QPaintEvent* event)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QRect rect = this->rect().adjusted(1, 1, -1, -1);

        if (!isEnabled())
        {
            QLabel::paintEvent(event);
            return;
        }

        if (underMouse() && _pressed)
        {
            painter.setBrush(QBrush(QColor(0xCC, 0xCC, 0xCC, 40)));
            painter.setPen(Qt::NoPen);
            painter.drawRoundedRect(rect, 4, 4);
        }
        else if (underMouse())
        {
            painter.setBrush(QBrush(QColor(0xCC, 0xCC, 0xCC, 20)));
            painter.setPen(Qt::NoPen);
            painter.drawRoundedRect(rect, 4, 4);
        }
        else
        {
            painter.setBrush(QBrush(Qt::white));
            painter.setPen(Qt::NoPen);
            painter.drawRoundedRect(rect, 4, 4);
        }

        QLabel::paintEvent(event);
    }

    _CtrlButton::_CtrlButton(Type type, QWidget* parent)
        : QPushButton(parent)
        , _type(type)
    {
        setFlat(true);
        setFixedSize(sc(48, 32));
    }

    void _CtrlButton::setType(Type type)
    {
        _type = type;
    }

    _CtrlButton::Type _CtrlButton::getType()
    {
        return _type;
    }

    void _CtrlButton::paintEvent(QPaintEvent*)
    {
        QPainter painter(this);

        QRect rect = this->rect();
        bool hovered = underMouse();
        bool pressed = isDown();

        // 背景
        QColor bgColor = parentWidget()->palette().color(QPalette::Window);

        if (_type == Type::Min)
        {
            if (hovered) bgColor = "#E5E5E5";
            if (pressed) bgColor = "#CACACB";
        }
        else if (_type == Type::Max)
        {
            if (hovered) bgColor = "#E5E5E5";
            if (pressed) bgColor = "#CCCCCC";
        }
        else if (_type == Type::Close)
        {
            if (hovered) bgColor = "#E81123";
            if (pressed) bgColor = "#F1707A";
        }

        painter.fillRect(rect, bgColor);

        // 前景
        QColor fgColor = Qt::black;

        if (_type == Type::Close && hovered)
            fgColor = Qt::white;
        if (!isActiveWindow())
            fgColor = "#999999";

        QRect iconRect(rect.center().x() - 6, rect.center().y() - 6, 12, 12);

        painter.setPen(QPen(fgColor, 1));

        if (_type == Type::Min)
        {
            int y = iconRect.center().y();
            painter.drawLine(iconRect.left(), y, iconRect.right(), y);
        }
        else if (_type == Type::Max)
        {
            if (window()->isMaximized())
            {
                QRect inner = iconRect.adjusted(2, 0, -1, -3);
                QRect outer = iconRect.adjusted(0, 2, -3, -1);
                painter.setBrush(bgColor);
                painter.drawRect(inner);
                painter.drawRect(outer);
            }
            else
            {
                painter.setBrush(Qt::NoBrush);
                painter.drawRect(iconRect.adjusted(0, 0, -1, -1));
            }
        }
        else if (_type == Type::Close)
        {
            painter.setPen(hovered ? "#F16B76" : !isActiveWindow() ? "#EBEBEB" : "#CCCCCC");
            painter.drawLine(iconRect.left() + 1, iconRect.top(), iconRect.right(), iconRect.bottom() - 1);
            painter.drawLine(iconRect.left() + 1, iconRect.bottom(), iconRect.right(), iconRect.top() + 1);
            painter.drawLine(iconRect.left(), iconRect.top() + 1, iconRect.right() - 1, iconRect.bottom());
            painter.drawLine(iconRect.left(), iconRect.bottom() - 1, iconRect.right() - 1, iconRect.top());

            painter.setPen(fgColor);
            painter.drawLine(iconRect.left(), iconRect.top(), iconRect.right(), iconRect.bottom());
            painter.drawLine(iconRect.left(), iconRect.bottom(), iconRect.right(), iconRect.top());
        }
    }

}