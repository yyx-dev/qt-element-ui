#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "icon.h"
#include "text.h"
#include "button.h"
#include "dialog.h"
#include "message.h"
#include "notification.h"
#include "badge.h"
#include "shadow.h"
#include "tooltip.h"

#include <QDebug>
#include <QTimer>

#define TEXT 0
#define BUTTON 1
#define SCROLLBAR 2
#define LINK 3
#define INPUT 4
#define FEEDBACK 5
#define DATA 6
#define PANEL 7
#define PROGRESS 8
#define FORM 9

#define CURRENT_INDEX INPUT

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
    setupTab7();
    setupTab8();
    setupTab9();

    ui->tabWidget->setCurrentIndex(CURRENT_INDEX);

    // Important!
    // Enable to let the focus widget loses focus,
    // when you clicked the application's background.
    setFocusPolicy(Qt::ClickFocus);
}

void MainWindow::setupTabs()
{
    ui->tabWidget->setTabIcon(0, Icon::CirclePlus);
    ui->tabWidget->setTabIcon(1, Icon::Open);
    ui->tabWidget->setTabIcon(2, Icon::Operation);
    ui->tabWidget->setTabIcon(3, Icon::Link);
    ui->tabWidget->setTabIcon(4, Icon::EditPen);
    ui->tabWidget->setTabIcon(5, Icon::Connection);
    ui->tabWidget->setTabIcon(6, Icon::DataBoard);
    ui->tabWidget->setTabIcon(7, Icon::Postcard);
    ui->tabWidget->setTabIcon(8, Icon::Operation);
    ui->tabWidget->setTabIcon(9, Icon::Odometer);
}

void MainWindow::setupTab0()
{
    ui->defaultText->setType(Text::Type::Default).setSize(Text::Size::Large);
    ui->primaryText->setType(Text::Type::Primary).setSize(Text::Size::Default);
    ui->successText->setType(Text::Type::Success);
    ui->infoText->setType(Text::Type::Info);
    ui->warningText->setType(Text::Type::Warning);
    ui->dangerText->setType(Text::Type::Danger);

    auto setStyle = [](QWidget* widget) {
        QFont font = widget->font();
        font.setFamilies(Comm::fontFmailies);
        font.setPointSize(Comm::defaultFontSize);
        widget->setFont(font);
        widget->setStyleSheet("border: none; color: #303133;");
    };

    setStyle(ui->shadow_1);
    setStyle(ui->shadow_2);
    setStyle(ui->shadow_3);
    setStyle(ui->shadow_4);

    ui->shadow_1->setReadOnly(true);
    ui->shadow_2->setReadOnly(true);
    ui->shadow_3->setReadOnly(true);
    ui->shadow_4->setReadOnly(true);

    ui->shadow_1->appendPlainText("\n\n      Shadow Basic");
    ui->shadow_2->appendPlainText("\n\n      Shadow Light");
    ui->shadow_3->appendPlainText("\n\n     Shadow Lighter");
    ui->shadow_4->appendPlainText("\n\n      Shadow Dark");

    Shadow::setShadow(ui->shadow_1, Shadow::Type::Basic);
    Shadow::setShadow(ui->shadow_2, Shadow::Type::Light);
    Shadow::setShadow(ui->shadow_3, Shadow::Type::Lighter);
    Shadow::setShadow(ui->shadow_4, Shadow::Type::Dark);
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

    ui->backtop->setSize(Backtop::Size::Default);
    ui->backtop->setTarget(ui->scrollArea);
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

    ui->popList->addItem("Item 1");
    ui->popList->addItem("Item 2");
    ui->popList->addItem("Item 3");
    ui->popList->addItem("Item 4");
    ui->popList->addItem("Item 5");

    ui->autoComplete->setData({"qt", "vue", "element", "cooking",
                               "mint-ui", "vuex", "vue-router", "babel"});


    ui->button_63->setText("Tooltip");
    Tooltip* tooltip = new Tooltip("test tooltip", ui->button_63);

    tooltip->setEffect(Tooltip::Effect::Light);
    tooltip->setPlacement(Tooltip::Placement::Right);
    tooltip->setTrigger(Tooltip::Trigger::Hover);

    ui->switch_1->setSize(Switch::Size::Large);
    ui->switch_2->setSize(Switch::Size::Default);
    ui->switch_3->setSize(Switch::Size::Small);

    ui->switch_1->setActiveColor(Color::success());
    ui->switch_1->setInactiveColor(Color::danger());

    ui->switch_1->setActiveText("Pay by year");
    ui->switch_1->setInactiveText("Pay by month");

    // ui->switch_2->setLoading(true);
    // ui->switch_2->setActiveAction(Icon::View);
    // ui->switch_2->setInactiveAction(Icon::Hide);
    ui->switch_2->setActiveAction('T');
    ui->switch_2->setInactiveAction('F');

    ui->switch_3->setDisabled(true);
}

