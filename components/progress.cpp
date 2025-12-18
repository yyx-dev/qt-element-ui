#include "progress.h"
#include "private/utils.h"
#include "color.h"
#include "icon.h"

#include <QPainter>

namespace Element
{
    Progress::Progress(QWidget* parent)
        : Progress(0, parent)
    {}

    Progress::Progress(int percentage, QWidget* parent)
        : QWidget(parent)
        , _precentage(percentage)
    {
        setFont(FontHelper().setPointSize(sc(8)).getFont());
    }

    Progress& Progress::setPercentage(int percentage)
    {
        _precentage = percentage;
        update();
        return *this;
    }

    Progress& Progress::setType(Type type)
    {
        _type = type;
        switch (_type)
        {
        case Type::Line: {
                setFixedHeight(qMax(_strokeWidth, FontHelper(font()).getTextHeight()));
            }
            break;
        case Type::Circle: {
                setMinimumSize(sc(50, 50));
            }
            break;
        case Type::Dashboard: {
                setMinimumSize(sc(50, 40));
            }
            break;
        }
        update();
        return *this;
    }

    Progress& Progress::setStrokeWidth(int width)
    {
        _strokeWidth = width;
        int height = qMax(width, FontHelper(font()).getTextHeight());
        setFixedHeight(height);
        update();
        return *this;
    }

    Progress& Progress::setTextInside(bool textInside)
    {
        _textInside = textInside;
        setStrokeWidth(FontHelper(font()).getTextHeight());
        update();
        return *this;
    }

    Progress& Progress::setStatus(Status status)
    {
        _status = status;
        update();
        return *this;
    }

    Progress& Progress::setIndeterminate(bool indeterminate)
    {
        _indeterminate = indeterminate;
        update();
        return *this;
    }

    Progress& Progress::setDuration(int duration)
    {
        _duration = duration;
        update();
        return *this;
    }

    Progress& Progress::setColor(const std::function<QString(int)>& precent2Color)
    {
        _color = precent2Color;
        update();
        return *this;
    }

    Progress& Progress::setShowText(bool showText)
    {
        _showText = showText;
        update();
        return *this;
    }

    Progress& Progress::setStrokeLinecap(StrokeLinecap linecap)
    {
        _strokeLinecap = linecap;
        update();
        return *this;
    }

    Progress& Progress::setFormat(const std::function<QString(int)>& precent2Text)
    {
        _format = precent2Text;
        update();
        return *this;
    }

