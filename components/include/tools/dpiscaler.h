#pragma once

#include <QSize>

namespace QTElementUI
{
    class DPIScaler
    {
    public:
        int w(int width);

        int h(int height);

        QSize scale(const QSize& size);

        DPIScaler& instance();

    private:
        DPIScaler();

        double _scaleFactor;

    private:
        double getScaleFactor();
    };
}
