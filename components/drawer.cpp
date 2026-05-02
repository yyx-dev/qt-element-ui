#include "drawer.h"
#include "text.h"
#include "icon.h"
#include "color.h"
#include "private/utils.h"
#include "private/animation.h"
#include "shadow.h"

#include <QtMath>
#include <QEvent>

namespace Element
{

    Drawer::Drawer(QWidget* topWidget)
        : QWidget(topWidget)
        , _layout(new QVBoxLayout(this))
    {
        setAttribute(Qt::WA_DeleteOnClose);
        setupHeader();
        setupBody();
        setupFooter();

        _layout->addWidget(_header);
        _layout->addLayout(_bodyLayout);
        _layout->addStretch();
        _layout->addWidget(_footer);

        ShadowEf::setShadow(this, ShadowEf::Type::Dark);
        _mask = MaskEf::setMask(this, parentWidget());
        connect(_mask, &Mask::clicked, this, [this](){closeDrawer(false);});

        setVisible(false);

        updatePosition();

        topWidget->installEventFilter(this);
    }

    Drawer& Drawer::setBody(QWidget* body)
    {
        _bodyLayout->replaceWidget(_body, body);
        _body = body;
        return *this;
    }

    Drawer& Drawer::setDestroyOnClose(bool destroy)
    {
        setAttribute(Qt::WA_DeleteOnClose, destroy);
        return *this;
    }

    Drawer& Drawer::setBeforeOpen(const std::function<void(std::function<void()>)>& callback)
    {
        _beforeOpenCallback = callback;
        return *this;
    }

    Drawer& Drawer::setBeforeClose(const std::function<void(std::function<void()>)>& callback)
    {
        _beforeCloseCallback = callback;
        return *this;
    }

    void Drawer::setupHeader()
    {
        _header = new QWidget(this);

        QLabel* text = new QLabel(_title, _header);
        text->setFont(FontHelper().setPointSize(12).getFont());

        QPalette palette = text->palette();
        palette.setColor(QPalette::WindowText, Color::primaryText());
        text->setPalette(palette);

        _closeIcon = new QLabel(_header);
        _closeIcon->setAttribute(Qt::WA_Hover);
        _closeIcon->installEventFilter(this);
        _closeIcon->setPixmap(Icon::instance().getPixmap(Icon::Close, Color::primaryText(), 20));
        connect(_closeIcon, &QLabel::linkActivated, this, [this](){closeDrawer(false);});

        QHBoxLayout* layout = new QHBoxLayout(_header);
        layout->setContentsMargins(20, 20, 20, 20);
        layout->setSpacing(0);
        layout->addWidget(text);
        layout->addStretch();
        layout->addWidget(_closeIcon);
    }

    void Drawer::setupBody()
    {
        _bodyLayout = new QVBoxLayout;
        _bodyLayout->setContentsMargins(20, 20, 20, 20);
        _bodyLayout->addWidget(new Text("Hi there!", this));
    }

    void Drawer::setupFooter()
    {
        _footer = new QWidget(this);

        _cancelBtn = new Button("cancel", _footer);

        _confirmBtn = new Button("confirm", _footer);
        _confirmBtn->setType(Button::Type::Primary);

        QHBoxLayout* layout = new QHBoxLayout(_footer);
        layout->setContentsMargins(20, 10, 20, 20);
        layout->setSpacing(10);
        layout->addStretch();
        layout->addWidget(_cancelBtn);
        layout->addWidget(_confirmBtn);

        connect(_cancelBtn, &Button::clicked, this, [this]() {emit rejected();});
        connect(_confirmBtn, &Button::clicked, this, [this]() {emit accepted();});
    }

    void Drawer::updatePosition()
    {
        QWidget* topWidget = parentWidget();

        QRect parentRect = topWidget->rect();
        int parentWidth = parentRect.width();
        int parentHeight = parentRect.height();

        QRect targetRect;
        switch (_direction)
        {
        case Direction::LeftToRight:
            targetRect.setRect(0, 0, parentWidth * 0.3, parentHeight);
            break;
        case Direction::RightToLeft:
            targetRect.setRect(parentWidth * 0.7, 0, parentWidth * 0.3, parentHeight);
            break;
        case Direction::TopToBottom:
            targetRect.setRect(0, 0, parentWidth, parentHeight * 0.3);
            break;
        case Direction::BottomToTop:
            targetRect.setRect(0, parentHeight * 0.7, parentWidth, parentHeight * 0.3);
            break;
        }

        if (isVisible())
        {
            setGeometry(targetRect);
        }
        else
        {
            QRect slideOutRect;
            switch (_direction)
            {
            case Direction::LeftToRight:
                slideOutRect = QRect(-targetRect.width(), targetRect.y(), targetRect.width(), targetRect.height());
                break;
            case Direction::RightToLeft:
                slideOutRect = QRect(parentWidth, targetRect.y(), targetRect.width(), targetRect.height());
                break;
            case Direction::TopToBottom:
                slideOutRect = QRect(targetRect.x(), -targetRect.height(), targetRect.width(), targetRect.height());
                break;
            case Direction::BottomToTop:
                slideOutRect = QRect(targetRect.x(), parentHeight, targetRect.width(), targetRect.height());
                break;
            }
            setGeometry(slideOutRect);
        }
    }

