#include "watermark.h"
#include <QPainter>

namespace Element
{

    Watermark::Watermark(QWidget *parent)
        : QWidget{parent}
    {}

    QString Watermark::content() const
    {
        return m_content;
    }

    void Watermark::setContent(const QString &content)
    {
        if(m_content == content)
        {
            return;
        }

        m_content = content;
        update();
    }

    QColor Watermark::color() const
    {
        return m_color;
    }

    void Watermark::setColor(const QColor &color)
    {
        if(m_color == color)
        {
            return;
        }

        m_color = color;
        update();
    }


    QFont Watermark::font() const
    {
        return m_font;
    }

    void Watermark::setFont(const QFont &font)
    {
        if(m_font == font)
        {
            return;
        }

        m_font = font;
        update();
    }

    int Watermark::rotate() const
    {
        return m_rotate;
    }

    void Watermark::setRotate(int rotate)
    {
        if(m_rotate == rotate)
        {
            return;
        }

        m_rotate = rotate;
        update();
    }

    QSize Watermark::gap() const
    {
        return m_gap;
    }

    void Watermark::setGap(const QSize &gap)
    {
        if(m_gap == gap)
        {
            return;
        }

        m_gap = gap;
        update();
    }

    QPoint Watermark::offset() const
    {
        return m_offset;
    }

    void Watermark::setOffset(const QPoint &offset)
    {
        if(m_offset == offset)
        {
            return;
        }

        m_offset = offset;
        update();
    }


    void Watermark::paintEvent(QPaintEvent *event)
    {
        Q_UNUSED(event)
        QPainter painter(this);
        painter.setRenderHint(QPainter::TextAntialiasing);

        QFont font(m_font);
        painter.setFont(font);
        painter.setPen(m_color);

        //rotate the canvas
        painter.translate(width() / 2, height() / 2);
        painter.rotate(m_rotate);
        painter.translate(-width() / 2, -height() / 2);

        for (int y = -height() + m_offset.y(); y < height() * 2; y += m_gap.height())
        {
            for (int x = -width() + m_offset.x(); x < width() * 2; x += m_gap.width())
            {
                QRect rect(x, y, m_gap.width(), m_gap.height());
                painter.drawText(rect, Qt::AlignCenter, m_content);
            }
        }
    }
}
