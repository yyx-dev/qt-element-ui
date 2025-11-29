#include "app.h"

// #define EXAMPLE

#ifdef EXAMPLE
#   include "mainwindow.h"
#else
#   include "widget.h"
#endif

int main(int argc, char* argv[])
{
    Element::App app(argc, argv);

#ifdef EXAMPLE
    MainWindow window;
    window.show();
#else
    Gallery::Widget widget;
    widget.show();
#endif

    return app.exec();
}