    void Progress::paintEvent(QPaintEvent*)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        switch (_type)
        {
        case Type::Line: paintLine(painter); break;
        case Type::Circle: paintCircle(painter); break;
        case Type::Dashboard: paintDashboard(painter); break;
        }
    }

    QString Progress::getColor()
    {
        switch (_status)
        {
        case Status::Success:
            return "#67C23A";
        case Status::Exception:
            return "#F56C6C";
        case Status::Warning:
            return "#E6A23C";
        case Status::None:
        default:
            break;
        }

        if (_color)
        {
            QString color = _color(_precentage);
            if (!color.isEmpty())
                return color;
        }
        return "#409EFF";
    }

    void Progress::paintLine(QPainter& painter)
    {
        QRect rect = this->rect();

        QString text = _format ? _format(_precentage) : QString::number(_precentage) + '%';
        QFontMetrics fm(font());
        int textWidth = fm.horizontalAdvance(text);

        int radius = _strokeWidth / 2;

        // 绘制背景
        QRect bgRect = rect;
        bgRect.setTop(rect.top() + ((rect.height() - _strokeWidth) / 2));
        bgRect.setHeight(_strokeWidth);
        if (!_textInside)
            bgRect.adjust(0, 0, -textWidth - 10, 0);

        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(Color::lighterBorder()));
        painter.drawRoundedRect(bgRect, radius, radius);

        // 绘制前景
        QRect fgRect = bgRect;
        fgRect.setWidth(bgRect.width() * _precentage / 100);

        painter.setBrush(QColor(getColor()));
        painter.drawRoundedRect(fgRect, radius, radius);

        // 绘制文字/图标
        if (_showText)
        {
            QRect textRect(rect.right() - textWidth, rect.top(), textWidth, rect.height());

            if (_status != Status::None)
            {
                QPixmap pixmap = Icon::instance().getPixmap(
                        _status == Status::Success ? Icon::CircleCheck
                    : _status == Status::Exception ? Icon::CircleClose : Icon::WarningFilled,
                        getColor(), sc(16));
                QRect iconRect = QRect(0, 0, pixmap.width(), pixmap.height());
                iconRect.moveCenter(textRect.center());
                painter.drawPixmap(iconRect, pixmap);
            }
            else
            {
                if (_textInside)
                    textRect.moveLeft(fgRect.width() - textWidth - 10);
                painter.setPen(_textInside ? Qt::white : QColor(Color::regularText()));
                painter.drawText(textRect, Qt::AlignCenter, text);
            }
        }
    }

    void Progress::paintCircle(QPainter& painter)
    {
        int& sw = _strokeWidth;
        int size = qMin(width(), height());
        QRect rect(0, 0, size, size);
        rect.moveCenter(this->rect().center());

        // 绘制背景
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(Color::lightFill()));
        painter.drawEllipse(rect);

        // 绘制留白
        painter.setBrush(Qt::white);
        painter.drawEllipse(rect.adjusted(sw, sw, -sw, -sw));

        // 绘制前景
        QPen pen;
        pen.setColor(QColor(getColor()));
        pen.setWidth(sw);
        pen.setCapStyle(_strokeLinecap == StrokeLinecap::Butt ? Qt::FlatCap
                    : _strokeLinecap == StrokeLinecap::Square ? Qt::SquareCap : Qt::RoundCap);

        painter.setPen(pen);
        painter.setBrush(Qt::NoBrush);
        int startAngle = 90 * 16;
        int spanAngle = -360 * _precentage / 100.0 * 16;
        painter.drawArc(rect.adjusted(sw/2, sw/2, -sw/2, -sw/2), startAngle, spanAngle);

        // 绘制文字/图标
        if (_showText)
        {
            QString text = _format ? _format(_precentage) : QString::number(_precentage) + '%';

            if (_status != Status::None)
            {
                QPixmap pixmap = Icon::instance().getPixmap(
                    _status == Status::Success ? Icon::CircleCheck :
                    _status == Status::Exception ? Icon::CircleClose : Icon::WarningFilled,
                    getColor(), sc(16));
                QRect iconRect(0, 0, pixmap.width(), pixmap.height());
                iconRect.moveCenter(rect.center());
                painter.drawPixmap(iconRect, pixmap);
            }
            else
            {
                painter.setPen(QColor(Color::regularText()));
                QFontMetrics fm(font());
                int textWidth = fm.horizontalAdvance(text);
                int textHeight = fm.height();

                QRect textRect(0, 0, textWidth, textHeight);
                textRect.moveCenter(rect.center());

                painter.drawText(textRect, Qt::AlignCenter, text);
            }
        }
    }

    void Progress::paintDashboard(QPainter& painter)
    {
        int& sw = _strokeWidth;
        int w = width() < height() ? width() : height() * 1.15;

        QRect rect(0, 0, w, w);
        rect.moveCenter(this->rect().center());
        rect.moveTop(this->rect().top());

        // 绘制背景
        QPen pen;
        pen.setColor(QColor(Color::lightFill()));
        pen.setWidth(sw);
        pen.setCapStyle(_strokeLinecap == StrokeLinecap::Butt ? Qt::FlatCap
                    : _strokeLinecap == StrokeLinecap::Square ? Qt::SquareCap : Qt::RoundCap);

        painter.setPen(pen);
        painter.setBrush(Qt::NoBrush);
        int startAngle = 227 * 16;
        int spanAngle = -274 * 16;
        painter.drawArc(rect.adjusted(sw/2, sw/2, -sw/2, -sw/2), startAngle, spanAngle);

        // 绘制前景
        pen.setColor(QColor(getColor()));
        pen.setWidth(sw);
        pen.setCapStyle(_strokeLinecap == StrokeLinecap::Butt ? Qt::FlatCap
                    : _strokeLinecap == StrokeLinecap::Square ? Qt::SquareCap : Qt::RoundCap);

        painter.setPen(pen);
        painter.setBrush(Qt::NoBrush);
        startAngle = 227 * 16;
        spanAngle = -274 * _precentage / 100.0 * 16;
        painter.drawArc(rect.adjusted(sw/2, sw/2, -sw/2, -sw/2), startAngle, spanAngle);

        // 绘制文字/图标
        if (_showText)
        {
            QString text = _format ? _format(_precentage) : QString::number(_precentage) + '%';

            if (_status != Status::None)
            {
                QPixmap pixmap = Icon::instance().getPixmap(
                    _status == Status::Success ? Icon::CircleCheck :
                    _status == Status::Exception ? Icon::CircleClose : Icon::WarningFilled,
                    getColor(), sc(16));
                QRect iconRect(0, 0, pixmap.width(), pixmap.height());
                iconRect.moveCenter(rect.center());
                painter.drawPixmap(iconRect, pixmap);
            }
            else
            {
                painter.setPen(QColor(Color::regularText()));
                QFontMetrics fm(font());
                int textWidth = fm.horizontalAdvance(text);
                int textHeight = fm.height();

                QRect textRect(0, 0, textWidth, textHeight);
                textRect.moveCenter(rect.center());

                painter.drawText(textRect, Qt::AlignCenter, text);
            }
        }
    }

}