#include "worldmap.h"

WorldMap::WorldMap()
{
    worldScene = new QGraphicsScene;
    worldView = new QGraphicsView(worldScene);
    zoomLevel = 0;
    actorList = {};
    pathList = {};
    graphicsItemList = {};
    //railList = {};
    setMap();
}

QGraphicsView *WorldMap::getWorld()
{
    return worldView;

}

QString WorldMap::test()
{
    QPoint testx = dynamic_cast<Actor*>(actorList[0])->getLocation();
    return QString::number(testx.x())+QString::number(testx.y());
}

QPoint WorldMap::getRelativeWorldPos(QPoint point)
{
    int x = point.x();
    int y = point.y();
    QScrollBar* xBar = worldView->horizontalScrollBar();
    QScrollBar* yBar = worldView->verticalScrollBar();
    QPoint newPoint = {0,0};
    if (zoomLevel > 0)
    {
        int xBarValue = xBar->value()*pow(1.25,zoomLevel);
        int yBarValue = yBar->value()*pow(1.25,zoomLevel);
        newPoint = {static_cast<int>((x-100)*pow(1.25,zoomLevel) + xBarValue),static_cast<int>((y-20)*pow(1.25,zoomLevel) + yBarValue)};
    }
    else if (zoomLevel == 0)
    {
        int xBarValue = xBar->value();
        int yBarValue = yBar->value();
        newPoint = {x-100 + xBarValue,y-20 + yBarValue};
    }
    else
    {
        int xBarValue = xBar->value()*pow(0.8,zoomLevel*-1);
        int yBarValue = yBar->value()*pow(0.8,zoomLevel*-1);
        newPoint = {static_cast<int>((x-100)*pow(0.8,zoomLevel*-1) + xBarValue),static_cast<int>((y-20)*pow(0.8,zoomLevel*-1) + yBarValue)};
    }
    return newPoint;
}

QPoint WorldMap::getAbsoluteWorldPos(QPoint point)
{
    int x = point.x();
    int y = point.y();
    QScrollBar* xBar = worldView->horizontalScrollBar();
    QScrollBar* yBar = worldView->verticalScrollBar();
    QPoint newPoint = {0,0};
    if (zoomLevel > 0)
    {
        int xBarValue = xBar->value()/pow(1.25,zoomLevel);
        int yBarValue = yBar->value()/pow(1.25,zoomLevel);
        newPoint = {static_cast<int>((x+100)/pow(1.25,zoomLevel) - xBarValue),static_cast<int>((y+20)/pow(1.25,zoomLevel) - yBarValue)};
    }
    else if (zoomLevel == 0)
    {
        int xBarValue = xBar->value();
        int yBarValue = yBar->value();
        newPoint = {x+100 - xBarValue, y + 20 - yBarValue};
    }
    else
    {
        int xBarValue = xBar->value()/pow(0.8,zoomLevel*-1);
        int yBarValue = yBar->value()/pow(0.8,zoomLevel*-1);
        newPoint = {static_cast<int>((x+100)/pow(0.8,zoomLevel*-1) - xBarValue),static_cast<int>((y+20)/pow(0.8,zoomLevel*-1) - yBarValue)};
    }
    return newPoint;
}

int WorldMap::getWorldWidth()
{
    return worldScene->width();
}

int WorldMap::getWorldHeight()
{
    return worldScene->height();
}

void WorldMap::zoomIn()
{
    if (zoomLevel > MIN_ZOOM_LEVEL)
    {
       worldView->scale(1.25,1.25);
       zoomLevel--;
    }
}

void WorldMap::zoomOut()
{
    if (zoomLevel < MAX_ZOOM_LEVEL)
    {
       worldView->scale(0.8,0.8);
       zoomLevel++;
    }

}

void WorldMap::actualizeMap()
{

}

void WorldMap::createTrain()
{
    /*
    DieselLocomotive* train1 = new DieselLocomotive;
    actorList.push_back(train1);
    DieselLocomotive* x = actorList.last();
    x->setName("train: " + QString::number(x->count));
    */
}

void WorldMap::moveAllTrains()
{

}

void WorldMap::setMap()
{

    //set world border and world size
    int mapXside = MAP_X_SIZE/2;
    int mapYside = MAP_Y_SIZE/2;
    worldScene->addLine(-mapXside + 15,-mapYside + 15,- mapXside +15, mapYside - 15, QPen(Qt::red,30)); //-15 OR +15 DUE TO line thickness
    worldScene->addLine(-mapXside + 15,mapYside - 15,mapXside - 15,mapYside -15, QPen(Qt::red,30));
    worldScene->addLine(mapXside -15,mapYside -15,mapXside -15,-mapYside +15, QPen(Qt::red,30));
    worldScene->addLine(mapXside -15,-mapYside +15,-mapXside +15,-mapYside +15, QPen(Qt::red,30));

    //set prefered zoom def1 + 15 = 16/20
    for (int i = 0; i < 17; i++) zoomOut();

    //images
    //QPixmap pixmap1("C:/Users/Bureš/Desktop/Dočasné dokumenty/C++/Screenshots/1.jpg");
    //QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap1);
    //worldScene->addItem(item);

    //addRoute(0,0,10000,0,10000,10000,0,10000, false);
    //addRoute(0,10000,-10000,0,-10000,-10000,0,-10000, false);
}

