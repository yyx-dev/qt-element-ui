#pragma once

#include "icon.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
        void setWindowIcon(Element::Icon::Name icon);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupWindow();
    void setupTabs();
    void setupTab0();
    void setupTab1();
    void setupTab2();
    void setupTab3();
    void setupTab4();
    void setupTab5();
    void setupTab6();
    void setupTab7();
    void setupTab8();
    void setupTab9();
    void setupTab10();

private:
    Ui::MainWindow *ui;
};
