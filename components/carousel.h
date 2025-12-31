#pragma once

#include "image.h"

#include <QSvgRenderer>
#include <QWidget>


namespace Element
{

    class Carousel : public QWidget
    {
        Q_OBJECT
    public:
        enum class Trigger
        {
            Hover,
            Click,
        };

        enum class IndicatorPos
        {
            Inside,
            Outside,
            None,
        };

        enum class Arrow
        {
            Always,
            Hover,
            Never,
        };

        enum class Type
        {
            Default,
            Card,
        };

        enum class Direction
        {
            Horizontal,
            Vertical,
        };

    public:
        Carousel& setTigger(Trigger trigger);
        Carousel& setIndicatorPos(IndicatorPos pos);
        Carousel& setArrow(Arrow arrow);
        Carousel& setAutoplay(bool autoplay);
        Carousel& setInterval(int interval);
        Carousel& setType(Type type);
        Carousel& setCardScale(double scale);
        Carousel& setLoop(bool loop);
        Carousel& setDirection(Direction direction);
        Carousel& setPauseOnHover(bool pauseOnHover);
        Carousel& addImage(const QPixmap& image);

    public:
        Carousel(QWidget* parent = nullptr);
        Carousel(const QList<QPixmap>& images, QWidget* parent = nullptr);

    protected:
        void paintEvent(QPaintEvent* event) override;
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        void enterEvent(QEnterEvent* event) override;
#else
        void enterEvent(QEvent* event) override;
#endif
        void leaveEvent(QEvent* event) override;
        void mouseMoveEvent(QMouseEvent* event) override;
        void mousePressEvent(QMouseEvent* event) override;
        void showEvent(QShowEvent* event) override;

    private:
        void showPrevious();
        void showNext();
        void calcArrowPos();
        void calcIndicatorPos();

    private:
        Trigger _trigger = Trigger::Click;
        IndicatorPos _indicatorPos = IndicatorPos::Inside;
        Arrow _arrow = Arrow::Hover;
        bool _autoplay = true;
        int _interval = 3000;
        Type _type = Type::Default;
        double _cardScale = 0.83;
        bool _loop = true;
        Direction _direction = Direction::Horizontal;
        bool _pauseOnHover = true;

    private:
        QList<QPixmap> _images;
        int _index = 0;

        bool _leftArrowHovered = false;
        bool _rightArrowHovered = false;
        QSvgRenderer* _leftArrowRenderer = nullptr;
        QSvgRenderer* _rightArrowRenderer = nullptr;
        QRect _leftArrowRect;
        QRect _rightArrowRect;

        QList<QRect> _indicatorRects;
        int _hoveredIndicatorIndex = -1;
    };

}
