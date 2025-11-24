#include "overview-page.h"
#include "text.h"
#include "inputline.h"

namespace Element
{
    OverviewPage::OverviewPage(QWidget* parent)
        : QWidget(parent)
        , _layout(new Layout(this))
    {
        setupWidget();
    }

    void OverviewPage::setupWidget()
    {
        Text* text1 = h1("Overview 组件总览", this);
        Text* text2 = p("以下是 Element Plus 提供的所有组件。", this);
        InputLine* line = new InputLine(this);
        Text* text3 = h3("Basic 基础组件", this);

        _layout->addWidget(text1);
        _layout->addWidget(text2);
        _layout->addWidget(line);
        _layout->addWidget(text3);
    }

}