void MainWindow::setupTab5()
{
    connect(ui->button_42, &Button::clicked, this, [&]() {
        Dialog* dialog = new Dialog("Tips", "this is a message dialog", this);
        dialog->show();
    });
    connect(ui->button_43, &Button::clicked, this, [&]() {
        Message* message = new Message("This is a message.", " VNode", this);
        message->setType(Message::Type::Info);
        message->show();
    });
    connect(ui->button_44, &Button::clicked, this, [&]() {
        Message* message = new Message("This is a message on top left.", this);
        message->setPlacement(Message::Place::TopLeft);
        message->show();
    });
    connect(ui->button_45, &Button::clicked, this, [&]() {
        Message* message = new Message("This is a message on top right.", this);
        message->setPlacement(Message::Place::TopRight);
        message->show();
    });
    connect(ui->button_46, &Button::clicked, this, [&]() {
        Message* message = new Message("This is a message on bottom.", this);
        message->setPlacement(Message::Place::Bottom);
        message->show();
    });
    connect(ui->button_47, &Button::clicked, this, [&]() {
        Message* message = new Message("This is a message on bottom left.", this);
        message->setPlacement(Message::Place::BottomLeft);
        message->show();
    });
    connect(ui->button_48, &Button::clicked, this, [&]() {
        Message* message = new Message("This is a message on bottom right.", this);
        message->setPlacement(Message::Place::BottomRight);
        message->show();
    });
    connect(ui->button_49, &Button::clicked, this, [&]() {
        Message* message = new Message("This is a primary message.", Message::Type::Primary, this);
        message->show();
    });
    connect(ui->button_50, &Button::clicked, this, [&]() {
        Message* message = new Message("This is a success message.", Message::Type::Success, this);
        message->show();
    });
    connect(ui->button_51, &Button::clicked, this, [&]() {
        Message* message = new Message("This is a warning message.", Message::Type::Warning, this);
        message->show();
    });
    connect(ui->button_52, &Button::clicked, this, [&]() {
        Message* message = new Message("This is a info message.", Message::Type::Info, this);
        message->show();
    });
    connect(ui->button_53, &Button::clicked, this, [&]() {
        Message* message = new Message("This is a error message.", Message::Type::Error, this);
        message->show();
    });
    connect(ui->button_54, &Button::clicked, this, [&]() {
        Notification* noti = new Notification("Title", "This is a reminder.", this);
        noti->show();
    });
    connect(ui->button_55, &Button::clicked, this, [&]() {
        Notification* noti = new Notification("Title", "This is a reminder on top left.", this);
        noti->setPosition(Notification::Position::TopLeft);
        noti->show();
    });
    connect(ui->button_56, &Button::clicked, this, [&]() {
        Notification* noti = new Notification("Title", "This is a reminder on bottom right.", this);
        noti->setPosition(Notification::Position::BottomLeft);
        noti->show();
    });
    connect(ui->button_57, &Button::clicked, this, [&]() {
        Notification* noti = new Notification("Title", "This is a reminder on bottom right.", this);
        noti->setPosition(Notification::Position::BottomRight);
        noti->show();
    });
    connect(ui->button_58, &Button::clicked, this, [&]() {
        Notification* noti = new Notification("Title", "This is a primary reminder.", Notification::Type::Primary, this);
        noti->show();
    });
    connect(ui->button_59, &Button::clicked, this, [&]() {
        Notification* noti = new Notification("Title", "This is a success reminder.", Notification::Type::Success, this);
        noti->show();
    });
    connect(ui->button_60, &Button::clicked, this, [&]() {
        Notification* noti = new Notification("Title", "This is a warning reminder.", Notification::Type::Warning, this);
        noti->show();
    });
    connect(ui->button_61, &Button::clicked, this, [&]() {
        Notification* noti = new Notification("Title", "This is a info reminder.", Notification::Type::Info, this);
        noti->show();
    });
    connect(ui->button_62, &Button::clicked, this, [&]() {
        Notification* noti = new Notification("Title", "This is a error reminder.", Notification::Type::Error, this);
        noti->show();
    });

    ui->dropdown->addItem("action 1");
    ui->dropdown->addItem("action 2");
    ui->dropdown->addItem("action 3");
    ui->dropdown->addSeparator();
    ui->dropdown->addItem("action 4");
}

