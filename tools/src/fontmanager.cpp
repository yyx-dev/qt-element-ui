#include "../include/fontmanager.h"
#include "../../tools/include/logger.h"

#include <QApplication>
#include <QFile>
#include <QDebug>

namespace QTElementUI
{

    FontManager::FontManager()
    {}

    FontManager& FontManager::instance()
    {
        static FontManager instance;
        return instance;
    }

    bool FontManager::loadFont(const QString& fontPath, const QString& alias)
    {
        if (_fontMap.contains(alias))
        {
            Log::debug("Font with alias " + alias + " already loaded");
            return true;
        }

        QFile fontFile(fontPath);
        if (!fontFile.open(QIODevice::ReadOnly))
        {
            Log::error("Failed to open font file: " + fontPath);
            return false;
        }

        QByteArray fontData = fontFile.readAll();
        fontFile.close();

        int fontId = QFontDatabase::addApplicationFontFromData(fontData);
        if (fontId == -1)
        {
            Log::error("Failed to load font from: " + fontPath);
            return false;
        }

        QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);

        // 存储字体信息
        QString fontKey = alias.isEmpty() ? fontFamily : alias;
        _fontMap.insert(fontKey, fontFamily);

        Log::debug("Successfully loaded font: " + fontFamily + ", with alias: " + fontKey);
        return true;
    }

    bool FontManager::setApplicationFont(const QString& fontAlias, int pointSize)
    {
        if (!_fontMap.contains(fontAlias))
        {
            Log::debug("Font not found: " + fontAlias);
            return false;
        }

        QString fontFamily = _fontMap.value(fontAlias);
        QFont font(fontFamily);

        if (pointSize > 0)
            font.setPointSize(pointSize);

        QApplication::setFont(font);
        Log::debug("Application font set to: " + fontFamily);

        return true;
    }

    QHash<QString, QString> FontManager::loadedFonts() const
    {
        return _fontMap;
    }

    bool FontManager::isFontLoaded(const QString& fontAlias) const
    {
        return _fontMap.contains(fontAlias);
    }

}
