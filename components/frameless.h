#pragma once

#include <QWidget>

namespace Element
{
    class DragProxy;

    class FramelessWindow : public QWidget
    {
        Q_OBJECT
    public:
        FramelessWindow(QWidget* parent = nullptr);
        QMargins getDraMargins();

    protected:
        void showEvent(QShowEvent* event) override;

    private:
        DragProxy* _dragProxy = nullptr;
    };

    class DragProxy : public QObject
    {
        Q_OBJECT

    public:
        void setMargins(const QMargins& margins);
        void setMargins(int top, int right, int bottom, int left);
        QMargins getMargins();

    public:
        DragProxy(QWidget* parent);

    protected:
        enum Region
        {
            Top = 0,
            TopRight,
            Right,
            RightBottom,
            Bottom,
            LeftBottom,
            Left,
            LeftTop,
            Inner,
            Unknown
        };

    protected:
        bool eventFilter(QObject* obj, QEvent* event);

        void checkRegions();
        Region hitRegion(const QPoint& pos);
        void updateGeometry(int x, int y, int w, int h);

        // 鼠标从边框快速移到窗体内子控件上，
        // 可能会造成鼠标样式未改变，这里使用计时器监控
        void startCursorTimer();
        void stopCursorTimer();

    private:
        QWidget* _proxyWidget = nullptr;
        QMargins _margins = {8, 8, 8, 8};
        QRect _regions[9];
        QPoint _originPosGlobal;
        QRect _originGeo;
        bool _mousePressed = false;
        Region _regionPressed = Unknown;
        int _cursorTimerId = 0;
    };
}