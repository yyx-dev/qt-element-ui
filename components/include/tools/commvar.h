#pragma once

#include <QString>
#include <QStringList>

namespace Element
{
    struct CommonVar
    {
        static QString fontFmaily;
        static QStringList fontFmailies;

        static int defaultFontSize;
        static int largeFontSize;
        static int smallFontSize;

        static int regularFontWeight;
        static int boldFontWeight;

        static int buttonIconSize;
        static int inputIconSize;
    };

}
