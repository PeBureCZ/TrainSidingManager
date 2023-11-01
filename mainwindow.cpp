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


void MainWindow::initializeMap()
{
    ui->MapView->addWidget(worldObj.getWorld(),1);
    ui->horizontalLayoutWidget->raise(); //raise layout inMapLayout
}



void MainWindow::on_pushButton_clicked()
{
    ui->label->setText(worldObj.test());
}

void MainWindow::testFce()
{

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint point = event->pos();
    //QPoint scenePoint = ui->graphicsView->mapToScene(windowPos);

    //ui->label->setText("test: " + QString::number(scenePoint.x())+ QString::number(scenePoint.y())); //return coordinate 100,100 on map
    ui->label->setText(QString::number(point.x()) + "/"+ QString::number(point.y()));

    //worldObj.addPoint(point.x(),point.y());
     worldObj.addRoute(point.x(),point.y(),1000,0,1000,1000,0,1000, true);
    //worldObj.addRoute(point.x(),point.y());
}



void MainWindow::on_SubBut_clicked()
{
    worldObj.zoomOut();
}


void MainWindow::on_AddBut_clicked()
{
    worldObj.zoomIn();
}