    void Drawer::startOpen()
    {
        if(_modal)
        {
            _mask->setDisabled(true);
            Animation::fadeIn(_mask, Animation::OpacityType::GraphicsEffect, 300, [this](){
                _mask->setDisabled(false);
            });
        }
        else
        {
            _mask->hide();
        }

        Animation::move(this, getSlideInPosition(), 300, [this](){
            emit opened();
        });
    }

    void Drawer::startClose()
    {
        _isClosing = true;

        if(_modal)
        {
            _mask->setDisabled(true);
            Animation::fadeOut(_mask, Animation::OpacityType::GraphicsEffect, 300, [this](){
                _mask->setDisabled(false);
            });
        }
        else
        {
            _mask->hide();
        }

        Animation::move(this, getSlideOutPosition(), 300, [this](){
            QWidget::hide();
            _isClosing = false;
            emit closed();
        });
    }

    void Drawer::closeDrawer(bool expectedClose)
    {
        if (_beforeCloseCallback && !expectedClose)
            _beforeCloseCallback([this](){ startClose(); });
        else
            startClose();
    }

    QRect Drawer::getSlideInPosition()
    {
        QRect currentRect = geometry();
        QRect slideInStart;
        switch (_direction)
        {
        case Direction::LeftToRight:
            slideInStart = QRect(currentRect.x() + currentRect.width(), currentRect.y(),
                                   currentRect.width(), currentRect.height());
            break;
        case Direction::RightToLeft:
            slideInStart = QRect(currentRect.x() - currentRect.width(), currentRect.y(),
                                   currentRect.width(), currentRect.height());
            break;
        case Direction::TopToBottom:
            slideInStart = QRect(currentRect.x(), currentRect.y() + currentRect.height(),
                                   currentRect.width(), currentRect.height());
            break;
        case Direction::BottomToTop:
            slideInStart = QRect(currentRect.x(), currentRect.y() - currentRect.height(),
                                   currentRect.width(), currentRect.height());
            break;
        }
        return slideInStart;
    }

    QRect Drawer::getSlideOutPosition()
    {
        QRect currentRect = geometry();
        QRect slideOutTarget;
        switch (_direction)
        {
        case Direction::LeftToRight:
            slideOutTarget = QRect(currentRect.x() - currentRect.width(), currentRect.y(),
                                 currentRect.width(), currentRect.height());
            break;
        case Direction::RightToLeft:
            slideOutTarget = QRect(currentRect.x() + currentRect.width(), currentRect.y(),
                                 currentRect.width(), currentRect.height());
            break;
        case Direction::TopToBottom:
            slideOutTarget = QRect(currentRect.x(), currentRect.y() - currentRect.height(),
                                 currentRect.width(), currentRect.height());
            break;
        case Direction::BottomToTop:
            slideOutTarget = QRect(currentRect.x(), currentRect.y() + currentRect.height(),
                                 currentRect.width(), currentRect.height());
            break;
        }
        return slideOutTarget;
    }

    bool Drawer::eventFilter(QObject* watched, QEvent* event)
    {
        if (watched == _closeIcon)
        {
            if (event->type() == QEvent::HoverEnter)
            {
                _closeIcon->setPixmap(Icon::instance().getPixmap(Icon::Close, Color::primary(), 20));
                _closeIcon->setCursor(Qt::PointingHandCursor);
                return true;
            }
            else if (event->type() == QEvent::HoverLeave)
            {
                _closeIcon->setPixmap(Icon::instance().getPixmap(Icon::Close, Color::primaryText(), 20));
                _closeIcon->setCursor(Qt::ArrowCursor);
                return true;
            }
            else if (event->type() == QEvent::MouseButtonPress)
            {
                emit _closeIcon->linkActivated("");
            }
        }
        else if (watched == parentWidget())
        {
            if(event->type() == QEvent::Resize || event->type() == QEvent::Move)
            {
                updatePosition();
                return false;
            }
        }
        return QWidget::eventFilter(watched, event);
    }

    void Drawer::showEvent(QShowEvent* event)
    {
        if(_isClosing) return;

        QWidget::showEvent(event);

        setFocus();

        if (_beforeOpenCallback)
            _beforeOpenCallback([this](){ startOpen(); });
        else
            startOpen();
    }

    void Drawer::keyPressEvent(QKeyEvent *event)
    {
        if (event->key() == Qt::Key_Escape)
            closeDrawer(false);
        else
            QWidget::keyPressEvent(event);
    }
}