#include "../include/mainwindow.h"
#include "ui_mainwindow.h"

#include "../../components/include/text.h"
#include "../../components/include/button.h"
#include "../../tools/include/iconmanager.h"

#include <QDebug>


using namespace QTElementUI;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::white);
    this->setPalette(palette);
    this->setAutoFillBackground(true);

    setupTab1();
    setupTab2();
    setupTab3();
    setupTab4();

    ui->tabWidget->setCurrentIndex(3);
}


void MainWindow::setupTab1()
{
    ui->defaultText->setType(Text::Type::default_);
    ui->primaryText->setType(Text::Type::primary);
    ui->successText->setType(Text::Type::success);
    ui->infoText->setType(Text::Type::info);
    ui->warningText->setType(Text::Type::warning);
    ui->dangerText->setType(Text::Type::danger);

    ui->defaultText->setSize(Text::Size::large);
}

void MainWindow::setupTab2()
{
    ui->pushButton_1->setStyle(Button::Style::default_).setType(Button::Type::default_).setDisabled(false);
    ui->pushButton_2->setStyle(Button::Style::default_).setType(Button::Type::primary).setDisabled(false);
    ui->pushButton_3->setStyle(Button::Style::default_).setType(Button::Type::success);
    ui->pushButton_4->setStyle(Button::Style::default_).setType(Button::Type::info);
    ui->pushButton_5->setStyle(Button::Style::default_).setType(Button::Type::warning);
    ui->pushButton_6->setStyle(Button::Style::default_).setType(Button::Type::danger);

    ui->pushButton_7 ->setStyle(Button::Style::plain).setType(Button::Type::default_).setDisabled(false);
    ui->pushButton_8 ->setStyle(Button::Style::plain).setType(Button::Type::primary).setDisabled(false);
    ui->pushButton_9 ->setStyle(Button::Style::plain).setType(Button::Type::success);
    ui->pushButton_10->setStyle(Button::Style::plain).setType(Button::Type::info);
    ui->pushButton_11->setStyle(Button::Style::plain).setType(Button::Type::warning);
    ui->pushButton_12->setStyle(Button::Style::plain).setType(Button::Type::danger);

    ui->pushButton_13->setStyle(Button::Style::round).setType(Button::Type::default_).setDisabled(true);
    ui->pushButton_14->setStyle(Button::Style::round).setType(Button::Type::primary).setDisabled(true);
    ui->pushButton_15->setStyle(Button::Style::round).setType(Button::Type::success);
    ui->pushButton_16->setStyle(Button::Style::round).setType(Button::Type::info);
    ui->pushButton_17->setStyle(Button::Style::round).setType(Button::Type::warning);
    ui->pushButton_18->setStyle(Button::Style::round).setType(Button::Type::danger);

    ui->pushButton_19->setStyle(Button::Style::circle).setType(Button::Type::default_).setIcon("search");
    ui->pushButton_20->setStyle(Button::Style::circle).setType(Button::Type::primary).setIcon("edit");
    ui->pushButton_21->setStyle(Button::Style::circle).setType(Button::Type::success).setIcon("check");
    ui->pushButton_22->setStyle(Button::Style::circle).setType(Button::Type::info).setIcon("message");
    ui->pushButton_23->setStyle(Button::Style::circle).setType(Button::Type::warning).setIcon("star");
    ui->pushButton_24->setStyle(Button::Style::circle).setType(Button::Type::danger).setIcon("delete");

    ui->pushButton_25->setType(Button::Type::primary).setIcon("edit", Button::IconPosition::only);
    ui->pushButton_26->setType(Button::Type::primary).setIcon("share", Button::IconPosition::only);
    ui->pushButton_27->setType(Button::Type::primary).setIcon("delete", Button::IconPosition::only);

    ui->pushButton_28->setType(Button::Type::primary).setText("Search").setIcon("search", Button::IconPosition::left);
    ui->pushButton_29->setType(Button::Type::primary).setText("Upload").setIcon("upload", Button::IconPosition::right);
}

void MainWindow::setupTab3()
{
    QVBoxLayout *contentLayout = new QVBoxLayout(ui->scrollAreaWidgetContents);
    ui->scrollAreaWidgetContents->setBackgroundRole(QPalette::Light);

    for(int i = 0; i < 50; i++) {
        QPushButton *button = new QPushButton(QString("按钮 %1").arg(i), ui->scrollAreaWidgetContents);
        button->setMinimumSize(500, 50);
        contentLayout->addWidget(button);
    }
}

void MainWindow::setupTab4()
{

}

MainWindow::~MainWindow()
{
    delete ui;
}

