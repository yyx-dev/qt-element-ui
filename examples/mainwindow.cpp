#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "tools/iconmanager.h"
#include "text.h"
#include "button.h"
#include "dialog.h"
#include "message.h"
#include "notification.h"

#include <QDebug>

#define TEXT 0
#define BUTTON 1
#define SCROLLBAR 2
#define LINK 3
#define INPUT 4
#define FEEDBACK 5
#define TAG 6

using namespace Element;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::white);
    this->setPalette(palette);
    this->setAutoFillBackground(true);

    setupTabs();
    setupTab0();
    setupTab1();
    setupTab2();
    setupTab3();
    setupTab4();
    setupTab5();
    setupTab6();

    ui->tabWidget->setCurrentIndex(FEEDBACK);
}

void MainWindow::setupTabs()
{
    ui->tabWidget->setTabIcon(0, Element::Icon::CirclePlus);
    ui->tabWidget->setTabIcon(1, Element::Icon::Open);
    ui->tabWidget->setTabIcon(2, Element::Icon::Operation);
    ui->tabWidget->setTabIcon(3, Element::Icon::Link);
    ui->tabWidget->setTabIcon(4, Element::Icon::EditPen);
    ui->tabWidget->setTabIcon(5, Element::Icon::Connection);
}


void MainWindow::setupTab0()
{
    ui->defaultText->setType(Text::Type::Default).setSize(Text::Size::Large);
    ui->primaryText->setType(Text::Type::Primary).setSize(Text::Size::Default);
    ui->successText->setType(Text::Type::Success);
    ui->infoText->setType(Text::Type::Info);
    ui->warningText->setType(Text::Type::Warning);
    ui->dangerText->setType(Text::Type::Danger);
}

