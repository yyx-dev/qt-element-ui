#pragma once

#include "icon.h"

#include <QApplication>

namespace Element
{
    class App : public QObject
    {
    public:
        static void setPalette(const QPalette& p);
        static void setWindowIcon(Icon::Name icon);
        static void setWindowIcon(QIcon icon);

        static void setApplicationName(const QString& name);
        static void setApplicationDisplayName(const QString& name);
        static void setApplicationVersion(const QString& version);
        static void setOrganizationName(const QString& name);
        static void setOrganizationDomain(const QString& domain);

        static QIcon getWindowIcon();
        static QString getApplicationDisplayName();

        static int exec();

    public:
        App(int argc, char **argv);
        ~App();

    private:
        QApplication* _app;
    };

}
