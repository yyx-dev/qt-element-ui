#include "app.h"
#include "window.h"
#include "widget.h"

// #define TEST

#include "mainwindow.h"

int main(int argc, char* argv[])
{
    Element::App app(argc, argv);
#ifdef TEST
    MainWindow window;
#else
    Element::Window window;
    Example::Widget widget(&window);
    widget.setupComponents();
    window.setWidget(&widget);
#endif

    window.show();

    return app.exec();
}