void WorldMap::addActor(QPoint spawnPos, int num)
{
    switch (num)
    {
    case 1: //only tests
        {

           QPainterPath path;
           path.cubicTo(10000, 0, 10000, 10000, 0, 10000);
           QGraphicsPathItem* railItem = new QGraphicsPathItem(path); //add graphics
           railItem->setPen(QPen(Qt::blue, 144));
           QPoint relativePos = getRelativeWorldPos(spawnPos);
           railItem->setPos(relativePos);
           worldScene->addItem(railItem);

           Actor* rail = new Rail(railItem); //add actor
           rail->setLocation(spawnPos);

           actorList.push_back(rail); //push actor  - INDEXED WITH graphicsItemList
           graphicsItemList.push_back(railItem); //push graphics - INDEXED WITH actorList

           railList.push_back(dynamic_cast<Rail*>(rail)); //push Rail actor (for find rail actor) - INDEXED WITH pathList (no with actor)
           pathList.push_back(railItem); //push graphic rail item for find graphic - INDEXED WITH railList (no with actor)

           /*
           Actor* newTrain = new Train;
           actorList.push_back(newTrain);
           dynamic_cast<Movable*>(newTrain)->addPath(pathList[0]);
           QString pngPath = QApplication::applicationDirPath() + "/loco.png";
           QPixmap pixmap(pngPath);
           QGraphicsItem* trainItem = new QGraphicsPixmapItem(pixmap);
           worldScene->addItem(trainItem);
           graphicsItemList.push_back(trainItem);
           QPointF relativePos2 = railItem->path().pointAtPercent(0.8);
           QPoint xxx = relativePos2.toPoint();
           trainItem->setPos(getRelativeWorldPos(xxx.x(),xxx.y()));
           */

           Actor* newTrain = new Train;
           actorList.push_back(newTrain);
           dynamic_cast<Movable*>(newTrain)->addPath(pathList[0]);

           QString pngPath = QApplication::applicationDirPath() + "/loco.png";
           QPixmap pixmap(pngPath);

           QGraphicsItem* trainItem = new QGraphicsPixmapItem(pixmap);
           graphicsItemList.push_back(trainItem);

           worldScene->addItem(trainItem);


           QPointF relativePos2 = railItem->path().pointAtPercent(0.5);
           QPoint absolute = getAbsoluteWorldPos(relativePos2.toPoint());

           QGraphicsItem* trainItem2 = new QGraphicsPixmapItem(pixmap);
           graphicsItemList.push_back(trainItem2);

           worldScene->addItem(trainItem2);
           trainItem->setPos(relativePos);
           trainItem2->setPos(absolute);

           break;
        }
    case 2: //only tests;
        {
           Actor* newTrain = new Train;
           actorList.push_back(newTrain);

           dynamic_cast<Movable*>(newTrain)->addPath(pathList[0]);
           QString pngPath = QApplication::applicationDirPath() + "/loco.png";
           QPixmap pixmap(pngPath);
           QGraphicsItem* trainItem = new QGraphicsPixmapItem(pixmap);
           worldScene->addItem(trainItem);
           graphicsItemList.push_back(trainItem);
           QPointF point = dynamic_cast<Movable*>(newTrain)->getLocationOnPath(0.0);
           trainItem->setPos(point);
            newTrain->setLocation(spawnPos);
           break;
        }
    default:
        {}
    }
}

void WorldMap::deleteAllActors()  //QGraphicsItem* item, QString name
{
    for (int i = 0; i < actorList.size(); i++)
    {
       delete actorList[i];
    }
    for (int i = 0; i < graphicsItemList.size(); i++)
    {
       delete graphicsItemList[i];
    }
    actorList.clear();
    graphicsItemList.clear();
}

void WorldMap::setActorLocation(QPoint newLocation, Actor *actor)
{
    if (actor)
    {
        actor->setLocation(newLocation);
        int actorIndex = actorList.indexOf(actor);
        if (Movable* movableActor = dynamic_cast<Movable*>(actor))
        {

            //dynamic_cast<Movable*>(actor)->
        }
        else
        {

        }
    }
}


WorldMap::~WorldMap()
{
    delete worldScene;
    delete worldView;
    deleteAllActors();
}



