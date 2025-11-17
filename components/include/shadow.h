#pragma once

#include <QGraphicsDropShadowEffect>
#include <QWidget>

namespace Element
{
    class Mask;

    class BackdropEffect
    {
    public:
        enum class ShadowType
        {
            Basic,
            Light,
            Lighter,
            Dark,
        };

    public:
        static void setShadow(QWidget* widget, ShadowType type);
        static Mask* setBgMask(QWidget* widget);
    };

    class Mask : public QWidget
    {
        Q_OBJECT
    public:
        Mask(QWidget* partner);

    signals:
        void clicked();

    protected:
        bool eventFilter(QObject* watched, QEvent* event) override;
        void paintEvent(QPaintEvent* event) override;
        void mousePressEvent(QMouseEvent* event) override;

    private:
        QWidget* _partner;
    };

}
