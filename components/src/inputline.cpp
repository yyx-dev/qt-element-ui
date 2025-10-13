/*
 *   1080p        2k
 *  240*30  ->  300*40
 *    300/240 = 1.25
 *    40/30 = 1.333
 *
 **/

#include "inputline.h"
#include "color.h"
#include "tools/commvar.h"
#include "tools/logger.h"

#include <QDebug>
#include <QApplication>
#include <QMargins>
#include <QAction>
#include <QMouseEvent>

namespace Element
{

    InputLine::InputLine(QWidget* parent)
        : InputLine("Please input", parent)
    {}

    InputLine::InputLine(const QString& placeholder, QWidget* parent)
        : QLineEdit(parent)
    {
        setPlaceholderText(placeholder);
        setSize(Size::Default);

        connect(this, &QLineEdit::textChanged, this, &InputLine::onTextChanged);
    }

    QString InputLine::getPlaceholder()
    {
        return placeholderText();
    }

    InputLine& InputLine::setPlaceholder(const QString& placeholder)
    {
        QLineEdit::setPlaceholderText(placeholder);
        return *this;
    }

    int InputLine::getWidth()
    {
        return QLineEdit::width();
    }

    InputLine& InputLine::setWidth(int width)
    {
        QLineEdit::setMinimumWidth(width);
        QLineEdit::setMaximumWidth(width);
        return *this;
    }

    bool InputLine::getDisabled()
    {
        return !QLineEdit::isEnabled();
    }

    InputLine& InputLine::setDisabled(bool disabled)
    {
        QLineEdit::setDisabled(disabled);
        return *this;
    }

    InputLine::Size InputLine::getSize()
    {
        return _size;
    }

    InputLine& InputLine::setSize(Size size)
    {
        _size = size;

        QString fontSize;
        int height = 0;

        if (size == Size::Large)
        {
            fontSize = "16px";
            height = 50;
        }
        else if (size == Size::Default)
        {
            fontSize = "16px";
            height = 40;
        }
        else if (size == Size::Small)
        {
            fontSize = "12px";
            height = 30;
        }

        _qssHelper.setProperty("QLineEdit", "font-family", CommonVar::fontFmaily)
                .setProperty("QLineEdit", "font-size", fontSize)
                .setProperty("QLineEdit", "color", Color::regularText())
                .setProperty("QLineEdit", "background", Color::baseBackground())
                .setProperty("QLineEdit", "border-radius", "4px")
                .setProperty("QLineEdit", "border", "1px solid " + Color::baseBorder())
                .setProperty("QLineEdit", "padding", "1px 11px")
                .setProperty("QLineEdit:hover", "border", "1px solid " + Color::disabledText())
                .setProperty("QLineEdit:focus", "border", "1px solid " + Color::primary())
                .setProperty("QLineEdit:disabled", "border", "1px solid " + Color::lightBorder())
                .setProperty("QLineEdit:disabled", "background", Color::lightFill())
                .setProperty("QLineEdit:disabled", "color", Color::placeholderText());
        setStyleSheet(_qssHelper.generate());

        setFixedSize(300, height);
        adjustSize();

        return *this;
    }

    Icon::Name InputLine::getSuffixIcon()
    {
        return _suffixIcon;
    }

    InputLine& InputLine::setSuffixIcon(Icon::Name icon)
    {
        if (!_suffixAction)
            return setSuffixIcon(icon, []{});

        _suffixAction->setIcon(
            Icon::instance().getIcon(icon, Color::placeholderText(), CommonVar::inputIconSize));
        _suffixIcon = icon;

        return *this;
    }

    InputLine& InputLine::setSuffixIcon(Icon::Name icon, const std::function<void()>& callback)
    {
        if (icon == Icon::None)
        {
            if (_suffixAction)
            {
                removeAction(_suffixAction);
                _suffixAction->deleteLater();
                _suffixAction = nullptr;
            }
        }
        else
        {
            if (_suffixAction)
                setSuffixIcon(Icon::None);

            _suffixAction = new QAction(
                Icon::instance().getIcon(icon, Color::placeholderText(), CommonVar::inputIconSize),
                "", this);
            connect(_suffixAction, &QAction::triggered, callback);
            addAction(_suffixAction, QLineEdit::TrailingPosition);
        }

        _suffixIcon = icon;
        return *this;
    }