void MainWindow::setupTab1()
{
    ui->button_1->setStyle(Button::Style::Default).setType(Button::Type::Default).setDisabled(false);
    ui->button_2->setStyle(Button::Style::Default).setType(Button::Type::Primary).setDisabled(false);
    ui->button_3->setStyle(Button::Style::Default).setType(Button::Type::Success);
    ui->button_4->setStyle(Button::Style::Default).setType(Button::Type::Info);
    ui->button_5->setStyle(Button::Style::Default).setType(Button::Type::Warning);
    ui->button_6->setStyle(Button::Style::Default).setType(Button::Type::Danger);

    ui->button_7 ->setStyle(Button::Style::Plain).setType(Button::Type::Default).setDisabled(false);
    ui->button_8 ->setStyle(Button::Style::Plain).setType(Button::Type::Primary).setDisabled(false);
    ui->button_9 ->setStyle(Button::Style::Plain).setType(Button::Type::Success);
    ui->button_10->setStyle(Button::Style::Plain).setType(Button::Type::Info);
    ui->button_11->setStyle(Button::Style::Plain).setType(Button::Type::Warning);
    ui->button_12->setStyle(Button::Style::Plain).setType(Button::Type::Danger);

    ui->button_13->setStyle(Button::Style::Round).setType(Button::Type::Default).setDisabled(true);
    ui->button_14->setStyle(Button::Style::Round).setType(Button::Type::Primary).setDisabled(true);
    ui->button_15->setStyle(Button::Style::Round).setType(Button::Type::Success);
    ui->button_16->setStyle(Button::Style::Round).setType(Button::Type::Info);
    ui->button_17->setStyle(Button::Style::Round).setType(Button::Type::Warning);
    ui->button_18->setStyle(Button::Style::Round).setType(Button::Type::Danger);

    ui->button_19->setStyle(Button::Style::Circle).setType(Button::Type::Default).setIcon(Icon::Search);
    ui->button_20->setStyle(Button::Style::Circle).setType(Button::Type::Primary).setIcon(Icon::Edit);
    ui->button_21->setStyle(Button::Style::Circle).setType(Button::Type::Success).setIcon(Icon::Check);
    ui->button_22->setStyle(Button::Style::Circle).setType(Button::Type::Info).setIcon(Icon::Message);
    ui->button_23->setStyle(Button::Style::Circle).setType(Button::Type::Warning).setIcon(Icon::Star);
    ui->button_24->setStyle(Button::Style::Circle).setType(Button::Type::Danger).setIcon(Icon::Delete);

    ui->button_25->setType(Button::Type::Primary).setIcon(Icon::Edit, Button::IconPosition::Only);
    ui->button_26->setType(Button::Type::Primary).setIcon(Icon::Share, Button::IconPosition::Only);
    ui->button_27->setType(Button::Type::Primary).setIcon(Icon::Delete, Button::IconPosition::Only);

    ui->button_28->setType(Button::Type::Primary).setText("Search").setIcon(Icon::Search, Button::IconPosition::Left);
    ui->button_29->setType(Button::Type::Primary).setText("Upload").setIcon(Icon::Upload, Button::IconPosition::Right);

    ui->button_30->setStyle(Button::Style::Link).setType(Button::Type::Default);
    ui->button_31->setStyle(Button::Style::Link).setType(Button::Type::Primary);
    ui->button_32->setStyle(Button::Style::Link).setType(Button::Type::Success);
    ui->button_33->setStyle(Button::Style::Link).setType(Button::Type::Info);
    ui->button_34->setStyle(Button::Style::Link).setType(Button::Type::Warning);
    ui->button_35->setStyle(Button::Style::Link).setType(Button::Type::Danger);

    ui->button_36->setStyle(Button::Style::Text).setType(Button::Type::Default);
    ui->button_37->setStyle(Button::Style::Text).setType(Button::Type::Primary);
    ui->button_38->setStyle(Button::Style::Text).setType(Button::Type::Success);
    ui->button_39->setStyle(Button::Style::Text).setType(Button::Type::Info);
    ui->button_40->setStyle(Button::Style::Text).setType(Button::Type::Warning);
    ui->button_41->setStyle(Button::Style::Text).setType(Button::Type::Danger);
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
    ui->link_1 ->setType(Link::Type::Default);
    ui->link_2 ->setType(Link::Type::Primary);
    ui->link_3 ->setType(Link::Type::Success);
    ui->link_4 ->setType(Link::Type::warning);
    ui->link_5 ->setType(Link::Type::Danger);
    ui->link_6 ->setType(Link::Type::info);
    ui->link_7 ->setType(Link::Type::Default).setDisabled(true);
    ui->link_8 ->setType(Link::Type::Primary).setDisabled(true);
    ui->link_9 ->setType(Link::Type::Success).setDisabled(true);
    ui->link_10->setType(Link::Type::warning).setDisabled(true);
    ui->link_11->setType(Link::Type::Danger).setDisabled(true);
    ui->link_12->setType(Link::Type::info).setDisabled(true);
    ui->link_13->setUnderline(Link::Underline::Default);
    ui->link_14->setUnderline(Link::Underline::Always);
    ui->link_15->setUnderline(Link::Underline::Hover);
    ui->link_16->setUnderline(Link::Underline::Never);
}

void MainWindow::setupTab4()
{
    ui->input_01->setClearable(true);
    ui->input_02->setDisabled(true);
    ui->input_03->setPrefixIcon(Icon::Star);
    ui->input_04->setSuffixIcon(Icon::Unlock);
    ui->input_05->setShowPassword(true);
    ui->input_06->setSize(InputLine::Size::Large);
    ui->input_07->setSize(InputLine::Size::Small);
    ui->input_08->setMaxLength(30);
    ui->input_09->setReadOnly(true);
    ui->input_10->setAutoFocus();
    ui->input_11->getWidth();
    ui->input_12->setResize(true);
    ui->input_13->setAutoSize(true);
    ui->input_14->setAutoSize(2, 5);

    ui->spinBox_1->setSize(InputNumber::Size::Large);
    ui->spinBox_2->setSize(InputNumber::Size::Default);
    ui->spinBox_3->setSize(InputNumber::Size::Small);
    ui->spinBox_4->setDisabled(true);
}

