#include "divider.h"
#include "text.h"

namespace Element
{
    QString Divider::getLineStyleString(LineStyle style)
    {
        switch (style)
        {
        case LineStyle::Solid:      return "solid";
        case LineStyle::Dashed:     return "dashed";
        case LineStyle::Dotted:     return "dotted";
        case LineStyle::DashDotLine:  return "dashDotLine";
        case LineStyle::DashDotDotLine:  return "dashDotDotLine";
        default:                    return "solid";
        }
    }

    HDivider::HDivider(QWidget* parent)
        : Divider(parent)
    {
        init();
        adjust(ContentPosition::Empty);
    }

    HDivider::HDivider(const QString& text, HDivider::ContentPosition conPos, QWidget* parent)
        : Divider(parent)
    {
        init();
        if(conPos == ContentPosition::Empty) return;

        QLabel* txt = new QLabel(this);
        txt->setText(text);
        txt->setAlignment(Qt::AlignCenter);
        QFont font = FontHelper().getFont();
        font.setPointSize(10);
        txt->setFont(font);
        setContent(txt);
        adjust(conPos);
    }

    HDivider::HDivider(QWidget* content, ContentPosition conPos, QWidget* parent)
        : Divider(parent)
    {
        init();
        setContent(content);
        adjust(conPos);
    }

    HDivider::HDivider(const QPixmap& pm, ContentPosition conPos, QWidget* parent)
        : Divider(parent)
    {
        init();
        QLabel* l = new QLabel(_content);
        l->setPixmap(pm);
        setContent(l);
        adjust(conPos);
    }

    HDivider& HDivider::setSpacing(int spacing)
    {
        this->layout()->setSpacing(spacing);
        return *this;
    }

    HDivider& HDivider::setPixmap(const QPixmap& pm)
    {
        QLabel* l = new QLabel(_content);
        l->setPixmap(pm);
        setContent(l);
        return *this;
    }

    HDivider& HDivider::setText(const QString text)
    {
        QLabel* txt = new QLabel(this);
        txt->setText(text);
        txt->setAlignment(Qt::AlignCenter);
        QFont font = FontHelper().getFont();
        font.setPointSize(10);
        txt->setFont(font);
        setContent(txt);

        if(_conPos == ContentPosition::Empty)
            adjust(ContentPosition::Center);

        return *this;
    }

    HDivider& HDivider::setContent(QWidget* content)
    {
        if(content)
        {
            QLayout* layout = _content->layout();
            QWidget* widget = nullptr;

            if (layout->count() > 0)
            {
                QLayoutItem* item = layout->itemAt(0);
                if (item) widget = item->widget();
            }

            if (widget == content) return *this;

            while (layout->count() > 0)
            {
                QLayoutItem* item = layout->takeAt(0);
                if (QWidget* w = item->widget())
                    w->deleteLater();

                delete item;
            }

            layout->addWidget(content);
            _content->setVisible(true);
        }
        else
        {
            _content->setVisible(false);
            _rightLine->setVisible(false);
        }

        return *this;
    }

    HDivider& HDivider::setContentPosition(HDivider::ContentPosition conPos)
    {
        adjust(conPos);
        return *this;
    }

    HDivider& HDivider::setLineColor(const QString& color)
    {
        _leftLine->setLineColor(color);
        _rightLine->setLineColor(color);
        return *this;
    }

    HDivider& HDivider::setLineStyle(Divider::LineStyle ls)
    {
        _leftLine->setLineStyle(ls);
        _rightLine->setLineStyle(ls);
        return *this;
    }

    void HDivider::init()
    {
        QHBoxLayout* layout= new QHBoxLayout(this);
        layout->setContentsMargins(0, 0, 0, 0);
        _leftLine = new HLine();
        layout->addWidget(_leftLine);

        _content = new QWidget(this);
        QHBoxLayout* l = new QHBoxLayout(_content);
        l->setContentsMargins(0, 0, 0, 0);
        layout->addWidget(_content);

        _rightLine = new HLine();
        layout->addWidget(_rightLine);
        layout->setSpacing(20);
    }

