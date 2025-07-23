#include "../include/mainwindow.h"
#include "../../components/include/scrollbar.h"
#include "../../tools/include/fontmanager.h"
#include "../../tools/include/logger.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication app(argc, argv);

    QTElementUI::ScrollBarSetting()(&app);
    QTElementUI::Log::setLevel(QTElementUI::Log::Level::Debug);
    QTElementUI::FontManager::instance().loadFont(":/resources/fonts/NotoSans-Regular.ttf", "NotoSans-Regular");

    MainWindow w;

    w.setWindowIcon(QIcon(":/resources/icons/qt-logo.png").pixmap(16, 16));
    w.setWindowTitle("QT Element UI 效果展示    -- 目前已完成 color text button scrollbar container");

    w.show();

    return app.exec();
}