void MainWindow::setupTab6()
{
    ui->avatar->setImage();

    Badge* badge = new Badge(ui->avatar);
    badge->setValue(1);

    ui->tag_01->setType(Tag::Type::Primary);
    ui->tag_02->setType(Tag::Type::Success);
    ui->tag_03->setType(Tag::Type::Info);
    ui->tag_04->setType(Tag::Type::Warning);
    ui->tag_05->setType(Tag::Type::Danger);

    ui->tag_06->setType(Tag::Type::Primary).setEffect(Tag::Effect::Dark);
    ui->tag_07->setType(Tag::Type::Success).setEffect(Tag::Effect::Dark);
    ui->tag_08->setType(Tag::Type::Info).setEffect(Tag::Effect::Dark);
    ui->tag_09->setType(Tag::Type::Warning).setEffect(Tag::Effect::Dark);
    ui->tag_10->setType(Tag::Type::Danger).setEffect(Tag::Effect::Dark);

    ui->tag_11->setType(Tag::Type::Primary).setEffect(Tag::Effect::Plain);
    ui->tag_12->setType(Tag::Type::Success).setEffect(Tag::Effect::Plain);
    ui->tag_13->setType(Tag::Type::Info).setEffect(Tag::Effect::Plain);
    ui->tag_14->setType(Tag::Type::Warning).setEffect(Tag::Effect::Plain);
    ui->tag_15->setType(Tag::Type::Danger).setEffect(Tag::Effect::Plain);

    ui->tag_16->setType(Tag::Type::Primary).setRound(true);
    ui->tag_17->setType(Tag::Type::Success).setRound(true);
    ui->tag_18->setType(Tag::Type::Info).setRound(true);
    ui->tag_19->setType(Tag::Type::Warning).setRound(true);
    ui->tag_20->setType(Tag::Type::Danger).setRound(true);

    ui->tag_21->setType(Tag::Type::Primary);
    ui->tag_22->setType(Tag::Type::Success);
    ui->tag_23->setType(Tag::Type::Info);
    ui->tag_24->setType(Tag::Type::Warning);
    ui->tag_25->setType(Tag::Type::Danger);

    ui->tag_21->setCloseable(true);
    ui->tag_22->setCloseable(true);
    ui->tag_23->setCloseable(true);
    ui->tag_24->setCloseable(true);
    ui->tag_25->setCloseable(true);

    ui->table->setWidth({200, 200});

    ui->table->setHightlight(0, Table::Highlight::Primary)
              .setHightlight(2, Table::Highlight::Success);
}

void MainWindow::setupTab7()
{
    ui->card_1->setHeader("Card name")
               .setBody({"List item 1", "List item 2", "List item 3", "List item 4"})
               .setFooter("Footer content")
               .setShadow(Card::Shadow::Always);

    ui->card_2->setHeader("Yummy hamburger")
               .setBody(QImage(":/icons/other/hamburger.png"));

    ui->collapseItem->setTitle("Consistency")
        .setContent("Consistent with real life: in line with the process and logic of real life, "
                    "and comply with languages and habits that the users are used to;\n"
                    "Consistent within interface: all elements should be consistent, "
                    "such as: design style, icons and texts, position of elements, etc.");
    ui->collapseItem->setCollapse();
}

