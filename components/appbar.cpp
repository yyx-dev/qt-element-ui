#include "appbar.h"
#include "app.h"
#include "icon.h"
#include "color.h"
#include "base.h"

#include <QStyle>
#include <QMouseEvent>
#include <QTimer>

namespace Element
{
    AppBar::AppBar(QWidget* parent)
        : QWidget(parent)
        , _layout(new QHBoxLayout(this))
        , _iconLabel(new QLabel(this))
        , _titleLabel(new QLabel(this))
        , _backButton(new QLabel(this))
        , _minButton(new _AppBarButton(_AppBarButton::Type::Min, this))
        , _maxButton(new _AppBarButton(_AppBarButton::Type::Max, this))
        , _closeButton(new _AppBarButton(_AppBarButton::Type::Close, this))
    {
        setFixedHeight(sc(48));

        _layout->setContentsMargins(0, 0, 0, 0);
        _layout->setSpacing(0);

        _backButton->setFixedSize(sc(40, 36));

        _iconLabel->setPixmap(App::getWindowIcon().pixmap(24));
        _titleLabel->setText(App::getApplicationDisplayName());
        _titleLabel->setContentsMargins(sc(8), 0, sc(8), 0);

        _backButton->setPixmap(Icon::instance().getPixmap(Icon::Back, Color::placeholderText(), 22));
        _backButton->setAlignment(Qt::AlignCenter);

        _layout->addSpacing(5);
        _layout->addWidget(_backButton);
        _layout->addWidget(_iconLabel);
        _layout->addWidget(_titleLabel);
        _layout->addStretch();
        _layout->addWidget(_minButton, 0, Qt::AlignTop);
        _layout->addWidget(_maxButton, 0, Qt::AlignTop);
        _layout->addWidget(_closeButton, 0, Qt::AlignTop);

        connect(_minButton, &QPushButton::clicked, this, &AppBar::onMinButtonClicked);
        connect(_maxButton, &QPushButton::clicked, this, &AppBar::onMaxButtonClicked);
        connect(_closeButton, &QPushButton::clicked, this, &AppBar::onCloseButtonClicked);
    }

    AppBar& AppBar::setBgColor(const QString& color)
    {
        QPalette pal = palette();
        pal.setColor(QPalette::Window, color);
        setPalette(pal);
        setAutoFillBackground(true);
        return *this;
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
            QWidget* child = childAt(event->pos());
            if (!child
             || (child != _minButton
              && child != _maxButton
              && child != _closeButton
              && child != _backButton))
            {
                _dragging = true;
                _dragStartPos = event->globalPos() - window()->frameGeometry().topLeft();
                event->accept();
                return;
            }
        }
        QWidget::mousePressEvent(event);
    }

    void AppBar::mouseMoveEvent(QMouseEvent* event)
    {
        if (_dragging && event->buttons() & Qt::LeftButton)
        {
            QPoint newPos = event->globalPos() - _dragStartPos;
            window()->move(newPos);
            event->accept();
            return;
        }
        QWidget::mouseMoveEvent(event);
    }

    void AppBar::mouseReleaseEvent(QMouseEvent* event)
    {
        if (event->button() == Qt::LeftButton && _dragging)
        {
            _dragging = false;
            event->accept();
            return;
        }
        QWidget::mouseReleaseEvent(event);
    }

    void AppBar::mouseDoubleClickEvent(QMouseEvent* event)
    {
        if (event->button() == Qt::LeftButton)
        {
            onMaxButtonClicked();
            event->accept();
            return;
        }
        QWidget::mouseDoubleClickEvent(event);
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


    _AppBarButton::_AppBarButton(Type type, QWidget* parent)
        : QPushButton(parent)
        , _type(type)
    {
        setFlat(true);
        setFixedSize(sc(48, 32));
    }

    void _AppBarButton::setType(Type type)
    {
        _type = type;
    }

    _AppBarButton::Type _AppBarButton::getType()
    {
        return _type;
    }

    void _AppBarButton::paintEvent(QPaintEvent*)
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