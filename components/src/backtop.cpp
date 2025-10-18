#include "backtop.h"
#include "icon.h"
#include "color.h"
#include "shadow.h"
#include "base.h"

#include <QPainter>
#include <QMouseEvent>
#include <QScrollBar>


namespace Element
{
    Backtop::Backtop(QWidget* parent)
        : Backtop(nullptr, parent)
    {}

    Backtop::Backtop(QScrollArea* target, QWidget* parent)
        : QLabel(parent)
        , _target(target)
        , _visibilityHeight(200)
        , _right(40)
        , _bottom(40)
        , _svgRenderer(Icon::instance().getRenderer(Icon::CaretTop, Color::primary(), this))
    {
        setShape(_shape);
        setSize(_size);
        setType(_type);

        Element::Shadow::setShadow(this, Element::Shadow::Type::Lighter);

        setVisible(false);
        setCursor(Qt::PointingHandCursor);

        if (_target) {
            connect(_target->verticalScrollBar(), &QScrollBar::valueChanged,
                    this, &Backtop::onScrollBarValueChanged);
        }
    }

    Backtop& Backtop::setShape(Shape shape)
    {
        _shape = shape;
        return *this;
    }

    Backtop& Backtop::setSize(Size size)
    {
        _size = size;
        if (_size == Size::Default) setFixedSize(60, 60);
        else if (_size == Size::Large) setFixedSize(80, 80);
        else if (_size == Size::Small) setFixedSize(40, 40);
        return *this;
    }

    Backtop& Backtop::setType(Type type)
    {
        _type = type;
        return *this;
    }

    Backtop& Backtop::setTarget(QScrollArea* target)
    {
        if (_target)
            disconnect(_target->verticalScrollBar(), &QScrollBar::valueChanged, this, &Backtop::onScrollBarValueChanged);

        _target = target;

        if (_target)
            connect(_target->verticalScrollBar(), &QScrollBar::valueChanged, this, &Backtop::onScrollBarValueChanged);

        return *this;
    }

    Backtop& Backtop::setVisibilityHeight(int visibilityHeight)
    {
        _visibilityHeight = visibilityHeight;
        return *this;
    }

    Backtop& Backtop::setRight(int right)
    {
        _right = right;
        return *this;
    }

    Backtop& Backtop::setBottom(int bottom)
    {
        _bottom = bottom;
        return *this;
    }

    void Backtop::paintEvent(QPaintEvent* event)
    {
        Q_UNUSED(event);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        int size = qMin(width(), height());
        int x = (width() - size) / 2;
        int y = (height() - size) / 2;

        QPainterPath clipPath;
        if (_shape == Shape::Circle)      clipPath.addEllipse(x, y, size, size);
        else if (_shape == Shape::Square) clipPath.addRoundedRect(x, y, size, size, 4, 4);
        painter.setClipPath(clipPath);

        painter.setBrush(Qt::white);
        painter.setPen(Qt::NoPen);
        if (_shape == Shape::Circle)      painter.drawEllipse(x, y, size, size);
        else if (_shape == Shape::Square) painter.drawRoundedRect(x, y, size, size, 4, 4);

        if (_type == Type::Icon && _svgRenderer->isValid())
        {
            if (_size == Size::Default)    _svgRenderer->render(&painter, QRectF(18, 18, 25, 25));
            else if (_size == Size::Large) _svgRenderer->render(&painter, QRectF(25, 25, 30, 30));
            else if (_size == Size::Small) _svgRenderer->render(&painter, QRectF(11, 10, 18, 18));
        }
        else
        {
            QFont font = QLabel::font();
            font.setFamilies(Comm::fontFmailies);
            font.setBold(true);
            if (_size == Size::Default || _size == Size::Large) font.setPointSize(14);
            else if (_size == Size::Small) font.setPointSize(Comm::defaultFontSize);

            painter.setPen(Color::primary());
            painter.setFont(font);

            QRectF textRect(x, y, size, size);
            painter.drawText(textRect, Qt::AlignCenter, "UP");
        }
    }

    void Backtop::mousePressEvent(QMouseEvent* event)
    {
        if (event->button() == Qt::LeftButton && _target)
            _target->verticalScrollBar()->setValue(0);

        QLabel::mousePressEvent(event);
    }

    void Backtop::onScrollBarValueChanged(int value)
    {
        setVisible(value > _visibilityHeight);
    }

}
