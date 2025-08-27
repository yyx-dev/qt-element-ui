#include "fontmanager.h"
#include "logger.h"

#include <QApplication>
#include <QFile>
#include <QDebug>

namespace QTElementUI
{
    FontManager& FontManager::instance()
    {
        static FontManager instance;
        return instance;
    }

    void FontManager::loadFont(const QString& fontPath, const QString& name)
    {
        QFile fontFile(fontPath);
        if (!fontFile.open(QIODevice::ReadOnly))
            Log::error("Failed to open font file: " + fontPath);

        int fontId = QFontDatabase::addApplicationFontFromData(fontFile.readAll());
        if (fontId == -1)
            Log::error("Failed to load font from: " + fontPath);

        QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
        _fontMap.insert(name, fontFamily);
    }

    void FontManager::setApplicationFont(const QString &name)
    {
        QFont font;
        font.setFamily(name);
        QApplication::setFont(font);
    }

    FontManager::FontManager()
    {}
}
