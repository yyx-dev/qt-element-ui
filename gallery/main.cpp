#include "app.h"

// #define EXAMPLE

#ifdef EXAMPLE
#include "mainwindow.h"
#else
#include "container.h"
#endif

void configurator(Element::Menu* menu, Element::Stack* stack);

int main(int argc, char* argv[])
{
    Element::App app(argc, argv);

#ifdef EXAMPLE
    MainWindow window;
    window.show();
#else

    Element::Container* container = Element::ContainerBuilder()
        .addAppBar()
        .addMenu()
        .addStack()
        .addFooter(nullptr)
        .addConfigurator(configurator)
        .build();

    container->show();

#endif

    return app.exec();
}


#include "overview-page.h"
#include "button-page.h"

void configurator(Element::Menu* menu, Element::Stack* stack)
{
    using namespace Element;
    using namespace Gallery;

    Menu::Item* overview = menu->addTopItem("Overview 组件总览");
    Menu::Item* basic = menu->addTopItem("Basic 基础组件");
    Menu::Item* form = menu->addTopItem("Form 表单组件");
    Menu::Item* data = menu->addTopItem("Data 数据展示");
    Menu::Item* navigation = menu->addTopItem("Navigation 导航");
    Menu::Item* feedback = menu->addTopItem("Feedback 反馈组件");
    Menu::Item* others = menu->addTopItem("Others 其他");

    Menu::Item* button = menu->addSubItem(basic, "Button 按钮");
    menu->addSubItem(basic, "Border 边框");
    menu->addSubItem(basic, "Color 色彩");
    menu->addSubItem(basic, "Container 布局容器");
    menu->addSubItem(basic, "Icon 图标");
    menu->addSubItem(basic, "Layout 布局");
    menu->addSubItem(basic, "Link 链接");
    menu->addSubItem(basic, "Text 文本");
    menu->addSubItem(basic, "Scrollbar 滚动条");
    menu->addSubItem(basic, "Space 间距");
    menu->addSubItem(basic, "Splitter 分隔面板");
    menu->addSubItem(basic, "Typography 排版");

    menu->addSubItem(form, "Autocomplete 自动补全输入框");
    menu->addSubItem(form, "Cascader 级联选择器");
    menu->addSubItem(form, "Checkbox 多选框");
    menu->addSubItem(form, "ColorPickerPanel 颜色选择器面板");
    menu->addSubItem(form, "ColorPicker 颜色选择器");
    menu->addSubItem(form, "DatePickerPanel 日期选择器面板");
    menu->addSubItem(form, "DatePicker 日期选择器");
    menu->addSubItem(form, "DateTimePicker 日期时间选择器");
    menu->addSubItem(form, "Form 表单组件");
    menu->addSubItem(form, "Input 输入框");
    menu->addSubItem(form, "Input Number 数字输入框");
    menu->addSubItem(form, "Input Tag 标签输入框");
    menu->addSubItem(form, "Mention 提及");
    menu->addSubItem(form, "Radio 单选框");
    menu->addSubItem(form, "Rate 评分");
    menu->addSubItem(form, "Select 选择器");
    menu->addSubItem(form, "VirtualizedSelect 虚拟化选择器");
    menu->addSubItem(form, "Slider 滑块");
    menu->addSubItem(form, "Switch 开关");
    menu->addSubItem(form, "TimePicker 时间选择器");
    menu->addSubItem(form, "TimeSelect 时间选择");
    menu->addSubItem(form, "Transfer 穿梭框");
    menu->addSubItem(form, "TreeSelect 树形选择");
    menu->addSubItem(form, "Upload 上传器");

    menu->addSubItem(data, "Avatar 头像");
    menu->addSubItem(data, "Badge 徽章");
    menu->addSubItem(data, "Calendar 日历");
    menu->addSubItem(data, "Card 卡片");
    menu->addSubItem(data, "Carousel 走马灯");
    menu->addSubItem(data, "Collapse 折叠面板");
    menu->addSubItem(data, "Descriptions 描述列表");
    menu->addSubItem(data, "Empty 空状态");
    menu->addSubItem(data, "Image 图片");
    menu->addSubItem(data, "Infinite Scroll 无限滚动");
    menu->addSubItem(data, "Pagination 分页");
    menu->addSubItem(data, "Progress 进度条");
    menu->addSubItem(data, "Result 结果");
    menu->addSubItem(data, "Skeleton 骨架屏");
    menu->addSubItem(data, "Table 表格");
    menu->addSubItem(data, "Virtualized Table 虚拟化表格");
    menu->addSubItem(data, "Tag 标签");
    menu->addSubItem(data, "Timeline 时间线");
    menu->addSubItem(data, "Tour 漫游式引导");
    menu->addSubItem(data, "Tree 树形控件");
    menu->addSubItem(data, "Virtualized Tree 虚拟化树形控件");
    menu->addSubItem(data, "Statistic 统计组件");
    menu->addSubItem(data, "Segmented 分段控制器");

    menu->addSubItem(navigation, "Affix 固钉");
    menu->addSubItem(navigation, "Anchor 锚点");
    menu->addSubItem(navigation, "Backtop 回到顶部");
    menu->addSubItem(navigation, "Breadcrumb 面包屑");
    menu->addSubItem(navigation, "Dropdown 下拉菜单");
    menu->addSubItem(navigation, "Menu 菜单");
    menu->addSubItem(navigation, "Page Header 页头");
    menu->addSubItem(navigation, "Steps 步骤条");
    menu->addSubItem(navigation, "Tabs 标签页");

    menu->addSubItem(feedback, "Alert 提示");
    menu->addSubItem(feedback, "Dialog 对话框");
    menu->addSubItem(feedback, "Drawer 抽屉");
    menu->addSubItem(feedback, "Loading 加载");
    menu->addSubItem(feedback, "Message 消息提示");
    menu->addSubItem(feedback, "MessageBox 消息弹出框");
    menu->addSubItem(feedback, "Notification 通知");
    menu->addSubItem(feedback, "Popconfirm 气泡确认框");
    menu->addSubItem(feedback, "Popover 弹出框");
    menu->addSubItem(feedback, "Tooltip 文字提示");

    menu->addSubItem(others, "Divider 分割线");
    menu->addSubItem(others, "Watermark 水印");

    stack->addWidget(overview, new OverviewPage);
    stack->addWidget(button, new ButtonPage);
}