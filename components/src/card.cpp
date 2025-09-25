#include "card.h"
#include "shadow.h"
#include "color.h"
#include "tools/commvar.h"

#include <QPainter>
#include <QDebug>

namespace Element
{
    Card::Card(QWidget* parent)
        : Card("", QStringList(), "", parent)
    {}
    Card::Card(const QStringList& contents, QWidget* parent)
        : Card("", contents, "", parent)
    {}
    Card::Card(const QString& header, const QStringList& contents, QWidget* parent)
        : Card(header, contents, "", parent)
    {}
    Card::Card(const QString& header, const QStringList& contents, const QString& footer, QWidget* parent)
        : QWidget(parent)
        , _header(new QLabel(this))
        , _footer(new QLabel(this))
        , _body(new QWidget(this))
        , _mainLayout(new QVBoxLayout(this))
    {
        setupUI();
        setHeader(header);
        setFooter(footer);
        setBody(contents);
    }

    Card::Card(const QString& header, QWidget* widget, QWidget* parent)
        : Card(header, widget, "", parent)
    {}
    Card::Card(const QString& header, QWidget* widget, const QString& footer, QWidget* parent)
        : QWidget(parent)
        , _header(new QLabel(this))
        , _footer(new QLabel(this))
        , _body(widget)
        , _mainLayout(new QVBoxLayout(this))
    {
        setupUI();
        setHeader(header);
        setFooter(footer);
        setBody(widget);
    }

    void Card::setupUI()
    {
        _header->setStyleSheet("padding: 18px 20px; border: none; border-bottom: 1px solid #E4E7ED; color: #303133; ");
        _footer->setStyleSheet("padding: 18px 20px; border: none; border-top: 1px solid #E4E7ED; color: #303133; ");
        _body->setStyleSheet("padding: 20px; border: none; color: #303133; ");

        _header->setWordWrap(true);
        _footer->setWordWrap(true);

        QFont font = _header->font();
        font.setFamilies(CommonVar::fontFmailies);
        font.setPointSize(10);
        _header->setFont(font);

        font = _footer->font();
        font.setFamilies(CommonVar::fontFmailies);
        font.setPointSize(10);
        _footer->setFont(font);

        _mainLayout->setContentsMargins(0, 0, 0, 0);
        _mainLayout->setSpacing(0);
        _mainLayout->addWidget(_header);
        _mainLayout->addWidget(_body);
        _mainLayout->addWidget(_footer);

        setLayout(_mainLayout);

        Element::Shadow::setShadow(this, Element::Shadow::Type::Basic);
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

    Card& Card::setBody(const QStringList& contents)
    {
        cleanLayout(_body);

        QVBoxLayout* bodyLayout = new QVBoxLayout(_body);
        bodyLayout->setContentsMargins(0, 0, 0, 0);
        bodyLayout->setSpacing(10);

        for (const QString& content : contents)
        {
            QLabel* label = new QLabel(content, _body);
            label->setStyleSheet("border: none; ");
            label->setWordWrap(true);

            QFont font = label->font();
            font.setFamilies(CommonVar::fontFmailies);
            font.setPointSize(10);
            label->setFont(font);

            bodyLayout->addWidget(label);
        }

        return *this;
    }

    Card& Card::setBody(const QImage& image)
    {
        cleanLayout(_body);

        QLabel* imageLabel = new QLabel(_body);
        imageLabel->setPixmap(QPixmap::fromImage(image));
        imageLabel->setScaledContents(true);

        QVBoxLayout* bodyLayout = new QVBoxLayout(_body);
        bodyLayout->setContentsMargins(0, 0, 0, 0);
        bodyLayout->addWidget(imageLabel);

        return *this;
    }

    Card& Card::setBody(QWidget* widget)
    {
        cleanLayout(_body);

        QVBoxLayout* bodyLayout = new QVBoxLayout(_body);
        bodyLayout->setContentsMargins(0, 0, 0, 0);
        bodyLayout->addWidget(widget);

        return *this;
    }

    Card& Card::setShadow(Shadow shadow)
    {
        _shadow = shadow;

        if (_shadow == Shadow::Always)
            graphicsEffect()->setEnabled(true);
        else
            graphicsEffect()->setEnabled(false);

        return *this;
    }


    void Card::paintEvent(QPaintEvent* event)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // 绘制圆角背景
        QPainterPath path;
        path.addRoundedRect(rect().adjusted(1, 1, -1, -1), 4, 4, Qt::AbsoluteSize);
        painter.setClipPath(path);

        // 填充背景
        painter.fillPath(path, Qt::white);

        // 绘制边框
        painter.setPen(QPen(QColor(Color::lightBorder()), 1));
        painter.drawRoundedRect(rect().adjusted(1, 1, -1, -1), 4, 4, Qt::AbsoluteSize);

        QWidget::paintEvent(event);
    }

    // 新增：处理鼠标进入事件
    void Card::enterEvent(QEvent* event)
    {
        if (_shadow == Shadow::Hover)
            graphicsEffect()->setEnabled(true);
        QWidget::enterEvent(event);
    }

    // 新增：处理鼠标离开事件
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
