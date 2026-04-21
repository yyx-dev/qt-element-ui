#include "dialog.h"
#include "private/animation.h"

#include <QBoxLayout>
#include <QTimer>
#include <QGraphicsDropShadowEffect>
#include <QEventLoop>

namespace Element
{
    Dialog::Dialog(QWidget* parent)
        : Dialog("", "", parent)
    {}

    Dialog::Dialog(const QString& title, const QString& content, QWidget* parent)
        : QDialog(parent)
        , _title(new Text(title, this))
        , _content(new Text(content, this))
        , _cancel(new Button("Cancel", this))
        , _confirm(new Button("Confirm", this))
    {
        setAttribute(Qt::WA_DeleteOnClose);
        setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
        setAttribute(Qt::WA_TranslucentBackground);
        setFixedSize(500, 202);
        setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

        QWidget* outerFrame = new QWidget(this);
        outerFrame->setGeometry(rect());
        QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(outerFrame);
        shadowEffect->setBlurRadius(12);
        shadowEffect->setColor(QColor(0, 0, 0, 102));
        shadowEffect->setOffset(0, 2);
        outerFrame->setGraphicsEffect(shadowEffect);

        QWidget* contentFrame = new QWidget(outerFrame);
        contentFrame->setStyleSheet("background-color: white; border-radius: 4px; border: none;");
        contentFrame->setGeometry(outerFrame->rect());

        _title->setParent(contentFrame);
        _content->setParent(contentFrame);
        _cancel->setParent(contentFrame);
        _confirm->setParent(contentFrame);
        _close = new QLabel(contentFrame);
        _close->setPixmap(Icon::instance().getPixmap(Icon::Close, Color::secondaryText(), 20));
        _close->setAttribute(Qt::WA_Hover);
        _close->installEventFilter(this);

        QHBoxLayout* headerLayout = new QHBoxLayout();
        headerLayout->addWidget(_title);
        headerLayout->addStretch();
        headerLayout->addWidget(_close);

        QVBoxLayout* mainLayout = new QVBoxLayout(contentFrame);
        mainLayout->setContentsMargins(20, 20, 20, 20);
        mainLayout->setSpacing(20);

        QHBoxLayout* buttonLayout = new QHBoxLayout();
        buttonLayout->setSpacing(10);
        buttonLayout->addStretch();
        buttonLayout->addWidget(_cancel);
        buttonLayout->addWidget(_confirm);

        mainLayout->addLayout(headerLayout);
        mainLayout->addWidget(_content);
        mainLayout->addLayout(buttonLayout);

        contentFrame->setLayout(mainLayout);

        QVBoxLayout* outerLayout = new QVBoxLayout(outerFrame);
        outerLayout->setContentsMargins(12, 12, 12, 12);
        outerLayout->addWidget(contentFrame);

        QVBoxLayout* windowLayout = new QVBoxLayout(this);
        windowLayout->setContentsMargins(0, 0, 0, 0);
        windowLayout->addWidget(outerFrame);
        setLayout(windowLayout);

        _title->setSize(Text::Size::Large);
        _confirm->setType(Button::Type::Primary);

        connect(_cancel, &QPushButton::clicked, this, [this]() { closeDialog(QDialog::Rejected, false); });
        connect(_confirm, &QPushButton::clicked, this, [this]() { closeDialog(QDialog::Accepted, false); });

        if (parentWidget())
            parentWidget()->installEventFilter(this);
    }

    Dialog& Dialog::setTitle(const QString &title)
    {
        _title->setText(title);
        return *this;
    }

    Dialog& Dialog::setContent(const QString &content)
    {
        _content->setText(content);
        return *this;
    }

    Dialog& Dialog::setModal(bool modal)
    {
        _modal = modal;
        return *this;
    }

    Dialog& Dialog::setBeforeClose(const std::function<void(std::function<void()>)>& callback)
    {
        _beforeCloseCallback = callback;
        return *this;
    }

    // Dialog::Accepted / Dialog::Rejected / Dialog::Closed
    void Dialog::show()
    {
        QDialog::show();
        getFocus();

        QWidget* pw = qobject_cast<QWidget*>(parent());
        if (pw && _modal)
        {
            _mask = MaskEf::setMask(this, pw);
            connect(_mask, &Mask::clicked, this, [this]() { closeDialog(QDialog::Rejected, true); });
            Animation::fadeIn(_mask, Animation::Type::GraphicsEffect, 300);

            QEventLoop loop;
            connect(this, &QDialog::finished, &loop, &QEventLoop::quit);
            loop.exec();

            return;
        }
    }

    void Dialog::closeDialog(int result, bool emitClosed)
    {
        if (_beforeCloseCallback && emitClosed)
        {
            _beforeCloseCallback([this, result, emitClosed]() {
                doClose(result, emitClosed);
            });
        }
        else
        {
            doClose(result, emitClosed);
        }
    }

    void Dialog::getFocus()
    {
        activateWindow();
        setFocus();
    }

    void Dialog::showEvent(QShowEvent *event)
    {
        QDialog::showEvent(event);

        if (parentWidget())
            updatePosition();

        Animation::fadeInMove(this, Animation::Type::WindowOpacity, -20, 300);
    }

    void Dialog::keyPressEvent(QKeyEvent *event)
    {
        if (event->key() == Qt::Key_Escape)
            closeDialog(QDialog::Rejected, true);
        else
            QDialog::keyPressEvent(event);
    }

    bool Dialog::eventFilter(QObject* watched, QEvent* event)
    {
        if (watched == _close)
        {
            if (event->type() == QEvent::HoverEnter)
            {
                _close->setPixmap(Icon::instance().getPixmap(Icon::Close, Color::primary(), 20));
                _close->setCursor(Qt::PointingHandCursor);
                return true;
            }
            else if (event->type() == QEvent::HoverLeave)
            {
                _close->setPixmap(Icon::instance().getPixmap(Icon::Close, Color::secondaryText(), 20));
                _close->setCursor(Qt::ArrowCursor);
                return true;
            }
            else if (event->type() == QEvent::MouseButtonPress)
            {
                closeDialog(QDialog::Rejected, true);
            }
        }
        else if (watched == parentWidget())
        {
            if(event->type() == QEvent::Resize || event->type() == QEvent::Move)
                updatePosition();
        }
        return QWidget::eventFilter(watched, event);
    }

    void Dialog::doClose(int result, bool emitClosed)
    {
        // Prevents multiple simultaneous close attempts.
        if(isClosing)
            return;

        isClosing = true;

        setResult(result);

        _cancel->setDisabled(true);
        _confirm->setDisabled(true);
        _close->setDisabled(true);
        if(_mask && _modal)
        {
            _mask->setDisabled(true);
            Animation::fadeOut(_mask, Animation::Type::GraphicsEffect, 300);
        }

        Animation::fadeOutMove(this, Animation::Type::WindowOpacity, -20, 300, [this, result, emitClosed]() {
            if (result == QDialog::Accepted)
                emit accepted();
            else if (emitClosed)
                emit closed();
            else
                emit rejected();
            QDialog::close();
        });
    }

    void Dialog::updatePosition()
    {
        if (!parentWidget()) return;

        int parentHeight = parentWidget()->height();
        int targetY = parentWidget()->pos().y() + parentHeight * 0.18;

        move(parentWidget()->pos().x() + (parentWidget()->width() - width()) / 2,
             targetY);
    }
}
