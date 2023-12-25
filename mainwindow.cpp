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
}

void MainWindow::initializeInterface()
{
    //ui
    ui->MapViewLayout->addWidget(world->getWorldView(),1);
    ui->UnusedBut1->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->UnusedBut2->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->UnusedBut3->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->UnusedBut4->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->UnusedBut5->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->UnusedBut6->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->UnusedBut7->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->UnusedBut8->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->UnusedBut9->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->UnusedBut10->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->UnusedBut11->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->UnusedBut12->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->UnusedBut13->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->UnusedBut14->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->UnusedBut15->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->UnusedBut16->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->UnusedBut17->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->UnusedBut18->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->UnusedBut19->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->UnusedBut20->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->UnusedBut21->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->UnusedBut22->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button

    //console
    managerConsole = new ManagerConsole(this); //add custom manager console
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QSize sizeView = world->getWorldView()->size();
    managerConsole->setConsolePos({160,sizeView.height()-250},250,250);
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
    if (delta > 0) //front
    {
        QRectF sceneRect = world->getWorldView()->sceneRect();
        QPointF sceneTopLeft = world->getWorldView()->mapToGlobal(sceneRect.topLeft().toPoint());
        int sceneGlobalX = sceneTopLeft.x();
        ui->label->setText(QString::number(globalPos.x()) + " / " + QString::number(globalPos.y()) + " !!! " + QString::number(sceneGlobalX + world->getWorldView()->getMapSizeX()));
    }
    else if (delta < 0) //back
    {
        ui->label->setText(QString::number(globalPos.x()) + " / " + QString::number(globalPos.y()));
    }
    else
    {
        ui->label->setText("nothing");
    }
    QWidget::wheelEvent(event);
}

void MainWindow::on_PlayBut_clicked() {}//overrided
void MainWindow::on_TestButton1_clicked() {}//overrided
void MainWindow::on_MultiFuncBut1_clicked() {}//overrided
void MainWindow::on_MoveBut_clicked() {}//overrided
void MainWindow::on_SubBut_clicked() {}//overrided
void MainWindow::on_AddBut_clicked() {}//overrided

void MainWindow::InterfaceSet(int menuSelected)
{
    switch (menuSelected)
    {
    case 1:
        ui->MultiFuncBut1->setText("nothing");
        break;
    case 2:
        break;
    case 3:
         ui->MultiFuncBut1->setText("Add rail");
        break;
    default:
        ui->MultiFuncBut1->setText("nothing");
    }
}


