#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    world = new WorldMap;
    initializeMap();
    menuSelected = 0;
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
    int index = 0;
    //world->deleteActor(world->getActorFromList(world->getActorListSize()-1));
    for (auto rail : world->railList)
    {
        qDebug() << QString::number(index);
        (rail->getConnectedRail(0) == nullptr) ? qDebug() << "null" : qDebug() << "connected";
        (rail->getConnectedRail(1) == nullptr) ? qDebug() << "null" : qDebug() << "connected";
        (rail->getConnectedRail(2) == nullptr) ? qDebug() << "null" : qDebug() << "connected";
        (rail->getConnectedRail(3) == nullptr) ? qDebug() << "null" : qDebug() << "connected";
        qDebug() << " ____ ";
        index++;
    }
}

void MainWindow::on_testButton2_clicked()
{
    if (world->railList.size() > 0) world->addTrainActor(world->railList[0]);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        switch (menuSelected)
        {
            //case 0: same as default
            case 1: //1 = add Rail (RailConstructor)
            {
                QPoint point = (world->getRelativeWorldPos(event->pos()));
                int zoom = world->getWorld()->getZoomLevel();
                int maxRadius = 1;
                if (zoom > 0) maxRadius += zoom * 150; //increase radius on zoom in
                QVector<Actor*> actors = world->getActorUnderClick({2});
                if (actors.size() == 0)
                {
                    world->addRailConstructor(point, nullptr);
                    menuSelected = 2;
                }
                else
                {
                    Actor* nearestActor = nullptr;
                    int distance = 99999999;
                    for (int i = 0; i < actors.size(); i++)
                    {
                        Trigger* nearestTrigger = {};
                        if (dynamic_cast<Rail*>(actors[i]))
                        {
                            nearestTrigger = world->getNearestTriggerInRange(actors[i], point, maxRadius);
                            if (nearestTrigger == nullptr) continue; //all triggers are out of range
                            int testedDistance = world->getDistance(nearestTrigger->getRelativeLocation() + dynamic_cast<Actor*>(actors[i])->getLocation(), point);
                            if (distance > testedDistance) //nearest actor by trigger
                            {
                                nearestActor = actors[i];
                                distance = testedDistance;
                            }
                        }
                    }
                    if (nearestActor != nullptr) //all actors are out of range
                    {
                        Trigger* nearestTrigger = world->getNearestTriggerInRange(nearestActor, point, maxRadius);
                        world->addRailConstructor(nearestActor->getLocation() + nearestTrigger->getRelativeLocation(), dynamic_cast<Rail*>(nearestActor));
                        menuSelected = 2;
                    }
                }
                break;
            }
            case 2: //2 = constructing rail (RailConstructor)
            {
                QVector<Actor*> actors = world->getActorUnderClick({2});
                RailConstructor* actualRailConstructor = dynamic_cast<RailConstructor*>(world->getActualConstructor());
                Rail* createdRail = dynamic_cast<Rail*>(actualRailConstructor->getActorConstructing());

                //bug exception (connect self connected Rail)
                for (auto actor : actors)
                {
                    if (dynamic_cast<Rail*>(actor) && -1 != dynamic_cast<Rail*>(actor)->getConnection(createdRail)) return;
                    //true = Rail construction continue with actual Constructor
                }

                int zoom = world->getWorld()->getZoomLevel();
                int maxRadius = 1;
                if (zoom > 0) maxRadius += zoom * 50; //increase radius on zoom in
                world->getWorldCollide()->addTriggerToActor(createdRail, 0, {2}, {0,0}, 0.0f); //for P0 point
                world->getWorldCollide()->addTriggerToActor(createdRail, 0, {2}, createdRail->getP3RelativeLocation().toPoint(), 0.0f);//for P3 point
                world->getWorldCollide()->addTriggerToActor(createdRail, 1, {0}, {0,0}, 0.0f);//create object BoxCollider
                if (actors.size() == 0)
                {
                    actualRailConstructor->setObjectBoxCollider();
                    world->deleteConstructor(false);
                    menuSelected = 1;
                }
                else
                {
                    for (int i = 0; i < actors.size(); ++i)
                    {
                        if (dynamic_cast<Rail*>(actors[i]))
                        {
                            QPoint point = event->pos();
                            Actor* actor = actors[i];
                            Trigger* nearestTrigger = world->getNearestTriggerInRange(actor, world->getRelativeWorldPos(point), maxRadius);
                            actualRailConstructor->actualizeConstructor(actor->getLocation() + nearestTrigger->getRelativeLocation());
                            actualRailConstructor->getOwnedRail()->connectRails(dynamic_cast<Rail*>(actors[i]), false);
                            actualRailConstructor->smoothEndPoint();
                            dynamic_cast<RailConstructor*>(world->getActualConstructor())->setObjectBoxCollider(); //actualize
                            world->deleteConstructor(false);
                            menuSelected = 1;
                        }
                    }
                }
            }
            default:  //incl. 0
            {
                QVector<Actor*> actors = world->getActorUnderClick({0});
                //nothing yet...
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

