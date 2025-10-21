#pragma once

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

    class FontManager
    {
    public:
        static FontManager& instance();
        void loadFont(const QString& fontPath, const QString& name = "");
        void setApplicationFont(const QString& name);
        static QFont font();
        static QFont font(QFont font);
    private:
        FontManager();
        FontManager(const FontManager&) = delete;
        FontManager& operator=(const FontManager&) = delete;
    private:
        QHash<QString, QString> _fontMap;
    };

    class ScaleHelper
    {
    public:
        static ScaleHelper& instance();
        int scale(int v);
        QSize scale(int w, int h);
        QSize scale(QSize size);
    private:
        ScaleHelper();
        ScaleHelper(const ScaleHelper&) = delete;
        ScaleHelper& operator=(const ScaleHelper&) = delete;
    private:
        qreal _factor;
    };
}

namespace Element
{
    // Two objects need to be set: partner and target.
    // Partner is the pop-up widget, target is the pointing widget
    class Arrow : public QWidget
    {
    Q_OBJECT

    public:
        enum class Direction { Up, Down, Left, Right };

    public:
        Arrow(QWidget* partner, QWidget* target);
        Arrow(const QString& color, Direction dir, QWidget* partner, QWidget* target);

        void setColor(const QString& color);
        void setDirection(Direction direction);

        // Due to anti-aliasing,
        // the actual border color will appear lighter.
        // Therefore, please set a darker color.​
        void setBorder(const QString& color);

    protected:
        void paintEvent(QPaintEvent* event) override;
        void showEvent(QShowEvent* event) override;

    private:
        void updatePosition();

    private:
        QWidget* _partner = nullptr;
        QWidget* _target = nullptr;

        Direction _direction = Direction::Down;
        QString _color;
        QString _borderColor;
    };
}
