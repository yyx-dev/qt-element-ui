#pragma once

#include <QString>

namespace Element
{

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

}
