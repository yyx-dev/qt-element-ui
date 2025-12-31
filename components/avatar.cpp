#include "avatar.h"
#include "color.h"
#include "private/utils.h"

#include <QPainter>
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#    include <QPainterPath>
#endif


namespace Element
{

    Avatar::Avatar(QWidget* parent)
        : QLabel(parent)
    {
        setSize(_size);
    }

    Avatar::Avatar(Icon::Name icon, QWidget* parent)
        : Avatar(parent)
    {
        setIcon(icon);
    }
    Avatar::Avatar(const QImage& image, QWidget* parent)
        : Avatar(parent)
    {
        setImage(image);
    }
    Avatar::Avatar(const QString& text, QWidget* parent)
        : Avatar(parent)
    {
        setText(text);
    }

    Avatar::Avatar(Icon::Name icon, Shape shape, Size size, QWidget* parent)
        : Avatar(parent)
    {
        setIcon(icon);
        _shape = shape, _size = size;
    }
    Avatar::Avatar(const QImage& image, Shape shape, Size size, QWidget* parent)
        : Avatar(parent)
    {
        setImage(image);
        _shape = shape, _size = size;
    }
    Avatar::Avatar(const QString& text, Shape shape, Size size, QWidget* parent)
        : Avatar(parent)
    {
        setText(text);
        _shape = shape, _size = size;
    }

    Avatar& Avatar::setIcon(Icon::Name icon)
    {
        _type = Type::Icon;
        _svgRenderer = Icon::instance().getRenderer(icon, Color::basicWhite(), this);
        return *this;
    }

    Avatar& Avatar::setImage(const QImage& image)
    {
        _type = Type::Image;

        if (image.isNull())
            _image.load(":/icons/other/avatar-load-failed.png");
        else
            _image = image;

        return *this;
    }

    Avatar& Avatar::setText(const QString& text)
    {
        _type = Type::Text;
        _text = text;
        return *this;
    }

    Avatar& Avatar::setSize(Avatar::Size size)
    {
        _size = size;
        setFixedSize(calcSize(), calcSize());
        return *this;
    }

    Avatar& Avatar::setShape(Avatar::Shape shape)
    {
        _shape = shape;
        return *this;
    }

    void Avatar::paintEvent(QPaintEvent* event)
    {
        Q_UNUSED(event);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        int size = qMin(width(), height());
        int x = (width() - size) / 2;
        int y = (height() - size) / 2;

        QPainterPath clipPath;
        if (_shape == Shape::Circle)
            clipPath.addEllipse(x, y, size, size);
        else if (_shape == Shape::Square)
            clipPath.addRoundedRect(x, y, size, size, 4, 4);
        painter.setClipPath(clipPath);

        painter.setBrush(QColor(Color::disabledText()));
        painter.setPen(Qt::NoPen);
        if (_shape == Shape::Circle)
            painter.drawEllipse(x, y, size, size);
        else if (_shape == Shape::Square)
            painter.drawRoundedRect(x, y, size, size, 4, 4);

        if (_type == Type::Icon && _svgRenderer->isValid())
        {
            if (_size == Size::Default)
                _svgRenderer->render(&painter, QRectF(13, 12, 25, 25));
            else if (_size == Size::Large)
                _svgRenderer->render(&painter, QRectF(15, 15, 30, 30));
            else if (_size == Size::Small)
                _svgRenderer->render(&painter, QRectF(6, 5, 18, 18));
        }
        else if (_type == Type::Text)
        {
            QFont font = FontHelper()
                             .setPointSize(_size == Size::Small ? Comm::smallFontSize : Comm::defaultFontSize)
                             .setBold()
                             .getFont();
            painter.setPen(Qt::white);
            painter.setFont(font);

            QRectF textRect(x, y, size, size);
            painter.drawText(textRect, Qt::AlignCenter, _text);
        }
        else if (_type == Type::Image && !_image.isNull())
        {
            QRectF imageRect(0, 0, calcSize(), calcSize());
            QImage scaledImage = _image.scaled(imageRect.size().toSize(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            painter.drawImage(imageRect, scaledImage);
        }
    }

    int Avatar::calcSize()
    {
        if (_size == Size::Default)
            return 50;
        else if (_size == Size::Small)
            return 30;
        else if (_size == Size::Large)
            return 60;
        else
            return 0;
    }

}
