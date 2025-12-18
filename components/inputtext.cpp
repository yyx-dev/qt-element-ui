#include "inputtext.h"
#include "color.h"
#include "private/utils.h"

#include <QApplication>
#include <QPainter>

#include <QMouseEvent>
#include <QtMath>

namespace Element
{

    InputText::InputText(QString placeholder, QWidget* parent)
        : QTextEdit(parent)
    {
        setPlaceholderText(placeholder);

        _qssHelper.setProperty("QTextEdit", "font-family", Comm::fontFmaily)
                .setProperty("QTextEdit", "font-size", "16px")
                .setProperty("QTextEdit", "color", Color::regularText())
                .setProperty("QTextEdit", "background", Color::baseBackground())
                .setProperty("QTextEdit", "border-radius", "4px")
                .setProperty("QTextEdit", "border", "1px solid " + Color::baseBorder())
                .setProperty("QTextEdit", "padding", "1px 11px")
                .setProperty("QTextEdit:hover", "border", "1px solid " + Color::disabledText())
                .setProperty("QTextEdit:focus", "border", "1px solid " + Color::primary())
                .setProperty("QTextEdit:disabled", "border", "1px solid " + Color::lightBorder())
                .setProperty("QTextEdit:disabled", "background", Color::lightFill())
                .setProperty("QTextEdit:disabled", "color", Color::placeholderText());
        setStyleSheet(_qssHelper.generate());

        setMinimumSize(300, 65);
        adjustSize();

        connect(this, &QTextEdit::textChanged, this, &InputText::onTextChanged);
    }

    InputText::InputText(QWidget* parent)
        : InputText("Please input", parent)
    {}

    QString InputText::getPlaceholder()
    {
        return QTextEdit::placeholderText();
    }

    InputText& InputText::setPlaceholder(const QString& placeholder)
    {
        QTextEdit::setPlaceholderText(placeholder);
        return *this;
    }

    int InputText::getWidth()
    {
        return QTextEdit::width();
    }

    InputText& InputText::setWidth(int width)
    {
        QTextEdit::setMinimumWidth(width);
        QTextEdit::setMaximumWidth(width);
        return *this;
    }

    bool InputText::isDisabled()
    {
        return !QTextEdit::isEnabled();
    }

    InputText& InputText::setDisabled(bool disabled)
    {
        QTextEdit::setDisabled(disabled);
        return *this;
    }

    int InputText::getMaxLength()
    {
        return _maxLength;
    }

    InputText& InputText::setMaxLength(int maxLength)
    {
        _maxLength = maxLength;

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
                qssHelper.setProperty("QLabel", "font-family", Comm::fontFmaily)
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

            QMargins margins = contentsMargins();
            margins.setRight(inputWidth - x);
            setContentsMargins(margins);
        }

