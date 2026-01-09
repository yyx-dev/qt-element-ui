#include "watermark.h"
#include "utils.h"
#include <QPainter>

namespace Element
{
Watermark::Watermark(QWidget *parent)
    : QWidget{parent}
{
    setFont(FontHelper(QWidget::font()).setPointSize(Comm::defaultFontSize).getFont());
}

Watermark &Watermark::setWatermark(const QString &text)
{
    return setContent(text);
}

QString Watermark::watermark() const
{
    return content();
}

QString Watermark::content() const
{
    return _content;
}

Watermark &Watermark::setContent(const QString &content)
{
    if(_content == content)
    {
        return *this;
    }

    _content = content;
    update();
    return *this;
}

QColor Watermark::color() const
{
    return _color;
}

Watermark &Watermark::setColor(const QColor &color)
{
    if(_color == color)
    {
        return *this;
    }

    _color = color;
    update();
    return *this;
}


QFont Watermark::font() const
{
    return _font;
}

Watermark &Watermark::setFont(const QFont &font)
{
    if(_font == font)
    {
        return *this;
    }

    _font = font;
    update();
    return *this;
}

int Watermark::rotate() const
{
    return _rotate;
}

Watermark &Watermark::setRotate(int rotate)
{
    if(_rotate == rotate)
    {
        return *this;
    }

    _rotate = rotate;
    update();
    return *this;
}

QSize Watermark::gap() const
{
    return _gap;
}

Watermark& Watermark::setGap(const QSize &gap)
{
    if(_gap == gap)
    {
        return *this;
    }

    _gap = gap;
    update();
    return *this;
}

QPoint Watermark::offset() const
{
    return _offset;
}

Watermark& Watermark::setOffset(const QPoint &offset)
{
    if(_offset == offset)
    {
        return *this;
    }

    _offset = offset;
    update();
    return *this;
}


void Watermark::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::TextAntialiasing);

    QFont font(_font);
    painter.setFont(font);
    painter.setPen(_color);

    //rotate the canvas
    painter.translate(width() / 2, height() / 2);
    painter.rotate(_rotate);
    painter.translate(-width() / 2, -height() / 2);

    for (int y = -height() + _offset.y(); y < height() * 2; y += _gap.height())
    {
        for (int x = -width() + _offset.x(); x < width() * 2; x += _gap.width())
        {
            QRect rect(x, y, _gap.width(), _gap.height());
            painter.drawText(rect, Qt::AlignCenter, _content);
        }
    }
}
}
