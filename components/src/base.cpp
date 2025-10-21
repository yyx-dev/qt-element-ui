#include "base.h"
#include "color.h"

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

    QFont FontManager::font()
    {
        QFont font;
        font.setFamilies(Comm::fontFmailies);
        font.setHintingPreference(QFont::HintingPreference::PreferNoHinting);
        return font;
    }

    QFont FontManager::font(QFont font)
    {
        font.setFamilies(Comm::fontFmailies);
        font.setHintingPreference(QFont::HintingPreference::PreferNoHinting);
        return font;
    }


    FontManager::FontManager()
    {}
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

    QSize ScaleHelper::scale(QSize size)
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
    Arrow::Arrow(QWidget* partner, QWidget* target)
        : Arrow(Color::primaryText(), Direction::Down, partner, target)
    {}

    Arrow::Arrow(const QString& color, Direction dir, QWidget* partner, QWidget* target)
        : QWidget(target->parentWidget())
        , _partner(partner)
        , _target(target)
    {
        setFixedSize(16, 8);
        setAttribute(Qt::WA_TransparentForMouseEvents);
        setColor(color);
        setDirection(dir);
        updatePosition();
    }

    void Arrow::setColor(const QString& color)
    {
        _color = color;
        update();
    }

    void Arrow::setDirection(Direction direction)
    {
        _direction = direction;
        update();
    }

    void Arrow::setBorder(const QString& color)
    {
        _borderColor = color;
        update();
    }

    void Arrow::paintEvent(QPaintEvent*)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QPolygon triangle;
        switch (_direction)
        {
        case Direction::Down:
            triangle << QPoint(0, 0) << QPoint(16, 0) << QPoint(8, 8);
            break;
        case Direction::Up:
            triangle << QPoint(0, 8) << QPoint(16, 8) << QPoint(8, 0);
            break;
        case Direction::Left:
            triangle << QPoint(8, 0) << QPoint(8, 16) << QPoint(0, 8);
            break;
        case Direction::Right:
            triangle << QPoint(0, 0) << QPoint(0, 16) << QPoint(8, 8);
            break;
        }

        // 绘制填充
        painter.setBrush(QColor(_color));
        painter.setPen(Qt::NoPen);
        painter.drawPolygon(triangle);

        // 绘制左斜边和右斜边
        if (!_borderColor.isEmpty())
        {
            QColor bc(_borderColor);
            QPen borderPen(bc);

            borderPen.setWidth(1);
            painter.setPen(borderPen);
            painter.setBrush(Qt::NoBrush);

            if (_direction == Direction::Down)
            {
                painter.drawLine(triangle[0], triangle[2]); // 左斜边
                painter.drawLine(triangle[1], triangle[2]); // 右斜边
            }
            else if (_direction == Direction::Up)
            {
                painter.drawLine(triangle[0], triangle[2]); // 左斜边
                painter.drawLine(triangle[1], triangle[2]); // 右斜边
            }
            else if (_direction == Direction::Left)
            {
                painter.drawLine(triangle[0], triangle[2]); // 上斜边
                painter.drawLine(triangle[1], triangle[2]); // 下斜边
            }
            else if (_direction == Direction::Right)
            {
                painter.drawLine(triangle[0], triangle[2]); // 上斜边
                painter.drawLine(triangle[1], triangle[2]); // 下斜边
            }
        }
    }

    void Arrow::showEvent(QShowEvent* event)
    {
        updatePosition();
        QWidget::showEvent(event);
    }

    void Arrow::updatePosition()
    {
        if (!_target) return;

        QPoint pos;
        if (_direction == Direction::Up)
        {
            pos = QPoint(_target->x() + (_target->width() - 16) / 2,
                         _partner->y() - 8);
        }
        else if (_direction == Direction::Down)
        {
            pos = QPoint(_target->x() + (_target->width() - 16) / 2,
                         _partner->y() + _partner->height());
        }
        else if (_direction == Direction::Left)
        {
            setFixedSize(8, 16);
            pos = QPoint(_partner->x() - 8,
                         _target->y() + (_target->height() - 16) / 2);
        }
        else if (_direction == Direction::Right)
        {
            setFixedSize(8, 16);
            pos = QPoint(_partner->x() + _partner->width(),
                         _target->y() + (_target->height() - 16) / 2);
        }

        move(pos);
    }
}
