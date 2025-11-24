#pragma once

#include <QMainWindow>

namespace Element
{
    class _ShadowWindow : public QMainWindow
    {
        Q_OBJECT
    public:
        void setWidget(QWidget* widget);

    public:
        _ShadowWindow(QWidget* parent = nullptr);

    protected:
        void changeEvent(QEvent *event) override;
        bool eventFilter(QObject* watched, QEvent* event) override;

    private:
        void applyResize();

    private:
        QWidget* _widget = nullptr;
    };

    class FramelessEf
    {
    public:
        static void setFrameless(QWidget* widget);
    };

}