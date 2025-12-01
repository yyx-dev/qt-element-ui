#pragma once

#include <QWidget>

namespace Element
{
    class FramelessWindow : public QWidget
    {
        Q_OBJECT
    public:
        FramelessWindow(QWidget* parent = nullptr);

    protected:
        void showEvent(QShowEvent *event) override;
    };

    class DragProxy : public QObject
    {
        Q_OBJECT

    public:
        void setBorderWidth(int top, int right, int bottom, int left);
        DragProxy(QWidget *parent);

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
        virtual bool eventFilter(QObject* obj, QEvent* event);

        void makeRegions();
        Region hitRegion(const QPoint& pos);
        void updateGeometry(int x, int y, int w, int h);

        // 鼠标从边框快速移到窗体内子控件上，
        // 可能会造成鼠标样式未改变，这里使用计时器监控
        void startCursorTimer();
        void stopCursorTimer();

    private:
        QWidget* _proxyWidget;
        int _top, _right, _bottom, _left;
        QRect _regions[9];

        QPoint _originPosGlobal; // 拖拽前鼠标位置
        QRect _originGeo;        // 拖拽前窗体位置和大小

        bool _mousePressed; // 鼠标是否按下
        Region _regionPressed; // 记录鼠标按下时所点击的区域

        int _cursorTimerId;
    };
}