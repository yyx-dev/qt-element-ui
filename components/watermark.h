#pragma once

#include <QWidget>

namespace Element
{

    class Watermark : public QWidget
    {
        Q_OBJECT
    public:
        explicit Watermark(QWidget *parent = nullptr);

        QString content() const;
        void setContent(const QString &content);

        QColor color() const;
        void setColor(const QColor &color);

        QFont font() const;
        void setFont(const QFont &font);

        int rotate() const;
        void setRotate(int rotate);

        QSize gap() const;
        void setGap(const QSize &gap);

        QPoint offset() const;
        void setOffset(const QPoint &offset);

    protected:
        void paintEvent(QPaintEvent *event) override;

    private:
        QString m_content{"Element Plus"};
        QColor m_color{0, 0, 0, 38};
        QFont m_font{"黑体", 10};
        int m_rotate{-22};
        QSize m_gap{100, 100};
        QPoint m_offset{0, 0};
    };

}
