#pragma once

#include <QString>
#include <QStringList>

namespace QTElementUI
{
    struct CommonVar
    {
        static QString baseFontFmaily;
        static QStringList baseFontFmailies;

        static int defaultFontSize;
        static int largeFontSize;
        static int smallFontSize;

        static int regularFontWeight;
        static int boldFontWeight;

        static int buttonIconSize;
        static int inputIconSize;
    };

}