void MainWindow::setupTab5()
{
    connect(ui->button_42, &Element::Button::clicked, this, [&]() {
        Dialog* dialog = new Dialog("Tips", "this is a message dialog", this);
        dialog->show();
    });
    connect(ui->button_43, &Element::Button::clicked, this, [&]() {
        Message* message = new Message("This is a message.", " VNode", this);
        message->setType(Message::Type::Info);
        message->show();
    });
    connect(ui->button_44, &Element::Button::clicked, this, [&]() {
        Message* message = new Message("This is a message on top left.", this);
        message->setPlacement(Message::Place::TopLeft);
        message->show();
    });
    connect(ui->button_45, &Element::Button::clicked, this, [&]() {
        Message* message = new Message("This is a message on top right.", this);
        message->setPlacement(Message::Place::TopRight);
        message->show();
    });
    connect(ui->button_46, &Element::Button::clicked, this, [&]() {
        Message* message = new Message("This is a message on bottom.", this);
        message->setPlacement(Message::Place::Bottom);
        message->show();
    });
    connect(ui->button_47, &Element::Button::clicked, this, [&]() {
        Message* message = new Message("This is a message on bottom left.", this);
        message->setPlacement(Message::Place::BottomLeft);
        message->show();
    });
    connect(ui->button_48, &Element::Button::clicked, this, [&]() {
        Message* message = new Message("This is a message on bottom right.", this);
        message->setPlacement(Message::Place::BottomRight);
        message->show();
    });
    connect(ui->button_49, &Element::Button::clicked, this, [&]() {
        Message* message = new Message("This is a primary message.", Message::Type::Primary, this);
        message->show();
    });
    connect(ui->button_50, &Element::Button::clicked, this, [&]() {
        Message* message = new Message("This is a success message.", Message::Type::Success, this);
        message->show();
    });
    connect(ui->button_51, &Element::Button::clicked, this, [&]() {
        Message* message = new Message("This is a warning message.", Message::Type::Warning, this);
        message->show();
    });
    connect(ui->button_52, &Element::Button::clicked, this, [&]() {
        Message* message = new Message("This is a info message.", Message::Type::Info, this);
        message->show();
    });
    connect(ui->button_53, &Element::Button::clicked, this, [&]() {
        Message* message = new Message("This is a error message.", Message::Type::Error, this);
        message->show();
    });
    connect(ui->button_54, &Element::Button::clicked, this, [&]() {
        Notification* noti = new Notification("Title", "This is a reminder.", this);
        noti->show();
    });
    connect(ui->button_55, &Element::Button::clicked, this, [&]() {
        Notification* noti = new Notification("Title", "This is a reminder on top left.", this);
        noti->setPosition(Notification::Position::TopLeft);
        noti->show();
    });
    connect(ui->button_56, &Element::Button::clicked, this, [&]() {
        Notification* noti = new Notification("Title", "This is a reminder on bottom right.", this);
        noti->setPosition(Notification::Position::BottomLeft);
        noti->show();
    });
    connect(ui->button_57, &Element::Button::clicked, this, [&]() {
        Notification* noti = new Notification("Title", "This is a reminder on bottom right.", this);
        noti->setPosition(Notification::Position::BottomRight);
        noti->show();
    });
    connect(ui->button_58, &Element::Button::clicked, this, [&]() {
        Notification* noti = new Notification("Title", "This is a primary reminder.", Notification::Type::Primary, this);
        noti->show();
    });
    connect(ui->button_59, &Element::Button::clicked, this, [&]() {
        Notification* noti = new Notification("Title", "This is a success reminder.", Notification::Type::Success, this);
        noti->show();
    });
    connect(ui->button_60, &Element::Button::clicked, this, [&]() {
        Notification* noti = new Notification("Title", "This is a warning reminder.", Notification::Type::Warning, this);
        noti->show();
    });
    connect(ui->button_61, &Element::Button::clicked, this, [&]() {
        Notification* noti = new Notification("Title", "This is a info reminder.", Notification::Type::Info, this);
        noti->show();
    });
    connect(ui->button_62, &Element::Button::clicked, this, [&]() {
        Notification* noti = new Notification("Title", "This is a error reminder.", Notification::Type::Error, this);
        noti->show();
    });
}

void MainWindow::setupTab6()
{

}

MainWindow::~MainWindow()
{
    delete ui;
}

