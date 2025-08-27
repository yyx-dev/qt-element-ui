#include "mainwindow.h"
#include "scrollbar.h"
#include "fontmanager.h"
#include "logger.h"

#include "dpiscaler.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QApplication app(argc, argv);


    QTElementUI::ScrollBarSetting()(&app);

    QTElementUI::Log::setLevel(QTElementUI::Log::Level::Debug);

    QTElementUI::FontManager::instance().setApplicationFont("微软雅黑");
    QTElementUI::FontManager::instance().loadFont(":/fonts/Inter-Regular.ttf", "Inter-Regular");
    QTElementUI::FontManager::instance().loadFont(":/fonts/NotoSans-Regular.ttf", "NotoSans-Regular");

    MainWindow w;

    w.setWindowIcon(QIcon(":/icons/qt-logo.png").pixmap(16, 16));
    w.setWindowTitle("QT Element UI 效果展示");

    w.show();


    return app.exec();
}
