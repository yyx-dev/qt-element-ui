#include "button-page.h"

namespace Gallery
{
    ButtonPage::ButtonPage(QWidget* parent)
        : QWidget(parent)
        , _layout(new Layout(this))
    {
        setupWidget();
    }

    void ButtonPage::setupWidget()
    {

    }
}