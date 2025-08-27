#include "iconmanager.h"
#include "commvar.h"
#include "color.h"
#include "logger.h"

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

    QIcon IconManager::getIcon(Icon icon, const QString &color, int size)
    {
        if (icon == Icon::None)
        {
            Log::error("IconManager.getIcon: icon name is none.");
            return QIcon();
        }

        int idx = static_cast<int>(icon);
        if (idx < 0 || idx > _iconList.size())
        {
            Log::error("IconManager.getIcon: icon index is out of range.");
            return QIcon();
        }

        QString name = _iconList[idx];

        auto key = std::make_tuple(name, color, size);

        if (_iconCache.contains(key))
            return _iconCache.value(key);

        QIcon res = createSvgIcon(QString(":/icons/%1.svg").arg(name), color, size);
        _iconCache.insert(key, res);
        return res;
    }

    void IconManager::preloadIcons()
    {
        QList<Icon> commonIcons = {
            Icon::Search, Icon::Star, Icon::Edit, Icon::Check
        };

        QStringList commonColors = {
            Color::blankFill(),
            Color::placeholderText(),
            Color::regularText()
        };

        QList<int> commonSizes = {16, 18, 20, 22, 24, 32};

        for (Icon icon : commonIcons) {
            for (const QString& color : commonColors) {
                for (int size : commonSizes) {
                    getIcon(icon, color, size);
                }
            }
        }
    }

    QIcon IconManager::createSvgIcon(const QString &path, const QString &color, int size)
    {
        if (!QFile::exists(path))
        {
            Log::error("IconManager.createSvgIcon: Icon file not found: " + path);
            return QIcon();
        }

        QFile file(path);
        if (!file.open(QIODevice::ReadOnly))
        {
            Log::error("IconManager.createSvgIcon: Failed to open icon file: " + path);
            return QIcon();
        }

        QString svgData = file.readAll();
        file.close();

        svgData.replace("fill=\"currentColor\"", QString("fill=\"%1\"").arg(color));


        QSvgRenderer renderer(svgData.toUtf8());

        QPixmap pixmap(size, size);
        pixmap.fill(Qt::transparent);

        QPainter painter(&pixmap);
        renderer.render(&painter);

        QIcon icon;
        icon.addPixmap(pixmap);

        return icon;
    }

    IconManager::IconManager()
        : _iconList({
            "add-location", "aim", "alarm-clock", "apple", "arrow-down", "arrow-down-bold", "arrow-left", "arrow-left-bold", "arrow-right", "arrow-right-bold", "arrow-up", "arrow-up-bold", "avatar",
            "back", "baseball", "basketball", "bell", "bell-filled", "bicycle", "bottom", "bottom-left", "bottom-right", "bowl", "box", "briefcase", "brush", "brush-filled", "burger",
            "calendar", "camera", "camera-filled", "caret-bottom", "caret-left", "caret-right", "caret-top", "cellphone", "chat-dot-round", "chat-dot-square", "chat-line-round", "chat-line-square", "chat-round",
            "chat-square", "check", "checked", "cherry", "chicken", "chrome-filled", "circle-check", "circle-check-filled", "circle-close", "circle-close-filled", "circle-plus", "circle-plus-filled", "clock",
            "close", "close-bold", "cloudy", "coffee", "coffee-cup", "coin", "cold-drink", "collection", "collection-tag", "comment", "compass", "connection", "coordinate", "copy-document", "cpu", "credit-card",
            "crop",
            "d-arrow-left", "d-arrow-right", "data-analysis", "data-board", "data-line", "d-caret", "delete", "delete-filled", "delete-location", "dessert", "discount", "dish", "dish-dot", "document",
            "document-add", "document-checked", "document-copy", "document-delete", "document-remove", "download", "drizzling",
            "edit", "edit-pen", "eleme", "eleme-filled", "element-plus", "expand",
            "failed", "female", "files", "film", "filter", "finished", "first-aid-kit", "flag", "fold", "folder", "folder-add", "folder-checked", "folder-delete",
            "folder-opened", "folder-remove", "food", "football", "fork-spoon", "fries", "full-screen",
            "goblet", "goblet-full", "goblet-square", "goblet-square-full", "gold-medal", "goods", "goods-filled", "grape", "grid", "guide",
            "handbag", "headset", "help", "help-filled", "hide", "histogram", "home-filled", "hot-water", "house",
            "ice-cream", "ice-cream-round", "ice-cream-square", "ice-drink", "ice-tea", "info-filled", "iphone",
            "key", "knife-fork",
            "lightning", "link", "list", "loading", "location", "location-filled", "location-information", "lock", "lollipop",
            "magic-stick", "magnet", "male", "management", "map-location", "medal", "memo", "menu", "message", "message-box", "mic", "microphone",
            "milk-tea", "minus", "money", "monitor", "moon", "moon-night", "more", "more-filled", "mostly-cloudy", "mouse", "mug", "mute", "mute-notification",
            "no-smoking", "notebook", "notification",
            "odometer", "office-building", "open", "operation", "opportunity", "orange",
            "paperclip", "partly-cloudy", "pear", "phone", "phone-filled", "picture", "picture-filled", "picture-rounded", "pie-chart", "place", "platform",
            "plus", "pointer", "position", "postcard", "pouring", "present", "price-tag", "printer", "promotion",
            "quartz-watch", "question-filled",
            "rank", "reading", "reading-lamp", "refresh", "refresh-left", "refresh-right", "refrigerator", "remove", "remove-filled", "right",
            "scale-to-original", "school", "scissor", "search", "select", "sell", "semi-select", "service", "setting", "set-up", "share", "ship", "shop",
            "shopping-bag", "shopping-cart", "shopping-cart-full", "shopping-trolley", "smoking", "soccer", "sold-out", "sort", "sort-down", "sort-up", "stamp",
            "star", "star-filled", "stopwatch", "success-filled", "sugar", "suitcase", "suitcase-line", "sunny", "sunrise", "sunset", "switch", "switch-button", "switch-filled",
            "takeaway-box", "ticket", "tickets", "timer", "toilet-paper", "tools", "top", "top-left", "top-right", "trend-charts", "trophy", "trophy-base", "turn-off",
            "umbrella", "unlock", "upload", "upload-filled", "user", "user-filled",
            "van", "video-camera", "video-camera-filled", "video-pause", "video-play", "view",
            "wallet", "wallet-filled", "warning", "warning-filled", "warn-triangle-filled", "watch", "watermelon", "wind-power",
            "zoom-in", "zoom-out",
        })
    {
        preloadIcons();
    }
}
