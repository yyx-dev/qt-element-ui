#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "text.h"
#include "button.h"
#include "iconmanager.h"

#include <QDebug>

#define TEXT 0
#define BUTTON 1
#define SCROLLBAR 2
#define CONTAINER 3
#define LINK 4
#define INPUT 5
#define NUMBER 6
#define TAG 7

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

    setupTab0();
    setupTab1();
    setupTab2();
    setupTab3();
    setupTab4();
    setupTab5();
    setupTab6();
    setupTab7();

    ui->tabWidget->setCurrentIndex(INPUT);
}


void MainWindow::setupTab0()
{
    ui->defaultText->setType(Text::Type::default_);
    ui->primaryText->setType(Text::Type::primary);
    ui->successText->setType(Text::Type::success);
    ui->infoText->setType(Text::Type::info);
    ui->warningText->setType(Text::Type::warning);
    ui->dangerText->setType(Text::Type::danger);

    ui->defaultText->setSize(Text::Size::large);
}

void MainWindow::setupTab1()
{
    ui->button_1->setStyle(Button::Style::default_).setType(Button::Type::default_).setDisabled(false);
    ui->button_2->setStyle(Button::Style::default_).setType(Button::Type::primary).setDisabled(false);
    ui->button_3->setStyle(Button::Style::default_).setType(Button::Type::success);
    ui->button_4->setStyle(Button::Style::default_).setType(Button::Type::info);
    ui->button_5->setStyle(Button::Style::default_).setType(Button::Type::warning);
    ui->button_6->setStyle(Button::Style::default_).setType(Button::Type::danger);

    ui->button_7 ->setStyle(Button::Style::plain).setType(Button::Type::default_).setDisabled(false);
    ui->button_8 ->setStyle(Button::Style::plain).setType(Button::Type::primary).setDisabled(false);
    ui->button_9 ->setStyle(Button::Style::plain).setType(Button::Type::success);
    ui->button_10->setStyle(Button::Style::plain).setType(Button::Type::info);
    ui->button_11->setStyle(Button::Style::plain).setType(Button::Type::warning);
    ui->button_12->setStyle(Button::Style::plain).setType(Button::Type::danger);

    ui->button_13->setStyle(Button::Style::round).setType(Button::Type::default_).setDisabled(true);
    ui->button_14->setStyle(Button::Style::round).setType(Button::Type::primary).setDisabled(true);
    ui->button_15->setStyle(Button::Style::round).setType(Button::Type::success);
    ui->button_16->setStyle(Button::Style::round).setType(Button::Type::info);
    ui->button_17->setStyle(Button::Style::round).setType(Button::Type::warning);
    ui->button_18->setStyle(Button::Style::round).setType(Button::Type::danger);

    ui->button_19->setStyle(Button::Style::circle).setType(Button::Type::default_).setIcon(Icon::Search);
    ui->button_20->setStyle(Button::Style::circle).setType(Button::Type::primary).setIcon(Icon::Edit);
    ui->button_21->setStyle(Button::Style::circle).setType(Button::Type::success).setIcon(Icon::Check);
    ui->button_22->setStyle(Button::Style::circle).setType(Button::Type::info).setIcon(Icon::Message);
    ui->button_23->setStyle(Button::Style::circle).setType(Button::Type::warning).setIcon(Icon::Star);
    ui->button_24->setStyle(Button::Style::circle).setType(Button::Type::danger).setIcon(Icon::Delete);

    ui->button_25->setType(Button::Type::primary).setIcon(Icon::Edit, Button::IconPosition::only);
    ui->button_26->setType(Button::Type::primary).setIcon(Icon::Share, Button::IconPosition::only);
    ui->button_27->setType(Button::Type::primary).setIcon(Icon::Delete, Button::IconPosition::only);

    ui->button_28->setType(Button::Type::primary).setText("Search").setIcon(Icon::Search, Button::IconPosition::left);
    ui->button_29->setType(Button::Type::primary).setText("Upload").setIcon(Icon::Upload, Button::IconPosition::right);

    ui->button_30->setStyle(Button::Style::link).setType(Button::Type::default_);
    ui->button_31->setStyle(Button::Style::link).setType(Button::Type::primary);
    ui->button_32->setStyle(Button::Style::link).setType(Button::Type::success);
    ui->button_33->setStyle(Button::Style::link).setType(Button::Type::info);
    ui->button_34->setStyle(Button::Style::link).setType(Button::Type::warning);
    ui->button_35->setStyle(Button::Style::link).setType(Button::Type::danger);

    ui->button_36->setStyle(Button::Style::text).setType(Button::Type::default_);
    ui->button_37->setStyle(Button::Style::text).setType(Button::Type::primary);
    ui->button_38->setStyle(Button::Style::text).setType(Button::Type::success);
    ui->button_39->setStyle(Button::Style::text).setType(Button::Type::info);
    ui->button_40->setStyle(Button::Style::text).setType(Button::Type::warning);
    ui->button_41->setStyle(Button::Style::text).setType(Button::Type::danger);
}

void MainWindow::setupTab2()
{
    QVBoxLayout *contentLayout = new QVBoxLayout(ui->scrollAreaWidgetContents);
    ui->scrollAreaWidgetContents->setBackgroundRole(QPalette::Light);

    for(int i = 0; i < 50; i++) {
        QPushButton *button = new QPushButton(QString("按钮 %1").arg(i), ui->scrollAreaWidgetContents);
        button->setMinimumSize(500, 50);
        contentLayout->addWidget(button);
    }
}

void MainWindow::setupTab3()
{

}

void MainWindow::setupTab4()
{
    ui->link_1 ->setType(Link::Type::default_);
    ui->link_2 ->setType(Link::Type::primary);
    ui->link_3 ->setType(Link::Type::success);
    ui->link_4 ->setType(Link::Type::warning);
    ui->link_5 ->setType(Link::Type::danger);
    ui->link_6 ->setType(Link::Type::info);
    ui->link_7 ->setType(Link::Type::default_).setDisabled(true);
    ui->link_8 ->setType(Link::Type::primary).setDisabled(true);
    ui->link_9 ->setType(Link::Type::success).setDisabled(true);
    ui->link_10->setType(Link::Type::warning).setDisabled(true);
    ui->link_11->setType(Link::Type::danger).setDisabled(true);
    ui->link_12->setType(Link::Type::info).setDisabled(true);
    ui->link_13->setUnderline(Link::Underline::default_);
    ui->link_14->setUnderline(Link::Underline::always);
    ui->link_15->setUnderline(Link::Underline::hover);
    ui->link_16->setUnderline(Link::Underline::never);
}

void MainWindow::setupTab5()
{
    ui->input_1->setClearable(true);
    ui->input_2->setDisabled(true);
    ui->input_3->setPrefixIcon(Icon::Star);
    ui->input_4->setSuffixIcon(Icon::Unlock);
    ui->input_5->setShowPassword(true);
    ui->input_6->setSize(Input::Size::large);
    ui->input_7->setSize(Input::Size::small);
    ui->input_8->setMaxLength(30);
    ui->input_9->setReadOnly(true);
}

void MainWindow::setupTab6()
{

}

void MainWindow::setupTab7()
{

}

MainWindow::~MainWindow()
{
    delete ui;
}

