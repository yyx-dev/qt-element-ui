#include "drawer.h"
#include "text.h"
#include "icon.h"
#include "color.h"
#include "private/utils.h"
#include "shadow.h"
#include "mask.h"

#include <QtMath>
#include <QEvent>

namespace Element
{

    Drawer::Drawer(QWidget* topWidget)
        : QWidget(topWidget)
        , _layout(new QVBoxLayout(this))
    {
        setupHeader();
        setupBody();
        setupFooter();

        _layout->addWidget(_header);
        _layout->addLayout(_bodyLayout);
        _layout->addStretch();
        _layout->addWidget(_footer);

        setVisible(false);

        ShadowEf::setShadow(this, ShadowEf::Type::Dark);
        Mask* mask = MaskEf::setMask(this, topWidget);

        connect(mask, &Mask::clicked, this, &Drawer::hide);
    }

    Drawer& Drawer::setBody(QWidget* body)
    {
        _bodyLayout->replaceWidget(_body, body);
        _body = body;
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
        connect(_closeIcon, &QLabel::linkActivated, this, &Drawer::close);

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

        connect(_cancelBtn, &Button::clicked, this, &Drawer::close);
        connect(_confirmBtn, &Button::clicked, this, &Drawer::confirm);
    }

    void Drawer::resizeEvent(QResizeEvent* event)
    {
        QWidget* topWidget = parentWidget();
        QRect rect = topWidget->rect();

        rect.setLeft(qRound(topWidget->rect().width() * 0.7));
        rect.setWidth(qRound(topWidget->rect().width() * 0.3));
        setGeometry(rect);

        QWidget::resizeEvent(event);
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
        return QWidget::eventFilter(watched, event);
    }



}