#include "badge.h"
#include "base.h"



namespace Element
{

    Badge::Badge(QWidget* partner)
        : QLabel(partner->parentWidget())
        , _partner(partner)
        , _numValue(0)
        , _max(0)
        , _isDot(false)
    {
        setFixedHeight(20);
        setMinimumWidth(20), setMaximumWidth(100);

        setAttribute(Qt::WA_TransparentForMouseEvents); // 允许鼠标事件穿透到父控件
        setAlignment(Qt::AlignCenter);

        QFont font = FontManager::font();
        font.setBold(true);
        font.setPointSize(7);

        _qsshelper.setProperty("QLabel", "color", "white")
                .setProperty("QLabel", "border", "none")
                .setProperty("QLabel", "border-radius", "10px")
                .setProperty("QLabel", "padding", "0px 6px 2px 6px")
                .setProperty("QLabel", "background-color", getColor());
        setStyleSheet(_qsshelper.generate());

        hide();
    }

    Badge::Badge(bool isDot, QWidget* partner) : Badge(partner)
    {
        setIsDot(isDot);
    }

    Badge::Badge(int value, QWidget* partner) : Badge(partner)
    {
        setValue(value);
    }

    Badge::Badge(int value, int max, QWidget* partner) : Badge(partner)
    {
        setValue(value);
        setMax(max);
    }

    Badge::Badge(const QString& value, QWidget* partner) : Badge(partner)
    {
        setValue(value);
    }

    Badge& Badge::setType(Type type)
    {
        _type = type;
        _qsshelper.setProperty("QLabel", "background-color", getColor());
        setStyleSheet(_qsshelper.generate());
        return *this;
    }

    Badge& Badge::setIsDot(bool isdot)
    {
        _isDot = isdot;
        return *this;
    }

    Badge& Badge::setValue(int value)
    {
        _numValue = value;

        if (value == 0)
        {
            hide();
        }
        else if (!isVisible())
        {
            if (_max != 0 && value > _max)
                setValue(QString::number(_max) + "+");
            else
                setValue(QString::number(_numValue));
            show();
        }
        return *this;
    }

    Badge& Badge::setValue(const QString& value)
    {
        _strValue = value;

        if (value.isEmpty())
        {
            hide();
        }
        else if (!isVisible())
        {
            setText(_strValue);
            adjustSize();
            show();
        }
        return *this;
    }

    Badge& Badge::setMax(int max)
    {
         _max = max;
         return *this;
    }

    void Badge::resizeEvent(QResizeEvent* event)
    {
        QLabel::resizeEvent(event);
        updatePosition();
    }

    void Badge::updatePosition()
    {
        if (!_partner)
            return;

        QRect partnerGeo = _partner->geometry();

        move(partnerGeo.x() + partnerGeo.width() - width() / 2,
             partnerGeo.y() - height() / 2);
    }

    QString Badge::getColor()
    {
        if (_type == Type::Primary) return Color::primary();
        else if (_type == Type::Success) return Color::success();
        else if (_type == Type::Info) return Color::info();
        else if (_type == Type::Warning) return Color::warning();
        else if (_type == Type::Danger) return Color::danger();
        else return "";
    }

}
