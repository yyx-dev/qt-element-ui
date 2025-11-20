#pragma once

#include <QWidget>

namespace Element
{
    class Mask;

    class MaskEf
    {
    public:
        static Mask* setMask(QWidget* partner, QWidget* covered);
    };

    class Mask : public QWidget
    {
        Q_OBJECT
    public:
        Mask(QWidget* partner, QWidget* covered);

    signals:
        void clicked();

    protected:
        bool eventFilter(QObject* watched, QEvent* event) override;
        void paintEvent(QPaintEvent* event) override;
        void mousePressEvent(QMouseEvent* event) override;

    private:
        QWidget* _partner = nullptr;
        QWidget* _covered = nullptr;
    };

}