void MainWindow::setupTab8()
{
    CollapseItem* item_1 = new CollapseItem("Consistency", "Consistent with real life: in line with the process and logic of real life, and comply with languages and habits that the users are used to;\nConsistent within interface: all elements should be consistent, such as: design style, icons and texts, position of elements, etc.", ui->collapse);
    CollapseItem* item_2 = new CollapseItem("Feedback", "Operation feedback: enable the users to clearly perceive their operations by style updates and interactive effects;\nVisual feedback: reflect current state by updating or rearranging elements of the page.", ui->collapse);
    CollapseItem* item_3 = new CollapseItem("Efficiency", "Simplify the process: keep operating process simple and intuitive;\nDefinite and clear: enunciate your intentions clearly so that the users can quickly understand and make decisions;\nEasy to identify: the interface should be straightforward, which helps the users to identify and frees them from memorizing and recalling.", ui->collapse);
    CollapseItem* item_4 = new CollapseItem("Controllability", "Decision making: giving advices about operations is acceptable, but do not make decisions for the users;\nControlled consequences: users should be granted the freedom to operate, including canceling, aborting or terminating current operation.", ui->collapse);

    ui->collapse->addItem(item_1).addItem(item_2).addItem(item_3).addItem(item_4);

    ui->upload_1->setTip("jpg/png files with a size less than 500kb.")
                 .setDrag(true);
    ui->upload_2->setTip("jpg/png files with a size less than 500kb.");

    connect(ui->upload_1, &Upload::uploadRequested, this, [](const QStringList& paths) {
        qDebug() << "received uploadRequest:" << paths;
    });
    connect(ui->upload_1, &Upload::removeRequested, this, [](const QString& path) {
        qDebug() << "received removeRequest:" << path;
    });

    connect(ui->upload_2, &Upload::uploadRequested, this, [](const QStringList& paths) {
        qDebug() << "received uploadRequest:" << paths;
    });
    connect(ui->upload_2, &Upload::removeRequested, this, [](const QString& path) {
        qDebug() << "received removeRequest:" << path;
    });
}

void MainWindow::setupTab9()
{
    ui->checkbox_1->setSize(Checkbox::Size::Large).setBorder(true);
    ui->checkbox_2->setSize(Checkbox::Size::Large);
    ui->checkbox_3->setSize(Checkbox::Size::Default).setBorder(true);
    ui->checkbox_4->setSize(Checkbox::Size::Default).setChecked(true).setDisabled(true);
    ui->checkbox_5->setSize(Checkbox::Size::Small).setBorder(true);
    ui->checkbox_6->setSize(Checkbox::Size::Small);

    ui->checkboxGroup->addCheckbox(ui->checkbox_8)
                      .addCheckbox(ui->checkbox_9)
                      .addCheckbox(ui->checkbox_10);

    ui->checkbox_7->setIndeterminate(true).setDisabled(true);
    ui->checkboxGroup->setMin(1).setMax(2);

    ui->radio_1->setSize(Radio::Size::Large).setBorder(true);
    ui->radio_2->setSize(Radio::Size::Large);
    ui->radio_3->setSize(Radio::Size::Default).setBorder(true);
    ui->radio_4->setSize(Radio::Size::Default).setChecked(true).setDisabled(true);
    ui->radio_5->setSize(Radio::Size::Small).setBorder(true);
    ui->radio_6->setSize(Radio::Size::Small);

    ui->radioGroup->addRadio(ui->radio_7)
                   .addRadio(ui->radio_8)
                   .addRadio(ui->radio_9);

    ui->rate->setSize(Rate::Size::Default);
//    ui->rate->setDisabled(true);
    ui->rate->setShowText(true);
//    ui->rate->setShowScore(true);
//    ui->rate->setAllowHalf(true);
    ui->rate->setTexts("oops", "disappointed", "normal", "good", "great");
}

MainWindow::~MainWindow()
{
    delete ui;
}