        return *this;
    }

    bool InputText::getReadOnly()
    {
        return InputText::isReadOnly();
    }

    InputText& InputText::setReadOnly(bool readOnly)
    {
        QTextEdit::setReadOnly(readOnly);
        return *this;
    }

    InputText& InputText::setAutoFocus()
    {
        setFocus();
        return *this;
    }

    bool InputText::getResize()
    {
        return _resize;
    }

    InputText& InputText::setResize(bool resize)
    {
        _resize = resize;

        if (resize)
        {
            if (!_resizeHandler)
                _resizeHandler = new ResizeHandler(this);

            _resizeHandler->updatePosition();
        }
        else
        {
            _resizeHandler->deleteLater();
            _resizeHandler = nullptr;
        }

        return *this;
    }

    bool InputText::getAutoSize()
    {
        return _autoSize;
    }

    InputText& InputText::setAutoSize(bool autosize)
    {
        _autoSize = autosize;
        updateHeight();
        return *this;
    }

    InputText& InputText::setAutoSize(int minRows, int maxRows)
    {
        if (minRows <= 0 || maxRows <= 0)
        {
            Log::error("TextInput::setAutoSize: wrong parameter");
            return *this;
        }

        _autoSize = true;
        _minRows = minRows, _curRows = minRows, _maxRows = maxRows;

        updateHeight();

        return *this;
    }

    void InputText::onTextChanged()
    {
        if (_maxLength > 0)
            maxLengthChecker();

        if (_autoSize)
            updateHeight();
    }

    void InputText::maxLengthChecker()
    {
        if (!_maxLengthLabel)
            return;

        QString tips;
        tips.reserve(16);
        tips.append(QString::number(toPlainText().length()))
             .append(" / ")
             .append(QString::number(_maxLength));

        _maxLengthLabel->setText(tips);
    }

    void InputText::enterEvent(QEvent* event)
    {
        if (!isEnabled())
            QApplication::setOverrideCursor(Qt::ForbiddenCursor);
        QTextEdit::enterEvent(event);
    }

    void InputText::leaveEvent(QEvent* event)
    {
        if (!isEnabled())
            QApplication::restoreOverrideCursor();
        QTextEdit::leaveEvent(event);
    }

    void InputText::resizeEvent(QResizeEvent *event)
    {
        QTextEdit::resizeEvent(event);

        if (_resizeHandler)
            _resizeHandler->updatePosition();
    }

    int InputText::calculateRows()
    {
        QString text = toPlainText();

        int textWidth = width() - contentsMargins().left() - contentsMargins().right() - frameWidth() - 3;

        QFontMetrics fm(font());
        QStringList lines = text.split('\n');

        int totalRows = 0;

        for (const QString &line : lines)
        {
            if (line.isEmpty())
            {
                totalRows += 1;
            }
            else
            {
                int lineWidth = fm.horizontalAdvance(line);
                int RowsNeed = qCeil(static_cast<qreal>(lineWidth) / textWidth);
                totalRows += qMax(1, RowsNeed);
            }
        }

        return totalRows;
    }

    int InputText::calculateHeight(int rows)
    {
        return QFontMetrics(font()).height() * rows
            + contentsMargins().top()
            + contentsMargins().bottom()
            + frameWidth() - 4;
    }

    void InputText::updateHeight()
    {
        int totalRows = calculateRows();

        if (_minRows > 0 && _maxRows > 0)
            totalRows = qBound(_minRows, totalRows, _maxRows);

        if (_curRows != totalRows)
        {
            _curRows = totalRows;
            setFixedHeight(calculateHeight(totalRows));
        }
    }

    QString InputText::placeholderText()
    {
        return QTextEdit::placeholderText();
    }


    ResizeHandler::ResizeHandler(QTextEdit* parent)
        : QWidget(parent)
        , _parent(parent)
    {
        setFixedSize(12, 12);
        setMouseTracking(true);
        setCursor(Qt::SizeVerCursor);
    }

    void ResizeHandler::paintEvent(QPaintEvent*)
    {
        QPainter painter(this);

        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(QPen (QColor("#666666"), 1.6));

        int in = 3;
        painter.drawLine(0 + in, height() - in, width() - in, 0 + in);
        painter.drawLine(5 + in, height() - in, width() - in, 5 + in);
    }

    void ResizeHandler::mousePressEvent(QMouseEvent *event)
    {
        if (event->button() == Qt::LeftButton)
        {
            _isResizing = true;
            _startPos = event->globalPos();
            _startSize = _parent->size();
        }
    }

    void ResizeHandler:: mouseMoveEvent(QMouseEvent *event)
    {
        if (_isResizing)
        {
            QPoint delta = event->globalPos() - _startPos;

            int newHeight = _startSize.height() + delta.y();
            newHeight = qMax(newHeight, _parent->minimumHeight());

            _parent->resize(_startSize.width(), newHeight);
        }
    }

    void ResizeHandler::mouseReleaseEvent(QMouseEvent*)
    {
        _isResizing = false;
    }

    void ResizeHandler::updatePosition()
    {
        move(_parent->width() - width(), _parent->height() - height());
    }
}
