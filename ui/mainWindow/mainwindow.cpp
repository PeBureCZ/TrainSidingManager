#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    world = new WorldMap(nullptr, new QGraphicsScene, new CustomQGraphicsView, new WorldCollide);
    initializeInterface();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete world;
    delete mapZoomLayout;
    delete widgetWithLayout;
}

void MainWindow::initializeInterface()
{
    //ui
    setEditAddInterface(EDIT_MODE_FREE);
    //Map
    ui->MapViewLayout->addWidget(world->getWorldView(),1);
    //unused button
    ui->MultiFuncBut4->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->MultiFuncBut5->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->MultiFuncBut6->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->MultiFuncBut7->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->MultiFuncBut8->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->MultiFuncBut9->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->MultiFuncBut10->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->MultiFuncBut11->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->MultiFuncBut12->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->MultiFuncBut13->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->MultiFuncBut14->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->MultiFuncBut15->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->MultiFuncBut16->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->MultiFuncBut17->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->MultiFuncBut18->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->MultiFuncBut19->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->MultiFuncBut20->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->MultiFuncBut21->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->MultiFuncBut22->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->MultiFuncBut23->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    //console
    managerConsole = new ManagerConsole(this); //add custom manager console
    //zoom option in map
    mapZoomLayout = new QHBoxLayout();
    widgetWithLayout = new QWidget();
    mapZoomLayout->addWidget(ui->SubBut);
    mapZoomLayout->addWidget(ui->AddBut);
    widgetWithLayout->setLayout(mapZoomLayout);
    widgetWithLayout->setGeometry(QRect(160,20,100,50));

    //BASIC STATS
    ui->BasicStats->setVisible(true);

    //SPECIAL STATS
    ui->SpecialStats->setVisible(true);
    //ui->SpecialLabel1->setVisible(false);
    //ui->SpecialTextEdit1->setVisible(false);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QSize sizeView = world->getWorldView()->size();
    managerConsole->setConsolePos({160,0},sizeView.width(),sizeView.height());
    managerConsole->printToConsole("bugged console (you have to resize window), affects response to mouse events", RED_BOLD_COLOR, MIDDLE_DURATION);
}

void MainWindow::playButSwitch(bool editMode)
{
    if (editMode) ui->PlayBut->setText("PlayMode");
    else ui->PlayBut->setText("EditMode");
    selectMenuSwitch(false);
}

void MainWindow::selectMenuSwitch(bool selectMode)
{
    (selectMode) ? ui->MenuName->setText("EDIT MENU") : ui->MenuName->setText("ADD MENU");
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    QPoint globalPos = QCursor::pos();
    int delta = event->angleDelta().y();
    if (delta > 0)
    {
        world->getWorldView()->zoomIn(true);
    }
    else if (delta < 0)
    {
        world->getWorldView()->zoomOut();
    }
    QWidget::wheelEvent(event);
}

void MainWindow::on_PlayBut_clicked() {}//overrided
void MainWindow::on_TestButton1_clicked()
{
    world->testFunction();
}
void MainWindow::on_SubBut_clicked() {}//overrided
void MainWindow::on_AddBut_clicked() {}//overrided
void MainWindow::on_AddMenuBut_clicked(){}//overrided
void MainWindow::on_EditMenuBut_clicked(){}//overrided

void MainWindow::on_MultiFuncBut1_clicked() {}//overrided
void MainWindow::on_MultiFuncBut2_clicked() {}//overrided
void MainWindow::on_MultiFuncBut3_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut4_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut5_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut6_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut7_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut8_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut9_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut10_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut11_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut12_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut13_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut14_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut15_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut16_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut17_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut18_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut19_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut20_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut21_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut22_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut23_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut24_clicked() {}//overrided

void MainWindow::InterfaceSet(int menuSelected)
{
    if (menuSelected >= OPTION_MODE_START && menuSelected <= OPTION_MODE_END) setBasicMenuInterface();
    else if (menuSelected >= EDIT_MODE_START && menuSelected <= EDIT_ADD_END) setEditAddInterface(menuSelected);
    else if (menuSelected >= SELECT_EDIT_START && menuSelected <= EDIT_MODE_END) setEditSelectInterface(menuSelected);
    else if (menuSelected >= PLAY_MODE_START && menuSelected <= ADD_PLAY_END) setPlayAddInterface(menuSelected);
    else if (menuSelected >= SELECT_PLAY_START && menuSelected <= PLAY_MODE_END) setPlaySelectInterface(menuSelected);
}

void MainWindow::setBasicMenuInterface()
{
    freeButton(ui->MultiFuncBut1);
    freeButton(ui->MultiFuncBut2);
    freeButton(ui->MultiFuncBut3);
    freeButton(ui->MultiFuncBut24);
}

void MainWindow::setEditSelectInterface(int menu)
{
    switch (menu)
    {
    case SELECT_EDIT_START:
        setButtonText("Rails", ui->MultiFuncBut1);
        freeButton(ui->MultiFuncBut2);
        freeButton(ui->MultiFuncBut3);
        freeButton(ui->MultiFuncBut24);
        break;
    default: setBasicMenuInterface();
    }
}

void MainWindow::setEditAddInterface(int menu)
{
    switch (menu)
    {
    case EDIT_MODE_FREE:
        setButtonText("Rails", ui->MultiFuncBut1);
        setButtonText("Signals", ui->MultiFuncBut2);
        setButtonText("Portals", ui->MultiFuncBut3);
        setButtonText("Delete", ui->MultiFuncBut24);
        break;
    default: setBasicMenuInterface();
    }
}

void MainWindow::setPlaySelectInterface(int menu)
{
    switch (menu)
    {
        default: setBasicMenuInterface();
    }
}

void MainWindow::setPlayAddInterface(int menu)
{
    switch (menu)
    {
    case PLAY_MODE_FREE:
        setButtonText("Train", ui->MultiFuncBut1);
        freeButton(ui->MultiFuncBut2);
        freeButton(ui->MultiFuncBut3);
        freeButton(ui->MultiFuncBut24);
        break;
    default: setBasicMenuInterface();
    }
}