    Icon::Name InputLine::getPrefixIcon()
    {
        return _prefixIcon;
    }

    InputLine& InputLine::setPrefixIcon(Icon::Name icon)
    {
        if (!_prefixAction)
            return setPrefixIcon(icon, []{});

        _prefixAction->setIcon(
            Icon::instance().getIcon(icon, Color::placeholderText(), CommonVar::inputIconSize));
        _prefixIcon = icon;

        return *this;
    }

    InputLine& InputLine::setPrefixIcon(Icon::Name icon, const std::function<void()>& callback)
    {
        if (icon == Icon::None)
        {
            if (_prefixAction)
            {
                removeAction(_prefixAction);
                _prefixAction->deleteLater();
                _prefixAction = nullptr;
            }
        }
        else
        {
            if (_prefixAction)
                setPrefixIcon(Icon::None);

            _prefixAction = new QAction(
                        Icon::instance().getIcon(icon, Color::placeholderText(), CommonVar::inputIconSize),
                        "", this);
            connect(_prefixAction, &QAction::triggered, callback);
            addAction(_prefixAction, QLineEdit::LeadingPosition);
        }

        _prefixIcon = icon;
        return *this;
    }

    int InputLine::getMaxLength()
    {
        return _maxLength;
    }

    InputLine& InputLine::setMaxLength(int maxLength)
    {
        _maxLength = maxLength;
        QLineEdit::setMaxLength(_maxLength);

        if (maxLength <= 0)
        {
            _maxLengthLabel->deleteLater();
            _maxLengthLabel = nullptr;
        }
        else
        {
            if (!_maxLengthLabel)
            {
                _maxLengthLabel = new QLabel(this);
                QSSHelper qssHelper;
                qssHelper.setProperty("QLabel", "font-family", CommonVar::fontFmaily)
                        .setProperty("QLabel", "font-size", "14px")
                        .setProperty("QLabel", "color", Color::secondaryText())
                        .setProperty("QLabel", "background", Color::baseBackground());
                _maxLengthLabel->setStyleSheet(qssHelper.generate());
            }

            QString labelText = QString("0 / %1").arg(_maxLength);
            _maxLengthLabel->setText(labelText);

            QFontMetrics fontMetrics(_maxLengthLabel->font());
            int textWidth = fontMetrics.horizontalAdvance(labelText);
            int textHeight = fontMetrics.height();

            int inputWidth = width();
            int inputHeight = height();

            int labelWidth = textWidth + 10;
            int labelHeight = textHeight;
            int rightMargin = 15;
            int x = inputWidth - labelWidth - rightMargin;
            int y = (inputHeight - labelHeight) / 2;

            _maxLengthLabel->setGeometry(x, y, labelWidth, labelHeight);
            _maxLengthLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

            QMargins margins = textMargins();
            margins.setRight(inputWidth - x);
            setTextMargins(margins);
        }

        return *this;
    }

    bool InputLine::getClearable()
    {
        return _clearable;
    }

    InputLine& InputLine::setClearable(bool clearable)
    {
        if (clearable)
        {
            setSuffixIcon(Icon::CircleClose, [&]{ setText(""); });
            clearableChecker();
        }
        else
        {
            setSuffixIcon(Icon::None);
        }

        _clearable = clearable;
        return *this;
    }

    bool InputLine::getShowPassword()
    {
        return _showPassword;
    }

    InputLine& InputLine::setShowPassword(bool showPassword)
    {
        _showPassword = showPassword;

        if (showPassword)
        {
            setPlaceholder("Please input password");

            setSuffixIcon(Icon::View, [&] {
                bool normal = echoMode() == Normal;
                setSuffixIcon(normal ? Icon::View : Icon::Hide);
                setEchoMode(normal ? EchoMode::Password : EchoMode::Normal);
            });

            showPasswordChecker();
        }
        else
        {
            setSuffixIcon(Icon::None);
        }

        return *this;
    }

