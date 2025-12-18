#include "card.h"
#include "shadow.h"
#include "color.h"
#include "private/utils.h"

#include <QPainter>
#include <QGraphicsDropShadowEffect>

namespace Element
{
    Card::Card(QWidget* parent)
        : Card("", nullptr, "", parent)
    {}
    Card::Card(const QString& header, QWidget* widget, QWidget* parent)
        : Card(header, widget, "", parent)
    {}
    Card::Card(const QString& header, QWidget* widget, const QString& footer, QWidget* parent)
        : QWidget(parent)
        , _header(new QLabel(this))
        , _footer(new QLabel(this))
        , _body(new QWidget(this))
        , _mainLayout(new QVBoxLayout(this))
    {
        setupUI();
        setHeader(header);
        setFooter(footer);
        setBody(widget);

        setMinimumSize(sc(300, 240));
        setMaximumSize(sc(380, 280));
    }

    void Card::setupUI()
    {
        int paddingh = sc(8);
        int paddingv = sc(12);
        _header->setStyleSheet(QString("padding: %1px %2px; border: none; border-bottom: 1px solid #E4E7ED; color: #303133;").arg(paddingh).arg(paddingv));
        _footer->setStyleSheet(QString("padding: %1px %2px; border: none; border-top: 1px solid #E4E7ED; color: #303133; ").arg(paddingh).arg(paddingv));
        _body->setStyleSheet("border: none; color: #303133; ");

        _header->setWordWrap(true);
        _footer->setWordWrap(true);

        _header->setFont(FontHelper(_header->font())
                .setPointSize(Comm::defaultFontSize)
                .getFont());

        _footer->setFont(FontHelper(_footer->font())
                .setPointSize(Comm::defaultFontSize)
                .getFont());

        _mainLayout->setContentsMargins(0, 0, 0, 0);
        _mainLayout->setSpacing(0);
        _mainLayout->addWidget(_header);
        _mainLayout->addWidget(_body, 1);
        _mainLayout->addWidget(_footer);

        ShadowEf::setShadow(this, ShadowEf::Type::Basic);
        setShadow(_shadow);

        setMouseTracking(true);
    }

    Card& Card::setHeader(const QString& header)
    {
        _header->setText(header);
        _header->setVisible(!header.isEmpty());
        return *this;
    }

    Card& Card::setFooter(const QString& footer)
    {
        _footer->setText(footer);
        _footer->setVisible(!footer.isEmpty());
        return *this;
    }

    Card& Card::setBody(QWidget* widget)
    {
        if (widget)
        {
            cleanLayout(_body);
            QVBoxLayout* layout = new QVBoxLayout(_body);
            layout->setContentsMargins(1, 0, 1, 1);
            layout->addWidget(widget);
        }
        return *this;
    }

    Card& Card::setShadow(Shadow shadow)
    {
        _shadow = shadow;
        graphicsEffect()->setEnabled(_shadow == Shadow::Always);
        return *this;
    }

    void Card::paintEvent(QPaintEvent* event)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // 绘制圆角背景
        QPainterPath path;
        path.addRoundedRect(rect().adjusted(0, 0, 0, 0), 4, 4, Qt::AbsoluteSize);
        painter.setClipPath(path);

        // 填充背景
        painter.fillPath(path, Qt::white);

        // 绘制边框
        painter.setPen(QPen(QColor(Color::lightBorder()), 1));
        painter.drawRoundedRect(rect().adjusted(0, 0, 0, 0), 4, 4, Qt::AbsoluteSize);

        QWidget::paintEvent(event);
    }

    void Card::enterEvent(QEvent* event)
    {
        if (_shadow == Shadow::Hover)
            graphicsEffect()->setEnabled(true);
        QWidget::enterEvent(event);
    }

    void Card::leaveEvent(QEvent* event)
    {
        if (_shadow == Shadow::Hover)
            graphicsEffect()->setEnabled(false);
        QWidget::leaveEvent(event);
    }

    void Card::cleanLayout(QWidget* widget)
    {
        if (widget->layout())
        {
            QLayout* oldLayout = widget->layout();
            QLayoutItem* item;

            while ((item = oldLayout->takeAt(0)) != nullptr)
            {
                if (item->widget())
                    delete item->widget();
                delete item;
            }
            delete oldLayout;
        }
    }

}
