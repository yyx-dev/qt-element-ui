#pragma once

#include <QFontDatabase>
#include <QHash>
#include <QString>

namespace QTElementUI
{

    class FontManager
    {
    public:
        static FontManager& instance();

        // 加载字体资源
        bool loadFont(const QString& fontPath, const QString& alias = "");

        // 设置应用字体
        bool setApplicationFont(const QString& fontAlias, int pointSize = -1);

        // 获取所有已加载字体
        QHash<QString, QString> loadedFonts() const;

        // 检查字体是否已加载
        bool isFontLoaded(const QString& fontAlias) const;

    private:
        explicit FontManager();
        FontManager(const FontManager&) = delete;
        FontManager& operator=(const FontManager&) = delete;

    private:
        QHash<QString, QString> _fontMap;
    };

}
