#include "app.h"
#include "window.h"
#include "widget.h"

int main(int argc, char* argv[])
{
    Element::App app(argc, argv);

    Element::Window w;
    w.setWidget(new Example::Widget(&w));
    w.show();

    return app.exec();
}
