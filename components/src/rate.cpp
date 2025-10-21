#include "rate.h"

#include "base.h"
#include "color.h"
#include "icon.h"


#include <QtMath>

namespace Element
{

    Rate::Rate(QWidget* parent)
        : Rate(0.0, parent)
    {}

    Rate::Rate(float value, QWidget* parent)
        : QWidget(parent)
        , _layout(new QHBoxLayout(this))
        , _text(new Text(this))
    {
        installEventFilter(this);
        _layout->setContentsMargins(0, 8, 0, 8);
        _layout->setSpacing(10);

        for (int i = 0; i < 5; i++)
        {
            QSvgWidget* star = new QSvgWidget(this);
            star->load(Icon::instance().getCodeArray(Icon::Star, Color::darkBorder()));
            star->setFixedSize(22, 22);
            star->installEventFilter(this);
            star->setMouseTracking(true);

            _stars.append(star);
            _layout->addWidget(star);
        }

        setCursor(Qt::PointingHandCursor);

        setSize(_size);
        setScore(value);
    }

    Rate& Rate::setScore(qreal value)
    {
        _value = qFloor(value * 10.0);
        _value = qBound(0, _value, 5 * 10);

        update(_value);
        return *this;
    }

    qreal Rate::getScore()
    {
        return (_value / 10.0) * (_max / 50);
    }

    Rate& Rate::setMax(int max)
    {
        if (max >= 5 && max % 5 == 0)
            _max = max * 10;
        return *this;
    }

    int Rate::getMax()
    {
        return _max / 10;
    }

    Rate& Rate::setSize(Size size)
    {
        _size = size;

        int totalHeight = _size == Size::Large ? 38 : _size == Size::Default ? 38 : 34;
        int iconSize = _size == Size::Large ? 22 : _size == Size::Default ? 22 : 18;

        for (auto* star : _stars)
            star->setFixedSize(iconSize, iconSize);

        setFixedHeight(totalHeight);
        adjustSize();
        return *this;
    }

    Rate::Size Rate::getSize()
    {
        return _size;
    }

    Rate& Rate::setAllowHalf(bool allowHalf)
    {
        _allowHalf = allowHalf;
        return *this;
    }

    bool Rate::getAllowHalf()
    {
        return _allowHalf;
    }

    Rate& Rate::setLowThreshold(int lowThreshold)
    {
        if (lowThreshold % (_max / 50) == 0 && lowThreshold > 0 && lowThreshold < _max)
            _lowThreshold = lowThreshold / (_max / 50) * 10;
        return *this;
    }

    int Rate::getLowThreshold()
    {
        return _lowThreshold / 10;
    }

    Rate& Rate::setHighThreshold(int highThreshold)
    {
        if (highThreshold % (_max / 50) == 0 && highThreshold > 0 && highThreshold < _max)
            _highThreshold = highThreshold / (_max / 50) * 10;
        return *this;
    }

    int Rate::setHighThreshold()
    {
        return _highThreshold / 10;
    }

    Rate& Rate::setShowText(bool showText)
    {
        _showText = showText;

        if (showText)
            _showScore = false;

        if (showText)
        {
            _layout->addWidget(_text);
        }
        else
        {
            _layout->removeWidget(_text);
            _text->hide();
        }

        adjustSize();
        return *this;
    }

    bool Rate::getShowText()
    {
        return _showText;
    }

    Rate& Rate::setShowScore(bool showScore)
    {
        _showScore = showScore;

        if (showScore)
            _showText = false;

        if (showScore)
        {
            _layout->addWidget(_text);
        }
        else
        {
            _layout->removeWidget(_text);
            _text->hide();
        }

        adjustSize();
        return *this;
    }

    bool Rate::getShowScore()
    {
        return _showScore;
    }

    Rate& Rate::setClearable(bool clearable)
    {
        _clearable = clearable;
        return *this;
    }

    bool Rate::getClearable()
    {
        return _clearable;
    }

    Rate& Rate::setDisabled(bool disabled)
    {
        QWidget::setDisabled(disabled);
        setCursor(disabled ? Qt::ArrowCursor : Qt::PointingHandCursor);
        return *this;
    }

    bool Rate::isDisabled()
    {
        return !QWidget::isEnabled();
    }

    Rate& Rate::setColors(const QString& lowColor, const QString& midColor, const QString& highColor)
    {
        _lowColor = lowColor, _midColor = midColor, _highColor = highColor;
        return *this;
    }

    Rate& Rate::setTexts(const QString& first, const QString& second, const QString& third,
                         const QString& fourth, const QString& fifth)
    {
        _texts = QStringList{first, second, third, fourth, fifth};
        return *this;
    }

    bool Rate::eventFilter(QObject* obj, QEvent* event)
    {
        if (isDisabled())
            return QWidget::eventFilter(obj, event);

        if (event->type() != QEvent::MouseMove
         && event->type() != QEvent::MouseButtonPress
         && event->type() != QEvent::Leave)
            return QWidget::eventFilter(obj, event);

        for (int i = 0; i < _stars.size(); ++i)
        {
            if (obj == _stars[i])
            {
                int pcent = qRound(static_cast<QMouseEvent*>(event)->x() * 10.0
                                 / _stars[i]->width());
                int frac = 0;

                if (pcent <= 0) frac = 0;
                else if (_allowHalf && pcent <= 5) frac = 5;
                else frac = 10;

                int tmpval = (i * 10 + frac);

                if (event->type() == QEvent::MouseMove)
                {
                    update(tmpval);
                }
                else if (event->type() == QEvent::MouseButtonPress)
                {
                    if (_clearable && _value == tmpval)
                        setValue(0);
                    else
                        setValue(tmpval);
                }
            }
        }

        if (obj == this && event->type() == QEvent::Leave)
        {
            update(_value);
        }

        return QWidget::eventFilter(obj, event);
    }

    void Rate::update(int value)
    {
        int full = value / 10;
        int part = value % 10;

        QString color = getColor(value);

        for (int i = 0; i < _stars.size(); ++i)
        {
            if (i < full)
            {
                _stars[i]->load(Icon::instance().getCodeArray(Icon::StarFilled, color));
            }
            else if (i == full && part > 0)
            {

                _stars[i]->load(partialStar(part, color, Color::darkBorder()));
            }
            else
            {
                if (isDisabled())
                    _stars[i]->load(Icon::instance().getCodeArray(Icon::StarFilled, Color::baseFill()));
                else
                    _stars[i]->load(Icon::instance().getCodeArray(Icon::Star, Color::darkBorder()));
            }
        }

        if (_showText)
        {
            if (full == 0 && part == 0)
            {
                _text->hide();
            }
            else if (part != 0)
            {
                _text->setText(_texts[full]);
                _text->show();
            }
            else
            {
                _text->setText(_texts[full - 1]);
                _text->show();
            }
        }
        else if (_showScore)
        {
            _text->setText(QString::number((value / 10.0) * (_max / 50)) + " points");
            _text->setColor(color);
            _text->show();
        }

        adjustSize();
    }

    QString Rate::getColor(int value)
    {
        if (value <= _lowThreshold)
            return _lowColor;
        else if (value < _highThreshold)
            return _midColor;
        else
            return _highColor;
    }

    void Rate::setValue(int value)
    {
        _value = value;
    }

    QByteArray Rate::partialStar(int percent, const QString& fillColor, const QString& borderColor)
    {
        Q_UNUSED(percent);
        Q_UNUSED(fillColor);
        Q_UNUSED(borderColor);

        return "";
    }

}
