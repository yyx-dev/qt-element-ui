#include "widget.h"
#include "base.h"
#include "frameless.h"

#include "overview-page.h"
#include "button-page.h"

#include <QMouseEvent>

namespace Gallery
{

    Widget::Widget(QWidget* parent)
        : Element::FramelessWindow(parent)
        , _layout(new QVBoxLayout(this))
        , _appbar(new Element::AppBar(this))
        , _menu(new Element::Menu(this))
        , _stack(new Element::Stack(_menu, this))
    {
        setMinimumSize(Element::sc(1200, 741));
        setMouseTracking(true);

        Element::setBgColor(this, Qt::white);
        setupContainer();
        setupComponents();
    }

    void Widget::setupContainer()
    {
        QHBoxLayout* layout = new QHBoxLayout;
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);
        layout->addWidget(_menu);
        layout->addWidget(_stack);

        _layout->setContentsMargins(0, 0, 0, 0);
        _layout->setSpacing(0);
        _layout->addWidget(_appbar);
        _layout->addLayout(layout);
    }

    void Widget::setupComponents()
    {
        using namespace Element;

        Menu::Item* overview = _menu->addTopItem("Overview 组件总览");
        Menu::Item* basic = _menu->addTopItem("Basic 基础组件");
        Menu::Item* form = _menu->addTopItem("Form 表单组件");
        Menu::Item* data = _menu->addTopItem("Data 数据展示");
        Menu::Item* navigation = _menu->addTopItem("Navigation 导航");
        Menu::Item* feedback = _menu->addTopItem("Feedback 反馈组件");
        Menu::Item* others = _menu->addTopItem("Others 其他");

        Menu::Item* button = _menu->addSubItem(basic, "Button 按钮");
        _menu->addSubItem(basic, "Border 边框");
        _menu->addSubItem(basic, "Color 色彩");
        _menu->addSubItem(basic, "Container 布局容器");
        _menu->addSubItem(basic, "Icon 图标");
        _menu->addSubItem(basic, "Layout 布局");
        _menu->addSubItem(basic, "Link 链接");
        _menu->addSubItem(basic, "Text 文本");
        _menu->addSubItem(basic, "Scrollbar 滚动条");
        _menu->addSubItem(basic, "Space 间距");
        _menu->addSubItem(basic, "Splitter 分隔面板");
        _menu->addSubItem(basic, "Typography 排版");

        _menu->addSubItem(form, "Autocomplete 自动补全输入框");
        _menu->addSubItem(form, "Cascader 级联选择器");
        _menu->addSubItem(form, "Checkbox 多选框");
        _menu->addSubItem(form, "ColorPickerPanel 颜色选择器面板");
        _menu->addSubItem(form, "ColorPicker 颜色选择器");
        _menu->addSubItem(form, "DatePickerPanel 日期选择器面板");
        _menu->addSubItem(form, "DatePicker 日期选择器");
        _menu->addSubItem(form, "DateTimePicker 日期时间选择器");
        _menu->addSubItem(form, "Form 表单组件");
        _menu->addSubItem(form, "Input 输入框");
        _menu->addSubItem(form, "Input Number 数字输入框");
        _menu->addSubItem(form, "Input Tag 标签输入框");
        _menu->addSubItem(form, "Mention 提及");
        _menu->addSubItem(form, "Radio 单选框");
        _menu->addSubItem(form, "Rate 评分");
        _menu->addSubItem(form, "Select 选择器");
        _menu->addSubItem(form, "VirtualizedSelect 虚拟化选择器");
        _menu->addSubItem(form, "Slider 滑块");
        _menu->addSubItem(form, "Switch 开关");
        _menu->addSubItem(form, "TimePicker 时间选择器");
        _menu->addSubItem(form, "TimeSelect 时间选择");
        _menu->addSubItem(form, "Transfer 穿梭框");
        _menu->addSubItem(form, "TreeSelect 树形选择");
        _menu->addSubItem(form, "Upload 上传器");

        _menu->addSubItem(data, "Avatar 头像");
        _menu->addSubItem(data, "Badge 徽章");
        _menu->addSubItem(data, "Calendar 日历");
        _menu->addSubItem(data, "Card 卡片");
        _menu->addSubItem(data, "Carousel 走马灯");
        _menu->addSubItem(data, "Collapse 折叠面板");
        _menu->addSubItem(data, "Descriptions 描述列表");
        _menu->addSubItem(data, "Empty 空状态");
        _menu->addSubItem(data, "Image 图片");
        _menu->addSubItem(data, "Infinite Scroll 无限滚动");
        _menu->addSubItem(data, "Pagination 分页");
        _menu->addSubItem(data, "Progress 进度条");
        _menu->addSubItem(data, "Result 结果");
        _menu->addSubItem(data, "Skeleton 骨架屏");
        _menu->addSubItem(data, "Table 表格");
        _menu->addSubItem(data, "Virtualized Table 虚拟化表格");
        _menu->addSubItem(data, "Tag 标签");
        _menu->addSubItem(data, "Timeline 时间线");
        _menu->addSubItem(data, "Tour 漫游式引导");
        _menu->addSubItem(data, "Tree 树形控件");
        _menu->addSubItem(data, "Virtualized Tree 虚拟化树形控件");
        _menu->addSubItem(data, "Statistic 统计组件");
        _menu->addSubItem(data, "Segmented 分段控制器");

        _menu->addSubItem(navigation, "Affix 固钉");
        _menu->addSubItem(navigation, "Anchor 锚点");
        _menu->addSubItem(navigation, "Backtop 回到顶部");
        _menu->addSubItem(navigation, "Breadcrumb 面包屑");
        _menu->addSubItem(navigation, "Dropdown 下拉菜单");
        _menu->addSubItem(navigation, "Menu 菜单");
        _menu->addSubItem(navigation, "Page Header 页头");
        _menu->addSubItem(navigation, "Steps 步骤条");
        _menu->addSubItem(navigation, "Tabs 标签页");

        _menu->addSubItem(feedback, "Alert 提示");
        _menu->addSubItem(feedback, "Dialog 对话框");
        _menu->addSubItem(feedback, "Drawer 抽屉");
        _menu->addSubItem(feedback, "Loading 加载");
        _menu->addSubItem(feedback, "Message 消息提示");
        _menu->addSubItem(feedback, "MessageBox 消息弹出框");
        _menu->addSubItem(feedback, "Notification 通知");
        _menu->addSubItem(feedback, "Popconfirm 气泡确认框");
        _menu->addSubItem(feedback, "Popover 弹出框");
        _menu->addSubItem(feedback, "Tooltip 文字提示");

        _menu->addSubItem(others, "Divider 分割线");
        _menu->addSubItem(others, "Watermark 水印");

        _stack->addWidget(overview, new OverviewPage(this));
        _stack->addWidget(button, new ButtonPage(this));

    }

}
