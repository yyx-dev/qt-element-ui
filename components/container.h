#pragma once

#include "appbar.h"
#include "menu.h"
#include "stack.h"
#include "frameless.h"

#include <QWidget>
#include <QVBoxLayout>

#include <functional>

namespace Element
{

    class Container : public FramelessWindow
    {
        Q_OBJECT
    public:
        AppBar* appBar() { return _appbar; }
        Menu* menu() { return _menu; }
        Stack* stack() { return _stack; }

    public:
        Container(QWidget* parent = nullptr);

    protected:
        QVBoxLayout* _layout = nullptr;
        AppBar* _appbar = nullptr;
        Menu* _menu = nullptr;
        Stack* _stack = nullptr;
    };

    class ContainerBuilder : public QObject
    {
    public:
        using Configurator = std::function<void(Menu*, Stack*)>;

    public:
        ContainerBuilder& addAppBar();
        ContainerBuilder& addMenu();
        ContainerBuilder& addStack();
        ContainerBuilder& addFooter(QWidget* footer);

        ContainerBuilder& addConfigurator(const Configurator& configurator);

        Container* build(QWidget* parent = nullptr);

    public:
        ContainerBuilder();

    private:
        Container* _container = nullptr;
        AppBar* _appbar = nullptr;
        Menu* _menu = nullptr;
        Stack* _stack = nullptr;
        Configurator _configurator = nullptr;
    };
}
