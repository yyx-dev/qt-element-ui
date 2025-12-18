#include "carousel.h"
#include "icon.h"
#include "color.h"
#include "private/utils.h"

#include <QPainter>
#include <QMouseEvent>

namespace Element
{
    Carousel::Carousel(QWidget *parent)
        : Carousel({}, parent)
    {}

    Carousel::Carousel(const QList<QPixmap>& images, QWidget* parent)
        : QWidget(parent)
        , _leftArrowRenderer(Icon::instance().getRenderer(Icon::Name::ArrowLeft, Color::blankFill(), this))
        , _rightArrowRenderer(Icon::instance().getRenderer(Icon::Name::ArrowRight, Color::blankFill(), this))
    {
        foreach (auto& image, images)
            addImage(image);

        setMouseTracking(true);
    }

    Carousel& Carousel::setTigger(Trigger trigger)
    {
        _trigger = trigger;
        return *this;
    }

    Carousel& Carousel::setIndicatorPos(IndicatorPos pos)
    {
        _indicatorPos = pos;
        return *this;
    }

    Carousel& Carousel::setArrow(Arrow arrow)
    {
        _arrow = arrow;
        return *this;
    }

    Carousel& Carousel::setAutoplay(bool autoplay)
    {
        _autoplay = autoplay;
        return *this;
    }

    Carousel& Carousel::setInterval(int interval)
    {
        _interval = interval;
        return *this;
    }

    Carousel& Carousel::setType(Type type)
    {
        _type = type;
        return *this;
    }

    Carousel& Carousel::setCardScale(double scale)
    {
        _cardScale = scale;
        return *this;
    }

    Carousel& Carousel::setLoop(bool loop)
    {
        _loop = loop;
        return *this;
    }

    Carousel& Carousel::setDirection(Direction direction)
    {
        _direction = direction;
        return *this;
    }

    Carousel& Carousel::setPauseOnHover(bool pauseOnHover)
    {
        _pauseOnHover = pauseOnHover;
        return *this;
    }

    Carousel& Carousel::addImage(const QPixmap& image)
    {
        _images.append(image);
        return *this;
    }

    void Carousel::paintEvent(QPaintEvent *event)
    {
        QWidget::paintEvent(event);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setRenderHint(QPainter::SmoothPixmapTransform);

        if (!_images.isEmpty())
        {
            const QPixmap& pixmap = _images.at(_index);

            QRect drawRect = rect();

            if (_type == Type::Default)
            {
                painter.drawPixmap(drawRect, pixmap);
            }
            else if (_type == Type::Card)
            {
                QSize scaledSize = pixmap.size();
                scaledSize.scale(drawRect.size() * _cardScale, Qt::KeepAspectRatio);

                QRect targetRect(QPoint(0, 0), scaledSize);
                targetRect.moveCenter(drawRect.center());

                painter.drawPixmap(targetRect, pixmap);
            }
        }

        if ((_arrow == Arrow::Always) || (_arrow == Arrow::Hover && underMouse()))
        {
            QColor bg = _leftArrowHovered ? QColor(31, 45, 61, int(0.23 * 255)) : QColor(31, 45, 61, int(0.11 * 255));
            painter.setBrush(bg);
            painter.setPen(Qt::NoPen);
            painter.drawEllipse(_leftArrowRect);

            if (_leftArrowRenderer->isValid())
            {
                QRect iconRect(0, 0, sc(12), sc(12));
                iconRect.moveCenter(_leftArrowRect.center());
                _leftArrowRenderer->render(&painter, iconRect);
            }

            QColor bgRight = _rightArrowHovered ? QColor(31, 45, 61, int(0.23 * 255)) : QColor(31, 45, 61, int(0.11 * 255));
            painter.setBrush(bgRight);
            painter.setPen(Qt::NoPen);
            painter.drawEllipse(_rightArrowRect);

            if (_rightArrowRenderer->isValid())
            {
                QRect iconRect(0, 0, sc(12), sc(12));
                iconRect.moveCenter(_rightArrowRect.center());
                _rightArrowRenderer->render(&painter, iconRect);
            }
        }

        if (_indicatorPos != IndicatorPos::None && !_images.isEmpty() && !_indicatorRects.isEmpty())
        {
            for (int i = 0; i < _indicatorRects.size(); ++i)
            {
                painter.setBrush(QColor(255, 255, 255, i == _index ? 255 : int(0.48 * 255)));
                painter.setPen(Qt::NoPen);

                const QRect& rect = _indicatorRects[i];
                painter.drawRect(rect);
            }
        }

    }

