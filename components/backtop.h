#pragma once

#include <QLabel>
#include <QScrollArea>
#include <QSvgRenderer>

namespace Element
{

    class Backtop : public QLabel
    {
    Q_OBJECT

    public:
        enum class Shape { Circle, Square };
        enum class Size { Large, Default, Small };
        enum class Type { Icon, Text };

    public:
        Backtop& setShape(Shape shape);
        Backtop& setSize(Size size);
        Backtop& setType(Type type);

        Backtop& setTarget(QScrollArea* target);
        Backtop& setVisibilityHeight(int visibilityHeight);
        Backtop& setRight(int right);
        Backtop& setBottom(int bottom);

    public:
        Backtop(QWidget* parent);
        Backtop(QScrollArea* target, QWidget* parent = nullptr);

    protected:
        void paintEvent(QPaintEvent* event) override;
        void mousePressEvent(QMouseEvent* event) override;

    private slots:
            void onScrollBarValueChanged(int value);

    private:
        Shape _shape = Shape::Circle;
        Size _size = Size::Default;
        Type _type = Type::Icon;

    private:
        QScrollArea* _target = nullptr;
        int _visibilityHeight;
        int _right;
        int _bottom;

    private:
        QSvgRenderer* _svgRenderer = nullptr;
    };

}
