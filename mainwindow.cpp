#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    world = new WorldMap;
    initializeMap();
}

void MainWindow::initializeMap()
{
    ui->MapView->addWidget(world->getWorld(),1);
    ui->horizontalLayoutWidget->raise(); //raise layout inMapLayout
}

void MainWindow::on_pushButton_clicked()
{
    QPoint spawnPoint = {0,0};
    world->addActor(spawnPoint,2);
}

void MainWindow::testFce()
{
    ui->label->setText(world->test());
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint point = event->pos();
    //world->addRoute(point.x(),point.y(),1000,0,1000,1000,0,1000, true);
    world->addActor(point,1);
}


void MainWindow::on_SubBut_clicked()
{
    world->zoomOut();
}


void MainWindow::on_AddBut_clicked()
{
    world->zoomIn();
}

void MainWindow::actualizeMap()
{
    world->moveAllTrains();
}

MainWindow::~MainWindow()
{
    delete world;
    delete ui;
}
