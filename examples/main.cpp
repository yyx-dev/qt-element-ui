#include "mainwindow.h"
#include "scrollbar.h"
#include "color.h"
#include "icon.h"
#include "tools/fontmanager.h"
#include "tools/logger.h"
#include "tools/dpiscaler.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char* argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QApplication app(argc, argv);

    Element::SetScrollBar()(&app);

    Element::Log::setLevel(Element::Log::Level::Debug);

    Element::FontManager::instance().setApplicationFont("微软雅黑");
    Element::FontManager::instance().loadFont(":/fonts/Inter-Regular.ttf", "Inter-Regular");
    Element::FontManager::instance().loadFont(":/fonts/NotoSans-Regular.ttf", "NotoSans-Regular");

    MainWindow w;

    w.setWindowIcon(Element::Icon::instance().getIcon(
        Element::Icon::Name::ElementPlus, Element::Color::primary(), 32));
    w.setWindowTitle("QT Element UI 效果展示");

    w.show();

    return app.exec();
}
