#pragma once

#include "icon.h"

#include <QString>
#include <QLabel>
#include <QFile>

namespace Element
{

    class Avatar : public QLabel
    {
    Q_OBJECT

    public:
        enum class Shape
        {
            Circle,
            Square
        };

        enum class Size
        {
            Default,
            Small,
            Large,
        };

         enum Type { Icon, Image, Text };

    public:
        void setIcon(Icon::Name icon = Icon::UserFilled);
        void setImage(const QImage& file = QImage(":/icons/other/example-avatar.png"));
        void setText(const QString& text = "user");

        void setSize(Size size);
        void setShape(Shape shape);

    public:
        Avatar(QWidget* parent = nullptr);
        Avatar(Icon::Name icon, QWidget* parent = nullptr);
        Avatar(const QImage& file, QWidget* parent = nullptr);
        Avatar(const QString& text, QWidget* parent = nullptr);

        Avatar(Icon::Name icon, Shape shape = Shape::Circle, Size size = Size::Default, QWidget* parent = nullptr);
        Avatar(const QImage& file, Shape shape = Shape::Circle, Size size = Size::Default, QWidget* parent = nullptr);
        Avatar(const QString& text, Shape shape = Shape::Circle, Size size = Size::Default, QWidget* parent = nullptr);

    protected:
        void paintEvent(QPaintEvent* event) override;

    private:
        int calcSize();

    private:
        Shape _shape = Shape::Circle;
        Size _size = Size::Default;
        Type _type;

    private:
        QSvgRenderer* _svgRenderer;
        QString _text;
        QImage _image;
    };

}
