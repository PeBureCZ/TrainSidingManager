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
    1 = add Rail (constructor)
    2 = constructing rail (RailConstructor)
    */
}

void MainWindow::initializeMap()
{
    ui->MapView->addWidget(world->getWorld(),1);
    ui->horizontalLayoutWidget->raise(); //raise layout inMapLayout
}

void MainWindow::on_TestButton1_clicked() //temporary
{
    //QPoint spawnPoint = {0,0};
    //world->addTrainActor(world->getRailFromList(0));
    //ui->label->setText(world->test());
    ui->label->setText(world->testFunction());
}

void MainWindow::on_testButton2_clicked()
{
    //world->deleteAllActors();
    ui->label->setText(world->getWorldCollide()->test());
}

void MainWindow::testFce() //temporary
{
    ui->label->setText(world->testFunction());
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        switch (menuSelected)
        {
        case 1: //1 = add Rail (constructor)
        {
            QPoint point = event->pos();
            world->addRailConstructor(point);
            menuSelected = 2;
            break;
            Actor* actor = world->getActorUnderClick({2});
            if (actor = nullptr)
            {

            }
            else
            {
            }
        }
        case 2: //2 = constructing rail (RailConstructor)
        {
            world->deleteConstructor(false);
            menuSelected = 1;
            break;
        }

        default:  //incl. 0 = default
        {
            QPoint globalPos = QCursor::pos();
            QPoint point = event->pos();
            ui->label->setText(QString::number(point.x())  + " __ " + QString::number(point.y()) + " / " + QString::number(globalPos.x())  + " __ " + QString::number(globalPos.y()));
        }
        }
    }
    else if (event->button() == Qt::RightButton)
    {
        switch (menuSelected)
        {
        case 1: //1 = add Rail (constructor)
        {
            //nothing?
            break;
        }
        case 2: //2 = constructing rail (RailConstructor)
        {

            world->deleteConstructor(true);
            menuSelected = 1;
            break;
        }

        default:  //incl. 0 = default
        {
            //will be move map
        }
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
    world->getWorld()->zoomIn(false); //false = sideways by mouse
}

void MainWindow::actualizeMap()
{
    world->actualizeAllInWorld();
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

