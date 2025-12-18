#include "link.h"
#include "color.h"
#include "private/utils.h"


#include <QApplication>

namespace Element
{

    Link::Link(QWidget* parent)
        : QLabel(parent)
        , _type(Type::Default)
        , _underline(Underline::Default)
    {
        QLabel::setFont(FontHelper()
                .setPointSize(Comm::defaultFontSize)
                .setBold(true)
                .getFont());

        setType(_type);
        setUnderline(_underline);
    }

    Link::Link(const QString& text, QWidget* parent)
        : Link(parent)
    {
        QLabel::setText(text);
        QLabel::adjustSize();
    }

    Link::Type Link::getType()
    {
        return _type;
    }

    Link& Link::setType(Type type)
    {
        _type = type;

        if (type == Type::Default)
        {
            _qsshelper.setProperty("QLabel", "color", Color::regularText());
            _qsshelper.setProperty("QLabel:hover", "color", Color::primary());
            _qsshelper.setProperty("QLabel:disabled", "color", Color::placeholderText());
        }
        else if (type == Type::Primary)
        {
            _qsshelper.setProperty("QLabel", "color", Color::primary());
            _qsshelper.setProperty("QLabel:hover", "color", Color::primaryL1());
            _qsshelper.setProperty("QLabel:disabled", "color", Color::primaryL2());
        }
        else if (type == Type::Success)
        {
            _qsshelper.setProperty("QLabel", "color", Color::success());
            _qsshelper.setProperty("QLabel:hover", "color", Color::successL1());
            _qsshelper.setProperty("QLabel:disabled", "color", Color::successL2());
        }
        else if (type == Type::info)
        {
            _qsshelper.setProperty("QLabel", "color", Color::info());
            _qsshelper.setProperty("QLabel:hover", "color", Color::infoL1());
            _qsshelper.setProperty("QLabel:disabled", "color", Color::infoL2());
        }
        else if (type == Type::warning)
        {
            _qsshelper.setProperty("QLabel", "color", Color::warning());
            _qsshelper.setProperty("QLabel:hover", "color", Color::warningL1());
            _qsshelper.setProperty("QLabel:disabled", "color", Color::warningL2());
        }
        else if (type == Type::Danger)
        {
            _qsshelper.setProperty("QLabel", "color", Color::danger());
            _qsshelper.setProperty("QLabel:hover", "color", Color::dangerL1());
            _qsshelper.setProperty("QLabel:disabled", "color", Color::dangerL2());
        }

        QLabel::setStyleSheet(_qsshelper.generate());
        return *this;
    }

    Link::Underline Link::getUnderline()
    {
        return _underline;
    }

    Link& Link::setUnderline(Underline underline)
    {
        _underline = underline;

        if (underline == Underline::Always)
            _qsshelper.setProperty("QLabel", "text-decoration", "underline");
        else if (underline == Underline::Never)
            _qsshelper.setProperty("QLabel", "text-decoration", "none");

        QLabel::setStyleSheet(_qsshelper.generate());
        return *this;
    }

    bool Link::isDisabled()
    {
        return !QLabel::isEnabled();
    }

    Link& Link::setDisabled(bool disabled)
    {
        QLabel::setDisabled(disabled);
        return *this;
    }

    Link& Link::setText(const QString& text)
    {
        QLabel::setText(text);
        adjustSize();
        return *this;
    }

    void Link::enterEvent(QEvent *event)
    {
        if (!isEnabled())
            QApplication::setOverrideCursor(Qt::ForbiddenCursor);
        else if (_underline != Underline::Never)
            setText("<u>" + text() + "</u>");

        QLabel::enterEvent(event);
    }

    void Link::leaveEvent(QEvent *event)
    {
        QApplication::restoreOverrideCursor();
        if (_underline != Underline::Always)
            setText(text().remove("<u>").remove("</u>"));

        QLabel::leaveEvent(event);
    }

}
