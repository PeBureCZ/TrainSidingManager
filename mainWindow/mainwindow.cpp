#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    world = new WorldMap;
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
    ui->MultiFuncBut1->setStyleSheet("background-color: rgba(240, 240, 240, 255);");
    ui->MultiFuncBut1->setText("Rails");
    ui->MultiFuncBut2->setStyleSheet("background-color: rgba(240, 240, 240, 255);");
    ui->MultiFuncBut2->setText("Signals");
    ui->MultiFuncBut24->setStyleSheet("background-color: rgba(240, 240, 240, 255);");
    ui->MultiFuncBut24->setText("Delete");
    //Map
    ui->MapViewLayout->addWidget(world->getWorldView(),1);
    //unused button

    ui->MultiFuncBut3->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
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
    mapZoomLayout = new QHBoxLayout;
    widgetWithLayout = new QWidget;
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
    managerConsole->setConsolePos({160,sizeView.height()-250},750,250);
}

void MainWindow::playButSwitch(bool editMode)
{
    if (editMode) ui->PlayBut->setText("PlayMode");
    else ui->PlayBut->setText("EditMode");
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
void MainWindow::on_TestButton1_clicked() {}//overrided
void MainWindow::on_MultiFuncBut1_clicked() {}//overrided
void MainWindow::on_MultiFuncBut2_clicked() {}//overrided
void MainWindow::on_SubBut_clicked() {}//overrided
void MainWindow::on_AddBut_clicked() {}//overrided
void MainWindow::on_MultiFuncBut24_clicked() {}

void MainWindow::InterfaceSet(int menuSelected)
{
    switch (menuSelected)
    {
    case EDIT_MODE:
        ui->MultiFuncBut1->setText("");
        ui->MultiFuncBut1->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
        ui->MultiFuncBut2->setText("");
        ui->MultiFuncBut2->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
        ui->MultiFuncBut24->setText("");
        ui->MultiFuncBut24->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
        break;
    case RAIL_ADD_MODE:
        break;
    case PLAY_MODE:
        ui->MultiFuncBut1->setStyleSheet("background-color: rgba(240, 240, 240, 255);");
        ui->MultiFuncBut1->setText("Rails");
        ui->MultiFuncBut2->setStyleSheet("background-color: rgba(240, 240, 240, 255);");
        ui->MultiFuncBut2->setText("Signals");
        ui->MultiFuncBut24->setStyleSheet("background-color: rgba(240, 240, 240, 255);");
        ui->MultiFuncBut24->setText("Delete");
        break;
    default:
        ui->MultiFuncBut1->setText("");
        ui->MultiFuncBut1->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
        ui->MultiFuncBut2->setText("");
        ui->MultiFuncBut2->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
        ui->MultiFuncBut24->setText("");
        ui->MultiFuncBut24->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    }
}



