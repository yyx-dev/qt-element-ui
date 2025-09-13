#pragma once

#include <QFontDatabase>
#include <QHash>
#include <QString>

namespace Element
{

    class FontManager
    {
    public:
        static FontManager& instance();

        void loadFont(const QString& fontPath, const QString& name = "");
        void setApplicationFont(const QString& name);

    private:
        FontManager();
        FontManager(const FontManager&) = delete;
        FontManager& operator=(const FontManager&) = delete;

    private:
        QHash<QString, QString> _fontMap;
    };

}
