#include "overview-page.h"
#include "text.h"
#include "inputline.h"
#include "card.h"
#include "image.h"
#include <QSvgWidget>

namespace Gallery
{
    OverviewPage::OverviewPage(QWidget* parent)
        : QWidget(parent)
        , _layout(new Layout(this))
    {
        _layout->setSpacing(Layout::SpaceSize::Large);
        setupWidget();
    }

    void OverviewPage::setupWidget()
    {
        auto text1 = h1("Overview 组件总览", this);
        auto text2 = p("以下是 Element Plus 提供的所有组件。", this);
        auto line = new InputLine(this);
        auto text3 = h3("Basic 基础组件", this);


        auto createCard = [&](const QString& header, const QString& image) {
            auto card = new Card(this);
            card->setHeader(header);
            card->setBody(new QSvgWidget(image));
            return card;
        };

        auto buttonCard = createCard("Button 按钮", ":/images/button.svg");
        auto borderCard = createCard("Border 边框", ":/images/border.svg");
        auto colorCard = createCard("Color 颜色", ":/images/color.svg");
        auto containerCard = createCard("Container 布局容器", ":/images/container.svg");
        auto iconCard = createCard("Icon 图标", ":/images/icon.svg");
        auto layoutCard = createCard("Layout 布局", ":/images/layout.svg");
        auto linkCard = createCard("Link 链接", ":/images/link.svg");
        auto textCard = createCard("Text 文本", ":/images/text.svg");
        auto scrollbarCard = createCard("Scrollbar 滚动条", ":/images/scrollbar.svg");
        auto spaceCard = createCard("Space 间距", ":/images/space.svg");
        auto splitterCard = createCard("Splitter 分隔面板", ":/images/splitter.svg");
        auto typographyCard = createCard("Typography 排版", ":/images/typography.svg");

        _layout->addWidget(text1);
        _layout->addWidget(text2);
        _layout->addWidget(line);
        _layout->addWidget(text3);
        _layout->addWidgets<FlowLayout>({
            buttonCard, borderCard, colorCard, containerCard,
            iconCard, layoutCard, linkCard, textCard,
            scrollbarCard, spaceCard, splitterCard, typographyCard
        });

        auto text4 = h3("Form 表单组件", this);
        auto text5 = h3("Data 数据展示", this);
        auto text6 = h3("Navigation 导航", this);
        auto text7 = h3("Feedback 反馈组件", this);
        auto text8 = h3("Others 其他", this);

        _layout->addWidget(text4);
        _layout->addWidget(text5);
        _layout->addWidget(text6);
        _layout->addWidget(text7);
        _layout->addWidget(text8);

    }

}