    bool InputLine::getReadOnly()
    {
        return QLineEdit::isReadOnly();
    }

    InputLine& InputLine::setReadOnly(bool readOnly)
    {
        QLineEdit::setReadOnly(readOnly);
        return *this;
    }

    InputLine& InputLine::setAutoFocus()
    {
        setFocus();
        return *this;
    }

    void InputLine::onTextChanged(const QString&)
    {
        if (_clearable)
            clearableChecker();

        if (_showPassword)
            showPasswordChecker();

        if (_maxLength > 0)
            maxLengthChecker();
    }

    void InputLine::clearableChecker()
    {
        if (!_suffixAction)
            return;

        bool visible = !text().isEmpty();
        if (_suffixAction->isVisible() != visible)
            _suffixAction->setVisible(visible);
    }

    void InputLine::showPasswordChecker()
    {
        if (!_suffixAction)
            return;

        bool visible = !text().isEmpty();
        if (_suffixAction->isVisible() != visible)
        {
            _suffixAction->setVisible(visible);
            setEchoMode(visible ? EchoMode::Password : EchoMode::Normal);
        }
    }

    void InputLine::maxLengthChecker()
    {
        if (!_maxLengthLabel)
            return;

        QString tips;
        tips.reserve(16);
        tips.append(QString::number(text().length()))
             .append(" / ")
             .append(QString::number(_maxLength));

        _maxLengthLabel->setText(tips);

    }

    void InputLine::focusInEvent(QFocusEvent* event)
    {
        QLineEdit::focusInEvent(event);
    }

    void InputLine::focusOutEvent(QFocusEvent* event)
    {
        QLineEdit::focusOutEvent(event);
    }

    void InputLine::enterEvent(QEvent* event)
    {
        if (!isEnabled())
            QApplication::setOverrideCursor(Qt::ForbiddenCursor);
        QLineEdit::enterEvent(event);
    }

    void InputLine::leaveEvent(QEvent* event)
    {
        if (!isEnabled())
            QApplication::restoreOverrideCursor();
        QLineEdit::leaveEvent(event);
    }

    void InputLine::mouseMoveEvent(QMouseEvent* event)
    {
        int w = width();
        int h = height();
        QRect prefixRect(2, 2, h - 4, h - 4);
        QRect suffixRect(w - h + 2, 2, h - 4, h - 4);

        QPoint pos = event->pos();

        bool isPrefixVisible = _prefixAction && _prefixAction->isVisible();
        bool isSuffixVisible = _suffixAction && _suffixAction->isVisible();

        bool isPrefixHovered = prefixRect.contains(pos);
        bool isSuffixHovered = suffixRect.contains(pos);

        if (isPrefixVisible && isPrefixHovered != _isPrefixHovered)
        {
            _isPrefixHovered = isPrefixHovered;
            _prefixAction->setIcon(Icon::instance().getIcon(
                _prefixIcon,
                isPrefixHovered ? Color::secondaryText() : Color::placeholderText(),
                CommonVar::inputIconSize));

            if (isPrefixHovered)
                QApplication::setOverrideCursor(Qt::PointingHandCursor);
            else
                QApplication::restoreOverrideCursor();
        }

        if (isSuffixVisible && isSuffixHovered != _isSuffixHovered)
        {
            _isSuffixHovered = isSuffixHovered;
            _suffixAction->setIcon(Icon::instance().getIcon(
                _suffixIcon,
                isSuffixHovered ? Color::secondaryText() : Color::placeholderText(),
                CommonVar::inputIconSize));

            if (isSuffixHovered)
                QApplication::setOverrideCursor(Qt::PointingHandCursor);
            else
                QApplication::restoreOverrideCursor();
        }

        QLineEdit::mouseMoveEvent(event);
    }

    QString InputLine::placeholderText()
    {
        return QLineEdit::placeholderText();
    }

}
