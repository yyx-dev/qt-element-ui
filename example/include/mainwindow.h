#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setupTab1();
    void setupTab2();
    void setupTab3();
    void setupTab4();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