    void HDivider::adjust(ContentPosition conPos)
    {
        if(_content->layout()->count()>0 && (conPos != ContentPosition::Empty))
        {
            _content->setVisible(true);
            _rightLine->setVisible(true);

            int streFactor1 = 0, streFactor2 = 0, streFactor3 = 0;
            switch (conPos)
            {
            case ContentPosition::Center:
                streFactor1 = streFactor3 = 1;
                streFactor2 = 0;
                break;
            case ContentPosition::Left:
                streFactor1 = streFactor2 = 0;
                streFactor3 = 1;
                break;
            case ContentPosition::Right:
                streFactor2 = streFactor3 = 0;
                streFactor1 = 1;
                break;
            case ContentPosition::Empty:
                break;
            }

            QBoxLayout* layout = qobject_cast<QBoxLayout*>(this->layout());
            layout->setStretchFactor(_leftLine, streFactor1);
            layout->setStretchFactor(_content, streFactor2);
            layout->setStretchFactor(_rightLine, streFactor3);
            _conPos = conPos;
        }
        else
        {
            _content->setVisible(false);
            _rightLine->setVisible(false);
        }
    }

    HDivider::ContentPosition HDivider::getContentPosition()
    {
        return _conPos;
    }

    Divider::Direction HDivider::getDirection() const
    {
        return Direction::Horizontal;
    }

    VDivider::VDivider(QWidget* parent)
        : Divider(parent)
    {
        setFixedWidth(1);
        setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        setProperty("color", "#dcdfe6");
        setProperty("style", "solid");
    }

    Divider::Direction VDivider::getDirection() const
    {
        return Direction::Vertical;
    }

    VDivider& VDivider::setLineColor(const QString& color)
    {
        if (color != property("color").toString())
        {
            setProperty("color", color);
            update();
        }
        return *this;
    }

    VDivider& VDivider::setLineStyle(Divider::LineStyle ls)
    {
        QString style = Divider::getLineStyleString(ls);
        if (style != property("style").toString())
        {
            setProperty("style", style);
            update();
        }
        return *this;
    }

    void VDivider::paintEvent(QPaintEvent*)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, false);

        QString color = property("color").toString();
        QString style = property("style").toString();

        QPen pen;
        pen.setColor(QColor(color));
        pen.setWidth(1);
        if (style == "solid")
            pen.setStyle(Qt::SolidLine);
        else if (style == "dashed")
            pen.setStyle(Qt::DashLine);
        else if (style == "dotted")
            pen.setStyle(Qt::DotLine);
        else if(style == "dashDotLine")
            pen.setStyle(Qt::DashDotLine);
        else if(style == "dashDotDotLine")
            pen.setStyle(Qt::DashDotDotLine);
        painter.setPen(pen);
        painter.drawLine(0, 0, 0, height());
    }

    HLine::HLine(QWidget* parent)
        : QWidget(parent)
    {
        setFixedHeight(1);
        setMinimumWidth(20);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        setProperty("color", "#dcdfe6");
        setProperty("style", "solid");
    }

    HLine& HLine::setLineColor(const QString& color)
    {
        if (color != property("color").toString())
        {
            setProperty("color", color);
            update();
        }
        return *this;
    }

    HLine& HLine::setLineStyle(Divider::LineStyle ls)
    {
        QString style = Divider::getLineStyleString(ls);
        if (style != property("style").toString())
        {
            setProperty("style", style);
            update();
        }
        return *this;
    }

    void HLine::paintEvent(QPaintEvent*)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, false);

        QString color = property("color").toString();
        QString style = property("style").toString();

        QPen pen;
        pen.setColor(QColor(color));
        pen.setWidth(1);
        if (style == "solid")
            pen.setStyle(Qt::SolidLine);
        else if (style == "dashed")
            pen.setStyle(Qt::DashLine);
        else if (style == "dotted")
            pen.setStyle(Qt::DotLine);
        else if(style == "dashDotLine")
            pen.setStyle(Qt::DashDotLine);
        else if(style == "dashDotDotLine")
            pen.setStyle(Qt::DashDotDotLine);
        painter.setPen(pen);
        painter.drawLine(0, 0, width(), 0);
    }
}