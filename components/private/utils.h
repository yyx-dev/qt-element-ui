#pragma once

#include "qfont.h"
#include "qpainter.h"
#include <QWidget>
#include <QFontDatabase>
#include <QHash>
#include <QDebug>

namespace Element
{
    struct Comm
    {
        static QString fontFmaily;
        static QStringList fontFmailies;
        static int defaultFontSize;
        static int largeFontSize;
        static int smallFontSize;
    };

    class QSSHelper
    {
    public:
        QSSHelper(const QString& qss = "");
        QSSHelper& operator=(const QString& qss);
        QStringList getGroupNames() const; // 获取所有样式组名称
        QStringList getProperties(const QString &groupName) const; // 获取指定组的属性列表
        QSSHelper& setProperty(const QString &groupName, const QString &key, const QString &value); // 向指定组添加属性
        QSSHelper& removeProperty(const QString &groupName, const QString &property); // 从指定组移除属性
        QSSHelper& clearGroup(const QString &groupName); // 清空指定组的所有属性并移除该组
        QString generate() const; // 生成QSS字符串
    private:
        void parse(const QString &qss);
    private:
        QHash<QString, QStringList> _styleGroups;
    };

    class Log
    {
    public:
        enum class Level { Debug=0, Info, Warn, Error, Fatal };
        static void debug(const QString& msg);
        static void info (const QString& msg);
        static void warn (const QString& msg);
        static void error(const QString& msg);
        static void fatal(const QString& msg);
        static void setLevel(Level lv);
    private:
        static QString coloredLevel(Level level);
        static void log(Level level, const QString& msg);
    private:
        static Level _level;
    };

    class FontLoader
    {
    public:
        static FontLoader& instance();
        void loadFont(const QString& fontPath, const QString& name = "");
        void setApplicationFont(const QString& name);

    private:
        FontLoader();
        FontLoader(const FontLoader&) = delete;
        FontLoader& operator=(const FontLoader&) = delete;

    private:
        QHash<QString, QString> _fontMap;
    };

    class FontHelper
    {
    public:
        FontHelper();
        FontHelper(QFont font);
        FontHelper& setFont(QFont font);
        FontHelper& setPointSize(int pointSize);
        FontHelper& setPixelSize(int pixelSize);
        FontHelper& setBold(bool bold = true);
        QFont getFont();

        int getTextWidth(const QString& text);
        int getTextHeight();

    private:
        QFont _font;
    };

    class ScaleHelper
    {
    public:
        static ScaleHelper& instance();
        int scale(int v);
        QSize scale(int w, int h);
        QSize scale(const QSize& size);
    private:
        ScaleHelper();
        ScaleHelper(const ScaleHelper&) = delete;
        ScaleHelper& operator=(const ScaleHelper&) = delete;
    private:
        qreal _factor;
    };

    inline int sc(int v) {
        return ScaleHelper::instance().scale(v);
    }
    inline QSize sc(int w, int h) {
        return ScaleHelper::instance().scale(w, h);
    }
    inline QSize sc(const QSize& size) {
        return ScaleHelper::instance().scale(size);
    }


    class DebugHelper
    {
    public:
        static void drawBorder(QPainter& painter, const QRect& rect);
    };

    inline void setBgColor(QWidget* widget, const QColor& color)
    {
        QPalette pal = widget->palette();
        pal.setColor(QPalette::Window, color);
        widget->setAutoFillBackground(true);
        widget->setPalette(pal);
    }

}