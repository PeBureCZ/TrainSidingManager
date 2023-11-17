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
    world->deleteActor(world->getActorFromList(world->getActorListSize()-1));
}

void MainWindow::on_testButton2_clicked()
{
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
                menuSelected = 2;
                int zoom = world->getWorld()->getZoomLevel();
                int maxRadius = 1;
                if (zoom > 0) maxRadius += zoom * 50; //increase radius on zoom in
                QVector<Actor*> actors = world->getActorUnderClick({2}, maxRadius);
                if (actors.size() == 0) world->addRailConstructor(world->getRelativeWorldPos(point), nullptr);
                else if (dynamic_cast<Rail*>(actors[0]))
                {
                    Actor* actor = dynamic_cast<Actor*>(actors[0]);
                    if (dynamic_cast<Rail*>(actor))
                    {
                        Trigger* nearestTrigger = world->getTriggerInRange(actor, world->getRelativeWorldPos(point), maxRadius);
                        world->addRailConstructor(actor->getLocation() + nearestTrigger->getRelativeLocation(), dynamic_cast<Rail*>(actor));
                    }
                }
                break;
            }
            case 2: //2 = constructing rail (RailConstructor)
            {

                int zoom = world->getWorld()->getZoomLevel();
                int maxRadius = 1;
                if (zoom > 0) maxRadius += zoom * 50; //increase radius on zoom in
                QVector<Actor*> actors = world->getActorUnderClick({2}, maxRadius);
                Rail* createdRail = dynamic_cast<Rail*>(world->getActualConstructor()->getActorConstructing());
                world->getWorldCollide()->addTriggerToActor(createdRail, 0, {2}, {0,0}, 0.0f); //for P0 point
                world->getWorldCollide()->addTriggerToActor(createdRail, 0, {2}, createdRail->getP3RelativeLocation().toPoint(), 0.0f);//for P3 point
                if (actors.size() == 0)
                {
                    world->deleteConstructor(false);
                }
                else
                {
                    for (int i = 0; i < actors.size(); ++i)
                    {
                        if (dynamic_cast<Rail*>(actors[i]))
                        {
                            QPoint point = event->pos();
                            Actor* actor = actors[0];
                            Trigger* nearestTrigger = world->getTriggerInRange(actor, world->getRelativeWorldPos(point), maxRadius);
                            world->getActualConstructor()->actualizeConstructor(actor->getLocation() + nearestTrigger->getRelativeLocation());
                            RailConstructor* actualRailConstructor = dynamic_cast<RailConstructor*>(world->getActualConstructor());
                            actualRailConstructor->getOwnedRail()->connectRails(dynamic_cast<Rail*>(actors[0]), false);
                            actualRailConstructor->smoothEndPoint();
                            world->deleteConstructor(false);
                            break;
                        }
                    }
                }
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
        QRectF sceneRect = world->getWorld()->sceneRect();
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

