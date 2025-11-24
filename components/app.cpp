#include "app.h"
#include "scrollbar.h"
#include "base.h"
#include "color.h"

namespace Element
{
    App::App(int argc, char **argv)
    {
        QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
        QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

        _app = new QApplication(argc, argv);

        // ScrollBar::setAppScrollBar();
        Log::setLevel(Element::Log::Level::Debug);

        FontLoader::instance().setApplicationFont("微软雅黑");
        FontLoader::instance().loadFont(":/fonts/Inter-Regular.ttf", "Inter-Regular");
        FontLoader::instance().loadFont(":/fonts/NotoSans-Regular.ttf", "NotoSans-Regular");

        setWindowIcon(Element::Icon::ElementPlus);

        setApplicationName("qt-element-ui");
        setApplicationDisplayName("QT Element UI");
        setApplicationVersion("beta-0.0.1");
        setOrganizationName("yyx");
        setOrganizationDomain("yyx.org");

    }

    App::~App()
    {
        delete _app;
    }

    void App::setPalette(const QPalette& p)
    {
        QApplication::setPalette(p);
    }

    void App::setWindowIcon(Icon::Name icon)
    {
        QApplication::setWindowIcon(Icon::instance().getIcon(icon, Color::primary(), 32));
    }

    void App::setWindowIcon(QIcon icon)
    {
        QApplication::setWindowIcon(icon);
    }

    void App::setApplicationName(const QString& name)
    {
        QApplication::setApplicationName(name);
    }

    void App::setApplicationDisplayName(const QString& name)
    {
        QApplication::setApplicationDisplayName(name);
    }

    void App::setApplicationVersion(const QString& version)
    {
        QApplication::setApplicationVersion(version);
    }

    void App::setOrganizationName(const QString& name)
    {
        QApplication::setOrganizationName(name);
    }

    void App::setOrganizationDomain(const QString& domain)
    {
        QApplication::setOrganizationDomain(domain);
    }

    int App::exec()
    {
        return QApplication::exec();
    }

    QIcon App::getWindowIcon()
    {
        return QApplication::windowIcon();
    }

    QString App::getApplicationDisplayName()
    {
        return QApplication::applicationDisplayName();
    }
}
