#include "dpiscaler.h"

#include <QApplication>
#include <QtMath>
#ifdef Q_OS_WIN
#include <windows.h>
#endif

namespace QTElementUI
{

    int DPIScaler::w(int width)
    {
        return width * _scaleFactor;
    }

    int DPIScaler::h(int height)
    {
        return qCeil(height * _scaleFactor);
    }

    QSize DPIScaler::scale(const QSize& size)
    {
        return QSize(w(size.width()), h(size.height()));
    }

    DPIScaler& DPIScaler::instance()
    {
        static DPIScaler instance;
        return instance;
    }

    DPIScaler::DPIScaler() : _scaleFactor(0)
    {
        _scaleFactor = getScaleFactor();
    }

    double DPIScaler::getScaleFactor() {
#ifdef Q_OS_WIN
        HDC screenDC = GetDC(nullptr);
        int dpiX = GetDeviceCaps(screenDC, LOGPIXELSX);
        ReleaseDC(nullptr, screenDC);
        return dpiX / 96.0;
#endif
    }

}
