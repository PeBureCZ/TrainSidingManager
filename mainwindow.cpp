#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    WorldMap world;
    worldObj = world;
    initializeMap();

}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow::initializeMap()
{
    ui->MapView->addWidget(worldObj.getWorld(),1);
}



void MainWindow::on_pushButton_clicked()
{
    worldObj.addRoute(0,0);
}

void MainWindow::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF point = event->scenePos();
    ui->label->setText("xx");
    //worldObj.addRoute(clickPos.x(),clickPos.y());
     //worldObj.addRoute(point.x(),point.y());
    worldObj.addRoute(0,0);
}


