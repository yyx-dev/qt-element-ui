#include "../include/logger.h"

#include <QDateTime>
#include <QDebug>
#include <QString>

namespace QTElementUI
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
            case Level::Debug: return "debug";                             // Default
            case Level::Info:  return "\033[32minfo\033[0m";               // Green
            case Level::Warn:  return "\033[33mwarn\033[0m";               // Yellow
            case Level::Error: return "\033[31merror\033[0m";              // Red
            case Level::Fatal: return "\033[41;97mfatal\033[0m";           // Red background, white text
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
