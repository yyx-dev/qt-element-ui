#pragma once

#include <QWidget>

namespace Element
{

class Watermark : public QWidget
{
    Q_OBJECT
public:
    explicit Watermark(QWidget *parent = nullptr);

    Watermark& setWatermark(const QString &text);
    QString watermark() const;

    //From the Element standard documentation
    QString content() const;
    Watermark& setContent(const QString &content);

    QColor color() const;
    Watermark& setColor(const QColor &color);

    QFont font() const;
    Watermark& setFont(const QFont &font);

    int rotate() const;
    Watermark& setRotate(int rotate);

    QSize gap() const;
    Watermark& setGap(const QSize &gap);

    QPoint offset() const;
    Watermark& setOffset(const QPoint &offset);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    //The default values are from the element standard document.
    QString _content = "Element Plus";
    QColor _color = {0, 0, 0, 38};
    QFont _font;
    int _rotate = -22;
    QSize _gap = {100, 100};
    QPoint _offset = {0, 0};
};

}
