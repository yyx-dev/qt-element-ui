#include "app.h"
#include "widget.h"
#include "mainwindow.h"

// #define TEST

int main(int argc, char* argv[])
{
    Element::App app(argc, argv);

#ifdef TEST
    MainWindow window;
    window.show();
#else
    Example::Widget widget;
    widget.show();
#endif

    return app.exec();
}
