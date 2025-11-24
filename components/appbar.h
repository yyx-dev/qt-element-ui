#pragma once

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>

namespace Element
{
    class _AppBarButton;

    class AppBar : public QWidget
    {
        Q_OBJECT
    public:
        AppBar& setBgColor(const QString& color);

    public:
        AppBar(QWidget* parent = nullptr);

    protected:
        void changeEvent(QEvent* event) override;
        void mousePressEvent(QMouseEvent* event) override;
        void mouseMoveEvent(QMouseEvent* event) override;
        void mouseReleaseEvent(QMouseEvent* event) override;
        void paintEvent(QPaintEvent* event) override;
        void mouseDoubleClickEvent(QMouseEvent* event);
    private:
        void onMinButtonClicked();
        void onMaxButtonClicked();
        void onCloseButtonClicked();

    private:
        QHBoxLayout* _layout;
        QLabel* _iconLabel;
        QLabel* _titleLabel;
        QLabel* _backButton;
        _AppBarButton* _minButton;
        _AppBarButton* _maxButton;
        _AppBarButton* _closeButton;

    private:
        bool _dragging = false;
        QPoint _dragStartPos;
    };

    class _AppBarButton : public QPushButton
    {
        Q_OBJECT
    public:
        enum class Type { Min, Max, Close };

    public:
        void setType(Type type);
        Type getType();

        _AppBarButton(Type type, QWidget* parent = nullptr);

    protected:
        void paintEvent(QPaintEvent* event) override;

    private:
        QColor getParentBgColor();
        Type _type;
    };

}