#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    world = new WorldMap;
    initializeMap();
    menuSelected = 0; //basic menu - "click" only
    /*
    0 =basic (select)
    1 = add Rail (actor)
    */
}

void MainWindow::initializeMap()
{
    ui->MapView->addWidget(world->getWorld(),1);
    ui->horizontalLayoutWidget->raise(); //raise layout inMapLayout
}

void MainWindow::on_TestButton_clicked() //temporary
{
    QPoint spawnPoint = {0,0};
    world->addTrainActor(world->getRailFromList(0));
}

void MainWindow::testFce() //temporary
{
    ui->label->setText(world->test());
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    switch (menuSelected)
    {
        case 1:
        {
            QPoint point = event->pos();
            //world->addRoute(point.x(),point.y(),1000,0,1000,1000,0,1000, true);
            world->addRailActor(point);
            break;
        }
        default:  //incl. 0 = default
        {

        }
    }
}


void MainWindow::wheelEvent(QWheelEvent *event)
{
    QPoint globalPos = QCursor::pos();
    int delta = event->angleDelta().y();

    if (delta > 0) //front
    {
            QRectF sceneRect = world->worldScene->sceneRect();
            QPointF sceneTopLeft = world->getWorld()->mapToGlobal(sceneRect.topLeft().toPoint());
            int sceneGlobalX = sceneTopLeft.x();
            ui->label->setText(QString::number(globalPos.x()) + " / " + QString::number(globalPos.y()) + " !!! " + QString::number(sceneGlobalX + world->getWorld()->getMapSizeX()));
    //world->getWorld()->testX());
    }
    else if (delta < 0) //beck
    {
            ui->label->setText(QString::number(globalPos.x()) + " / " + QString::number(globalPos.y()));
    }
    else
    {
        ui->label->setText("nothing");
    }
    QWidget::wheelEvent(event);
}


void MainWindow::on_SubBut_clicked()
{
    world->getWorld()->zoomOut();
}


void MainWindow::on_AddBut_clicked()
{
    world->getWorld()->zoomIn();
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

void MainWindow::on_MoveBut_clicked()
{
    menuSelected = 0;
}

void MainWindow::on_AddRailBut_clicked()
{
    menuSelected = 1;
}




