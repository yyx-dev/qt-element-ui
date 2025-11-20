#include "base.h"
#include "qfont.h"

#include <QPainter>
#include <QRegularExpression>
#include <QApplication>
#include <QFile>
#include <QDateTime>

#ifdef Q_OS_WIN
#include <windows.h>
#endif

namespace Element
{
    QString Comm::fontFmaily = "'Noto Sans', 'Microsoft YaHei', 微软雅黑";
    QStringList Comm::fontFmailies = {"Noto Sans", "Microsoft YaHei", "微软雅黑"};

    int Comm::defaultFontSize = 10;
    int Comm::largeFontSize = 12;
    int Comm::smallFontSize = 8;
}

namespace Element
{
    QSSHelper::QSSHelper(const QString& qss)
    {
        if (!qss.isEmpty())
            parse(qss);
    }

    QSSHelper& QSSHelper::operator=(const QString& qss)
    {
        if (!qss.isEmpty())
            parse(qss);

        return *this;
    }

    void QSSHelper::parse(const QString &qss)
    {
        _styleGroups.clear();

        // 使用正则表达式匹配样式组
        QRegularExpression groupRegex(R"(([^{]+)\s*\{([^}]+)\})");
        QRegularExpressionMatchIterator it = groupRegex.globalMatch(qss);

        while (it.hasNext())
        {
            QRegularExpressionMatch match = it.next();
            QString groupName = match.captured(1).trimmed();
            QString groupContent = match.captured(2).trimmed();

            // 分割属性
            QStringList properties = groupContent.split(';', QString::SkipEmptyParts);
            QStringList trimmedProperties;

            for (QString prop : properties)
                trimmedProperties << prop.trimmed();

            _styleGroups[groupName] = trimmedProperties;
        }
    }

    QStringList QSSHelper::getGroupNames() const
    {
        return _styleGroups.keys();
    }

    QStringList QSSHelper::getProperties(const QString &groupName) const
    {
        return _styleGroups.value(groupName, QStringList());
    }

    QSSHelper& QSSHelper::setProperty(const QString &groupName, const QString &key, const QString &value)
    {
        // 如果组不存在，先创建空组
        if (!_styleGroups.contains(groupName)) {
            _styleGroups[groupName] = QStringList();
        }

        QStringList &properties = _styleGroups[groupName];
        QString newProperty = QString("%1: %2").arg(key).arg(value);

        // 检查是否已存在相同key的属性
        bool found = false;
        for (int i = 0; i < properties.size(); ++i) {
            if (properties[i].startsWith(key + ":")) {
                properties[i] = newProperty; // 覆盖现有属性
                found = true;
                break;
            }
        }

        if (!found) {
            properties << newProperty;
        }

        return *this;
    }

    QSSHelper& QSSHelper::removeProperty(const QString &groupName, const QString &property)
    {
        if (_styleGroups.contains(groupName))
        {
            QStringList &properties = _styleGroups[groupName];
            properties.removeAll(property);

            // 如果组为空，则移除整个组
            if (properties.isEmpty())
                _styleGroups.remove(groupName);
        }

        return *this;
    }

     QSSHelper& QSSHelper::clearGroup(const QString &groupName)
    {
        _styleGroups.remove(groupName);
        return *this;
    }

    QString QSSHelper::generate() const
    {
        QString result;

        for (auto it = _styleGroups.constBegin(); it != _styleGroups.constEnd(); ++it)
        {
            const QString &groupName = it.key();
            const QStringList &properties = it.value();

            result += groupName + " {\n";
            for (const QString &prop : properties)
                result += "    " + prop + ";\n";

            result += "}\n\n";
        }

        return result.trimmed();
    }

}

namespace Element
{
    void Log::debug(const QString& msg) { log(Level::Debug, msg); }
    void Log::info (const QString& msg) { log(Level::Info, msg);  }
    void Log::warn (const QString& msg) { log(Level::Warn, msg);  }
    void Log::error(const QString& msg) { log(Level::Error, msg); }
    void Log::fatal(const QString& msg) { log(Level::Fatal, msg); }

