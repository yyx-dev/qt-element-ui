#pragma once

#include <QObject>
#include <QIcon>
#include <QMap>
#include <QColor>

namespace QTElementUI
{

    class IconManager
    {

    public:
        // 获取单例实例
        static IconManager& instance();

        IconManager(const IconManager&) = delete;
        IconManager& operator=(const IconManager&) = delete;


        QIcon getIcon(const QString& name);
        QIcon getIcon(const QString& name, const QString& color);

        void preloadIcons();

    private:
        explicit IconManager();

         QIcon createSvgIcon(const QString &path, const QString &color);

    private:
        //name&color -> icon
        QMap<QPair<QString, QString>, QIcon> _coloredIconCache;
    };

}
