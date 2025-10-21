#include "icon.h"
#include "base.h"
#include "color.h"

#include <QSvgRenderer>
#include <QFile>
#include <QPixmap>
#include <QPainter>
#include <QApplication>
#include <QDir>


namespace Element
{

    Icon& Icon::instance()
    {
        static Icon instance;
        return instance;
    }

    QIcon Icon::getIcon(Icon::Name icon, const QString &color, int size)
    {
        return getIcon(icon, color, "", size);
    }

    QPixmap Icon::getPixmap(Icon::Name icon, const QString& color, int size)
    {
        return getPixmap(icon, color, "", size);
    }

    QIcon Icon::getIcon(Name icon, const QString& color, const QString& bgColor, int size)
    {
        if (!checkIcon(icon))
            return QIcon();

        auto key = std::make_tuple(_iconList[(int)icon], color, size);

        if (_iconCache.contains(key))
            return _iconCache.value(key);

        QIcon res = createSvgIcon(icon, color, bgColor, size);
        _iconCache.insert(key, res);

        return res;
    }

    QPixmap Icon::getPixmap(Name icon, const QString& color, const QString& bgColor, int size)
    {
        return getIcon(icon, color, bgColor, size).pixmap(size);
    }

    QString Icon::getCode(Icon::Name icon, const QString& color)
    {
        if (!checkIcon(icon))
            return QString();

        return readSvgData(icon, color);
    }

    QByteArray Icon::getCodeArray(Icon::Name icon, const QString& color)
    {
        return getCode(icon, color).toUtf8();
    }

    QSvgRenderer* Icon::getRenderer(Icon::Name icon, const QString& color, QObject* parent)
    {
        return new QSvgRenderer(getCodeArray(icon, color), parent);
    }

    bool Icon::checkIcon(Icon::Name icon)
    {
        if (Icon::isNull(icon))
        {
            Log::error("IconManager.checkIconIndex: icon name is none.");
            return false;
        }

        int idx = static_cast<int>(icon);
        if (idx < 0 || idx > _iconList.size())
        {
            Log::error("IconManager.checkIconIndex: icon index is out of range.");
            return false;
        }

        return true;
    }

    QString Icon::readSvgData(Icon::Name icon, const QString& color)
    {
        QString path = ":/icons/" + _iconList[(int)icon] + ".svg";

        if (!QFile::exists(path))
        {
            Log::error("IconManager.checkIconExist: Icon file not found: " + path);
            return QString();
        }

        QFile file(path);
        if (!file.open(QIODevice::ReadOnly))
        {
            Log::error("IconManager.checkIconExist: Failed to open icon file: " + path);
            return QString();
        }

        QString svgData = file.readAll();
        file.close();

        svgData.replace("fill=\"currentColor\"", QString("fill=\"%1\"").arg(color));

        return svgData;
    }

    QIcon Icon::createSvgIcon(Icon::Name icon, const QString& color, int size)
    {
        return createSvgIcon(icon, color, "", size);
    }

    QIcon Icon::createSvgIcon(Icon::Name icon, const QString& color, const QString& bgColor, int size)
    {
        QSvgRenderer renderer(readSvgData(icon, color).toUtf8());

        QPixmap pixmap(size, size);

        if (bgColor.isEmpty())
            pixmap.fill(Qt::transparent);
        else
            pixmap.fill(bgColor);

        QPainter painter(&pixmap);
        renderer.render(&painter);

        QIcon res;
        res.addPixmap(pixmap);
        return res;
    }


    void Icon::preloadIcons()
    {
        QList<Name> commonIcons = {
            Icon::Search, Name::Star, Name::Edit, Name::Check
        };

        QStringList commonColors = {
            Color::blankFill(),
            Color::placeholderText(),
            Color::regularText()
        };

        QList<int> commonSizes = {16, 18, 20, 22, 24, 32};

        for (Name icon : commonIcons) {
            for (const QString& color : commonColors) {
                for (int size : commonSizes) {
                    getIcon(icon, color, size);
                }
            }
        }
    }

    Icon::Icon()
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
