#include "overview-page.h"

#include "card.h"
#include "image.h"
#include "inputline.h"
#include "text.h"

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
        auto createCard = [&](const QString& header, const QString& image) {
            auto card = new Card(this);
            card->setHeader(header);
            card->setBody(new QSvgWidget(image));
            return card;
        };

        auto text1 = h1("Overview 组件总览", this);
        auto text2 = p("以下是 Element Plus 提供的所有组件。", this);
        auto input = new InputLine(this);
        auto text3 = h3("Basic 基础组件", this);
        auto text4 = h3("Form 表单组件", this);
        auto text5 = h3("Data 数据展示", this);
        auto text6 = h3("Navigation 导航", this);
        auto text7 = h3("Feedback 反馈组件", this);
        auto text8 = h3("Others 其他", this);

        auto card01 = createCard("Button 按钮", ":/images/button.svg");
        auto card02 = createCard("Border 边框", ":/images/border.svg");
        auto card03 = createCard("Color 颜色", ":/images/color.svg");
        auto card04 = createCard("Container 布局容器", ":/images/container.svg");
        auto card05 = createCard("Icon 图标", ":/images/icon.svg");
        auto card06 = createCard("Layout 布局", ":/images/layout.svg");
        auto card07 = createCard("Link 链接", ":/images/link.svg");
        auto card08 = createCard("Text 文本", ":/images/text.svg");
        auto card09 = createCard("Scrollbar 滚动条", ":/images/scrollbar.svg");
        auto card10 = createCard("Space 间距", ":/images/space.svg");
        auto card11 = createCard("Splitter 分隔面板", ":/images/splitter.svg");
        auto card12 = createCard("Typography 排版", ":/images/typography.svg");
        auto card13 = createCard("Autocomplete 自动补全输入框", ":/images/autocomplete.svg");
        auto card14 = createCard("Cascader 级联选择器", ":/images/cascader.svg");
        auto card15 = createCard("Checkbox 多选框", ":/images/checkbox.svg");
        auto card16 = createCard("ColorPickerPanel 颜色选择器面板", ":/images/color-picker-panel.svg");
        auto card17 = createCard("ColorPicker 颜色选择器", ":/images/color-picker.svg");
        auto card18 = createCard("DatePickerPanel 日期选择器面板", ":/images/date-picker-panel.svg");
        auto card19 = createCard("DatePicker 日期选择器", ":/images/date-picker.svg");
        auto card20 = createCard("DateTimePicker 日期时间选择器", ":/images/datetime-picker.svg");
        auto card21 = createCard("Form 表单", ":/images/form.svg");
        auto card22 = createCard("Input 输入框", ":/images/input.svg");
        auto card23 = createCard("Input Number 数字输入框", ":/images/input-number.svg");
        auto card24 = createCard("InputTag 标签输入框", ":/images/input-tag.svg");
        auto card25 = createCard("Mention 提及", ":/images/mention.svg");
        auto card26 = createCard("Radio 单选框", ":/images/radio.svg");
        auto card27 = createCard("Rate 评分", ":/images/rate.svg");
        auto card28 = createCard("Select 选择器", ":/images/select.svg");
        auto card29 = createCard("Slider 滑块", ":/images/slider.svg");
        auto card30 = createCard("Switch 开关", ":/images/switch.svg");
        auto card31 = createCard("TimePicker 时间选择器", ":/images/time-picker.svg");
        auto card32 = createCard("TimeSelect 时间选择", ":/images/time-select.svg");
        auto card33 = createCard("Transfer 穿梭框", ":/images/transfer.svg");
        auto card34 = createCard("TreeSelect 树形选择", ":/images/tree-select.svg");
        auto card35 = createCard("Upload 上传", ":/images/upload.svg");
        auto card36 = createCard("Avatar 头像", ":/images/avatar.svg");
        auto card37 = createCard("Badge 徽章", ":/images/badge.svg");
        auto card38 = createCard("Calendar 日历", ":/images/calendar.svg");
        auto card39 = createCard("Card 卡片", ":/images/card.svg");
        auto card40 = createCard("Carousel 走马灯", ":/images/carousel.svg");
        auto card41 = createCard("Collapse 折叠面板", ":/images/collapse.svg");
        auto card42 = createCard("Descriptions 描述列表", ":/images/descriptions.svg");
        auto card43 = createCard("Empty 空状态", ":/images/empty.svg");
        auto card44 = createCard("Image 图片", ":/images/image.svg");
        auto card45 = createCard("Infinite Scroll 无限滚动", ":/images/infinite-scroll.svg");
        auto card46 = createCard("Pagination 分页", ":/images/pagination.svg");
        auto card47 = createCard("Progress 进度条", ":/images/progress.svg");
        auto card48 = createCard("Result 结果", ":/images/result.svg");
        auto card49 = createCard("Skeleton 骨架屏", ":/images/skeleton.svg");
        auto card50 = createCard("Table 表格", ":/images/table.svg");
        auto card51 = createCard("Tag 标签", ":/images/tag.svg");
        auto card52 = createCard("Timeline 时间线", ":/images/timeline.svg");
        auto card53 = createCard("Tour 漫游式引导", ":/images/tour.svg");
        auto card54 = createCard("Tree 树形控件", ":/images/tree.svg");
        auto card55 = createCard("Statistic 统计组件", ":/images/statistic.svg");
        auto card56 = createCard("Segmented 分段控制器", ":/images/segmented.svg");
        auto card57 = createCard("Affix 固钉", ":/images/affix.svg");
        auto card58 = createCard("Anchor 锚点", ":/images/anchor.svg");
        auto card59 = createCard("Backtop 回到顶部", ":/images/backtop.svg");
        auto card60 = createCard("Breadcrumb 面包屑", ":/images/breadcrumb.svg");
        auto card61 = createCard("Dropdown 下拉菜单", ":/images/dropdown.svg");
        auto card62 = createCard("Menu 菜单", ":/images/menu.svg");
        auto card63 = createCard("Page Header 页头", ":/images/page-header.svg");
        auto card64 = createCard("Steps 步骤条", ":/images/steps.svg");
        auto card65 = createCard("Tabs 标签页", ":/images/tabs.svg");
        auto card66 = createCard("Alert 提示", ":/images/alert.svg");
        auto card67 = createCard("Dialog 对话框", ":/images/dialog.svg");
        auto card68 = createCard("Drawer 抽屉", ":/images/drawer.svg");
        auto card69 = createCard("Loading 加载", ":/images/loading.svg");
        auto card70 = createCard("Message 消息提示", ":/images/message.svg");
        auto card71 = createCard("MessageBox 消息弹框", ":/images/message-box.svg");
        auto card72 = createCard("Notification 通知", ":/images/notification.svg");
        auto card73 = createCard("Popconfirm 气泡确认框", ":/images/popconfirm.svg");
        auto card74 = createCard("Popover 弹出框", ":/images/popover.svg");
        auto card75 = createCard("Tooltip 文字提示", ":/images/tooltip.svg");
        auto card76 = createCard("Divider 分割线", ":/images/divider.svg");
        auto card77 = createCard("Watermark 水印", ":/images/watermark.svg");

        _layout->addWidget(text1);
        _layout->addWidget(text2);
        _layout->addWidget(input);

        _layout->addWidget(text3);
        _layout->addWidgets({
            card01, card02, card03, card04, card05, card06, card07, card08, card09, card10, card11, card12
        });

        _layout->addWidget(text4);
        _layout->addWidgets({
            card13, card14, card15, card16, card17, card18, card19, card20, card21, card22, card23, card24,
            card25, card26, card27, card28, card29, card30, card31, card32, card33, card34, card35,
        });

        _layout->addWidget(text5);
        _layout->addWidgets({
            card36, card37, card38, card39, card40, card41, card42, card43, card44, card45, card46, card47,
            card48, card49, card50, card51, card52, card53, card54, card55, card56,
        });

        _layout->addWidget(text6);
        _layout->addWidgets({ card57, card58, card59, card60, card61, card62, card63, card64, card65, });

        _layout->addWidget(text7);
        _layout->addWidgets({ card66, card67, card68, card69, card70, card71, card72, card73, card74, card75, });

        _layout->addWidget(text8);
        _layout->addWidgets({ card76, card77, });
    }

}