    void Log::setLevel(Level lv) { _level = lv; }

    QString Log::coloredLevel(Level level)
    {
        switch (level) {
            case Level::Debug: return "debug";                   // Default
            case Level::Info:  return "\033[32minfo\033[0m";     // Green
            case Level::Warn:  return "\033[33mwarn\033[0m";     // Yellow
            case Level::Error: return "\033[31merror\033[0m";    // Red
            case Level::Fatal: return "\033[41;97mfatal\033[0m"; // Red background, white text
        }
        return "";
    }

    void Log::log(Level level, const QString& msg)
    {
        if (level < _level)
            return;

        QString output = QString("[%1] [%2] %3")
                .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"), coloredLevel(level), msg);

        switch (level) {
            case Level::Debug:
                qDebug().noquote() << output;
                break;
            case Level::Info:
                qInfo().noquote() << output;
                break;
            case Level::Warn:
                qWarning().noquote() << output;
                break;
            case Level::Error:
                qCritical().noquote() << output;
                break;
            case Level::Fatal:
                qCritical().noquote() << output;
                break;
        }
    }

    Log::Level Log::_level = Log::Level::Debug;
}

namespace Element
{
    FontLoader& FontLoader::instance()
    {
        static FontLoader instance;
        return instance;
    }

    void FontLoader::loadFont(const QString& fontPath, const QString& name)
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

    void FontLoader::setApplicationFont(const QString &name)
    {
        QFont font;
        font.setFamily(name);
        QApplication::setFont(font);
    }

    FontLoader::FontLoader() {}

    FontHelper::FontHelper() { setFont(_font); }
    FontHelper::FontHelper(QFont font) { setFont(font); }

    FontHelper& FontHelper::setFont(QFont font)
    {
        _font = font;
        _font.setFamilies(Comm::fontFmailies);
        _font.setHintingPreference(QFont::HintingPreference::PreferNoHinting);
        return *this;
    }

    FontHelper& FontHelper::setPointSize(int pointSize)
    {
        _font.setPointSize(pointSize);
        return *this;
    }

    FontHelper& FontHelper::setPixelSize(int pixelSize)
    {
        _font.setPixelSize(pixelSize);
        return *this;
    }

    FontHelper& FontHelper::setBold(bool bold)
    {
        _font.setBold(bold);
        return *this;
    }

    QFont FontHelper::getFont() { return _font; }

    int FontHelper::getTextWidth(const QString& text)
    {
        return QFontMetrics(_font).horizontalAdvance(text);
    }

    int FontHelper::getTextHeight()
    {
        return QFontMetrics(_font).height();
    }

}


namespace Element
{
    ScaleHelper& ScaleHelper::instance()
    {
        static ScaleHelper instance;
        return instance;
    }

    int ScaleHelper::scale(int v)
    {
        return v * _factor;
    }

    QSize ScaleHelper::scale(int w, int h)
    {
        return QSize(w * _factor, h * _factor);
    }

    QSize ScaleHelper::scale(const QSize& size)
    {
        return scale(size.width(), size.height());
    }

    ScaleHelper::ScaleHelper()
    {
        _factor = 0.0;

#ifdef Q_OS_WIN
        HDC screenDC = GetDC(nullptr);
        int dpiX = GetDeviceCaps(screenDC, LOGPIXELSX);
        ReleaseDC(nullptr, screenDC);
        _factor = dpiX / 96.0;
#endif

        if (qFuzzyIsNull(_factor))
            Log::fatal("wrong system factor");
    }
}

namespace Element
{
    void DebugHelper::drawBorder(QPainter& painter, const QRect& rect)
    {
        QPen redPen(Qt::red, 1);
        painter.setPen(redPen);
        painter.setBrush(Qt::NoBrush);
        painter.drawRect(rect);
    }

}