    void Carousel::enterEvent(QEvent* event)
    {
        if (_arrow != Arrow::Never)
            update();
        QWidget::enterEvent(event);
    }

    void Carousel::leaveEvent(QEvent* event)
    {
        if (_arrow != Arrow::Never)
            update();
        QWidget::leaveEvent(event);
    }

    void Carousel::mouseMoveEvent(QMouseEvent* event)
    {
        // check arrows hover
        bool leftChanged = _leftArrowHovered != _leftArrowRect.contains(event->pos());
        bool rightChanged = _rightArrowHovered != _rightArrowRect.contains(event->pos());

        _leftArrowHovered = _leftArrowRect.contains(event->pos());
        _rightArrowHovered = _rightArrowRect.contains(event->pos());


        // check indicators hover
        int hoveredIndicator = -1;
        if (_indicatorPos != IndicatorPos::None && !_indicatorRects.isEmpty())
        {
            for (int i = 0; i < _indicatorRects.size(); ++i)
            {
                if (_indicatorRects[i].contains(event->pos()))
                {
                    hoveredIndicator = i;
                    break;
                }
            }
        }

        bool indicatorHovered = (hoveredIndicator != -1);
        bool indicatorChanged = _hoveredIndicatorIndex != hoveredIndicator;
        _hoveredIndicatorIndex = hoveredIndicator;

        if (_leftArrowHovered || _rightArrowHovered || indicatorHovered)
            setCursor(Qt::PointingHandCursor);
        else
            unsetCursor();

        if (leftChanged || rightChanged || indicatorChanged)
            update();

        QWidget::mouseMoveEvent(event);
    }

    void Carousel::mousePressEvent(QMouseEvent* event)
    {
        if (event->button() == Qt::LeftButton)
        {
            if (_leftArrowRect.contains(event->pos()))
            {
                showPrevious();
                return;
            }
            else if (_rightArrowRect.contains(event->pos()))
            {
                showNext();
                return;
            }

            if (_indicatorPos != IndicatorPos::None && !_indicatorRects.isEmpty())
            {
                for (int i = 0; i < _indicatorRects.size(); ++i)
                {
                    if (_indicatorRects[i].contains(event->pos()))
                    {
                        if (_index != i)
                        {
                            _index = i;
                            update();
                        }
                        return;
                    }
                }
            }
        }

        QWidget::mousePressEvent(event);
    }

    void Carousel::showEvent(QShowEvent* event)
    {
        static bool first = true;
        if (first)
        {
            calcArrowPos();
            calcIndicatorPos();
            first = false;
        }

        QWidget::showEvent(event);
    }

    void Carousel::showPrevious()
    {
        if (_images.isEmpty()) return;

        if (_index > 0)
            --_index;
        else if (_loop)
            _index = _images.size() - 1;

        update();
    }

    void Carousel::showNext()
    {
        if (_images.isEmpty()) return;

        if (_index < _images.size() - 1)
            ++_index;
        else if (_loop)
            _index = 0;

        update();
    }

    void Carousel::calcArrowPos()
    {
        if (_arrow == Arrow::Never)
            return;

        const int diameter = 36;
        const int radius = diameter / 2;
        const int margin = 20 + radius;
        const QPoint center = rect().center();
        const int y = center.y();

        _leftArrowRect = QRect(margin - radius, y - radius, diameter, diameter);
        _rightArrowRect = QRect(width() - margin - radius, y - radius, diameter, diameter);
    }

    void Carousel::calcIndicatorPos()
    {
        if (_indicatorPos == IndicatorPos::None || _images.isEmpty())
        {
            _indicatorRects.clear();
            return;
        }

        const int indicatorW = 30;
        const int indicatorH = 2;
        const int spacing = 10;
        const int totalW = _images.size() * indicatorW + (_images.size() - 1) * spacing;
        const int startX = (width() - totalW) / 2;
        const int y = height() - 25 - indicatorH / 2;

        _indicatorRects.clear();
        _indicatorRects.reserve(_images.size());

        for (int i = 0; i < _images.size(); ++i)
        {
            QRect rect(startX + i * (indicatorW + spacing),
                    y - indicatorH / 2,
                    indicatorW,
                    indicatorH);
            _indicatorRects.append(rect);
        }
    }

}