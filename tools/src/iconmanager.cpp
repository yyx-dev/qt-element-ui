#include "../include/iconmanager.h"
#include "../include/commvar.h"
#include "components/include/color.h"

#include <QSvgRenderer>
#include <QFile>
#include <QPixmap>
#include <QPainter>
#include <QApplication>
#include <QDir>
#include <QDebug>

namespace QTElementUI
{

    IconManager& IconManager::instance()
    {
        static IconManager instance;
        return instance;
    }

    IconManager::IconManager()
    {
        preloadIcons();
    }

    QIcon IconManager::getIcon(const QString &name)
    {
        return getIcon(name, Color::blankFill());
    }

    QIcon IconManager::getIcon(const QString &name, const QString &color)
    {
        // 检查缓存中是否已有
        QPair<QString, QString> key(name, color);
        if (_coloredIconCache.contains(key))
            return _coloredIconCache.value(key);

        // 构造图标并返回
        QString svgPath = QString(":/resources/icons/%1.svg").arg(name);

        QIcon icon = createSvgIcon(svgPath, color);
        _coloredIconCache.insert(key, icon);

        return icon;
    }

    void IconManager::preloadIcons()
    {
        QStringList commonIcons = CommonVar::commonIconList;

        foreach (const QString &name, commonIcons) {
            getIcon(name, Color::regularText());
            getIcon(name, Color::blankFill());
        }
    }

    QIcon IconManager::createSvgIcon(const QString &path, const QString &color)
    {
        // 检查文件是否存在
        if (!QFile::exists(path))
        {
            qDebug() << "Icon file not found:" << path;
            return QIcon();
        }

        // 读取SVG文件内容
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly))
        {
            qDebug() << "Failed to open icon file:" << path;
            return QIcon();
        }

        QString svgData = file.readAll();
        file.close();

        // 替换颜色
        svgData.replace("fill=\"currentColor\"", QString("fill=\"%1\"").arg(color));

        // 创建渲染器
        QSvgRenderer renderer(svgData.toUtf8());

        // 创建不同尺寸的图标
        QIcon icon;
        QList<int> sizes = {16, 18, 32, 48}; // 多种尺寸

        foreach (int size, sizes) {
            QPixmap pixmap(size, size);
            pixmap.fill(Qt::transparent);

            QPainter painter(&pixmap);
            renderer.render(&painter);

            icon.addPixmap(pixmap);
        }

        return icon;
    }

}
