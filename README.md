# qt-element-ui

## 介绍

`qt-element-ui` 是一个基于 Qt 框架的 UI 组件库，旨在为开发者提供一套美观、易用的界面组件。灵感来源于 [Element Plus](https://element-plus.org)，该项目为 Qt 开发者提供了类似风格和功能的组件，适用于桌面应用程序开发。

该项目包含以下核心组件：

- **按钮（Button）**
- **容器（Container）**
- **滚动条（ScrollBar）**
- **文本（Text）**
- **图标管理器（IconManager）**
- **字体管理器（FontManager）**
- **样式表辅助类（QSSHelper）**

此外，项目还集成了丰富的 SVG 图标资源，便于开发者快速构建现代风格的用户界面。

## 软件架构

项目采用模块化设计，主要分为以下几个部分：

- **components/**：包含所有 UI 组件的实现，如按钮、容器、滚动条等。
- **tools/**：提供辅助工具类，如字体管理、图标管理、日志记录、QSS 样式处理等。
- **resources/icons/**：SVG 图标资源目录。
- **resources/fonts/**：字体资源目录。
- **example/**：示例程序，展示如何使用组件库。

## 安装教程

### 依赖项

- Qt 5 或 Qt 6（支持 QWidget 模块）
- CMake（可选，用于构建）

### 构建与安装

1. 克隆仓库：

```bash
git clone https://gitee.com/yyx_dev/qt-element-ui.git
cd qt-element-ui
```

2. 构建项目：

```bash
qmake qt-element-ui.pro
make
```

3. 安装库文件（可选）：

```bash
sudo make install
```

## 使用说明

### 示例程序

项目包含一个示例程序 `example/mainwindow.cpp`，演示了如何使用组件库中的组件。你可以通过以下命令运行示例：

```bash
cd example
qmake
make
./example
```

### 使用组件

在你的 Qt 项目中，包含相应的头文件并使用组件：

```cpp
#include <QApplication>
#include <QTElementUI/Button>
#include <QTElementUI/Text>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    QVBoxLayout *layout = new QVBoxLayout(&window);

    QTElementUI::Button *button = new QTElementUI::Button("点击我");
    QTElementUI::Text *text = new QTElementUI::Text();
    text->setText("这是一个文本组件");

    layout->addWidget(button);
    layout->addWidget(text);

    window.setLayout(layout);
    window.show();

    return app.exec();
}
```

## 参与贡献

欢迎贡献代码、文档或提出建议。请参考 [CONTRIBUTING.md](CONTRIBUTING.md) 获取更多信息。

## 特技

- 支持 SVG 图标资源管理
- 提供统一的字体管理机制
- 使用 QSS 样式辅助类简化样式设置
- 支持多种组件样式定制
- 提供丰富的调试日志功能

## 许可证

本项目采用 [MIT License](LICENSE)，详情请参阅 LICENSE 文件。