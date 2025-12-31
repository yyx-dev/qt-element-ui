#pragma once

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>

namespace Element
{
    class _BackButton;
    class _CtrlButton;

    class AppBar : public QWidget
    {
        Q_OBJECT
    public:
        AppBar(QWidget* parent = nullptr);
        AppBar(int dragMargin, QWidget* parent = nullptr);

    public:
        void setDragMargin(int margin);

    protected:
        void changeEvent(QEvent* event) override;
        void mousePressEvent(QMouseEvent* event) override;
        void mouseMoveEvent(QMouseEvent* event) override;
        void mouseReleaseEvent(QMouseEvent* event) override;
        void paintEvent(QPaintEvent* event) override;
        void mouseDoubleClickEvent(QMouseEvent* event) override;

    signals:
        void backButtonClicked();

    public slots:
        void enableBackButton();
        void disableBackButton();

    private:
        void onMinButtonClicked();
        void onMaxButtonClicked();
        void onCloseButtonClicked();

    private:
        QHBoxLayout* _layout;
        QLabel* _iconLabel;
        QLabel* _titleLabel;
        _BackButton* _backButton;
        _CtrlButton* _minButton;
        _CtrlButton* _maxButton;
        _CtrlButton* _closeButton;

    private:
        bool _dragging = false;
        QPoint _dragStartPos;
        int _dragMargin = 8;
    };

    class _BackButton : public QLabel
    {
        Q_OBJECT
    public:
        _BackButton(QWidget* parent = nullptr);

    protected:
        #if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    void enterEvent(QEnterEvent* event) override;
#else
    void enterEvent(QEvent* event) override;
#endif
        void leaveEvent(QEvent* event) override;
        void mousePressEvent(QMouseEvent* event) override;
        void mouseReleaseEvent(QMouseEvent* event) override;
        void paintEvent(QPaintEvent* event) override;

    private:
        bool _pressed = false;
    };

    class _CtrlButton : public QPushButton
    {
        Q_OBJECT
    public:
        enum class Type { Min, Max, Close };

    public:
        void setType(Type type);
        Type getType();

        _CtrlButton(Type type, QWidget* parent = nullptr);

    protected:
        void paintEvent(QPaintEvent* event) override;

    private:
        QColor getParentBgColor();
        Type _type;
    };

}