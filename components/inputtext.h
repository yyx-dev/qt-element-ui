#pragma once

#include "base.h"
#include "icon.h"

#include <QTextEdit>
#include <QLabel>

namespace Element
{

    class ResizeHandler : public QWidget
    {
    Q_OBJECT
    public:
        ResizeHandler(QTextEdit* parent);
        void updatePosition();

    protected:
        void paintEvent(QPaintEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;

    private:
        QTextEdit* _parent = nullptr;
        bool _isResizing = false;
        QPoint _startPos;
        QSize _startSize;
    };

    class InputText : public QTextEdit
    {
    Q_OBJECT

    public:
        QString getPlaceholder();
        InputText& setPlaceholder(const QString& placeholder);

        int getWidth();
        InputText& setWidth(int width);

        bool isDisabled();
        InputText& setDisabled(bool disabled);

        int getMaxLength();
        InputText& setMaxLength(int maxLength);

        bool getReadOnly();
        InputText& setReadOnly(bool readonly);

        InputText& setAutoFocus();

        bool getResize();
        InputText& setResize(bool resize);

        bool getAutoSize();
        InputText& setAutoSize(bool autosize);
        InputText& setAutoSize(int minRows, int maxRows);

        // TODO: validate

    public:
        InputText(QWidget* parent = nullptr);
        InputText(QString placeholder, QWidget* parent = nullptr);

    private:
        bool _resize = false;
        bool _clearable = false;
        bool _autoSize = false;

        int _maxLength = 0;
        int _minRows = 1, _curRows = 1, _maxRows = 0;

    private:
        QSSHelper _qssHelper;

        QLabel* _maxLengthLabel = nullptr;
        ResizeHandler* _resizeHandler = nullptr;

    private:
        void maxLengthChecker();

        int calculateRows();
        int calculateHeight(int rows);
        void updateHeight();

    protected:
        void onTextChanged();

        void enterEvent(QEvent *event) override;
        void leaveEvent(QEvent *event) override;
        void resizeEvent(QResizeEvent *event) override;

    private:
        QString placeholderText();
    };
}
