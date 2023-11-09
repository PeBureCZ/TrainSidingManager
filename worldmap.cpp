#include "worldmap.h"

WorldMap::WorldMap()
{
    worldScene = new QGraphicsScene;
    worldView = new CustomQGraphicsView;
    worldView->setScene(worldScene);
    actorList = {}; //push actor  - INDEXED WITH graphicsItemList
    graphicsItemList = {}; //push graphics - INDEXED WITH actorList
    pathList = {}; //push graphic rail item for find graphic - INDEXED WITH railList (no with actor)
    railList = {}; //push Rail actor (for find rail actor) - INDEXED WITH pathList (no with actor)
    setMap(250000, 200000); //set map x,y border size
}

CustomQGraphicsView *WorldMap::getWorld() //return view of scene (QGraphicsView)
{
    return worldView;
}

QString WorldMap::test()
{
    return "";
}

QPoint WorldMap::getRelativeWorldPos(QPoint point)
//transfer position from (e.g.) mouse click event in mainwindow (relative to scene) to scene coordination
{
    int zoomLevel = worldView->getZoomLevel();
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

int WorldMap::getWorldWidth()
{
    return worldScene->width();
}

int WorldMap::getWorldHeight()
{
    return worldScene->height();
}


void WorldMap::actualizeMap()
{

}

void WorldMap::addTrainActor(Rail* spawnOnRail)
{
    if (pathList.size() > 0)
    {
       Actor* newTrain = new Train(spawnOnRail);
       actorList.push_back(newTrain);

       dynamic_cast<Train*>(newTrain)->setActualPath(pathList[0]);
       QString pngPath = QApplication::applicationDirPath() + "/loco.png";
       //QString pngPath = ""; // TEST ONLY - ABSOLUTE
       QPixmap pixmap(pngPath);
       QGraphicsItem* trainItem = new QGraphicsPixmapItem(pixmap);
       worldScene->addItem(trainItem);
       graphicsItemList.push_back(trainItem);
       QPointF spawnPoint = dynamic_cast<Train*>(newTrain)->getLocationOnPath(0.0) + dynamic_cast<Train*>(newTrain)->getActualPath()->pos();
       trainItem->setPos(spawnPoint);
       newTrain->setLocation(spawnPoint.toPoint());
    }
}

void WorldMap::addRailActor(QPoint point)
{
    QPainterPath path;
    path.cubicTo(10000, 0, 10000, 10000, 0, 10000);
    QGraphicsPathItem* railItem = new QGraphicsPathItem(path); //add graphics
    railItem->setPen(QPen(Qt::blue, 144));
    QPoint relativePos = getRelativeWorldPos(point);
    railItem->setPos(relativePos.toPointF());
    worldScene->addItem(railItem);

    Actor* rail = new Rail(railItem); //add actor
    railList.push_back(dynamic_cast<Rail*>(rail));
    actorList.push_back(rail);
    graphicsItemList.push_back(railItem);
    pathList.push_back(railItem);

    rail->setLocation(point);
}

void WorldMap::addStaticlActor(QPoint spawnPos, int num)
{
    switch (num)
    {
        case 1:
        {
           //code
           break;
        }
        case 2:
        {
           //code
           break;
        }
        default:
        {}
    }
}

void WorldMap::addRailwaylActor(Rail* railActor, int num) //need to refract later!
{
    switch (num)
    {
        case 1:
        {
           //createRail(spawnPos);
           break;
        }
        case 2:
        {
           //createTrain(spawnPos);
           break;
        }
        default:
        {}
    }
}

void WorldMap::moveAllTrains() //need to refract later!
{
    for (auto actor : actorList)
    {
       if (dynamic_cast<Train*>(actor))
       {
           float currentPathValue = dynamic_cast<Train*>(actor)->getActualPathValue(); //check value on path = % value (e.g. 0.542)
           QGraphicsPathItem* actualPath = dynamic_cast<Train*>(actor)->getActualPath(); //check actual path saved in train
           float newPathValue = currentPathValue + 0.001; //temporary solution - train need speed!
           (newPathValue > 1 ) ? newPathValue = 1 : newPathValue; //temporary - train will continue on the new path/rail track, atc.
           QPoint onPathPoint = actualPath->path().pointAtPercent(newPathValue).toPoint() + actualPath->pos().toPoint(); //get new scene location
           setActorLocation(onPathPoint,actor); //actualize actor location
           dynamic_cast<Train*>(actor)->setActualPathValue(newPathValue); //actualize new train value on path (rail track)
       }
    }
}

void WorldMap::setMap(int xSize, int ySize) //need to refract later!
{
    worldView->setWorldMap(xSize, ySize);
    int mapXside = worldView->getMapSizeX();
    int mapYside = worldView->getMapSizeY();
    worldScene->addLine(-mapXside + 150,-mapYside + 150,- mapXside +150, mapYside - 150, QPen(Qt::red,300)); //-15 OR +15 DUE TO line thickness
    worldScene->addLine(-mapXside + 150,mapYside - 150,mapXside - 150,mapYside -150, QPen(Qt::red,300));
    worldScene->addLine(mapXside -150,mapYside -150,mapXside -150,-mapYside +150, QPen(Qt::red,300));
    worldScene->addLine(mapXside -150,-mapYside +150,-mapXside +150,-mapYside +150, QPen(Qt::red,300));
    /*
    IMAGES - NEED ADD THIS OPTION! (image instances?!)
    QPixmap pixmap1("C:/Users/Bureš/Desktop/Dočasné dokumenty/C++/Screenshots/1.jpg");
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap1);
    worldScene->addItem(item);
    */
}

void WorldMap::setActorLocation(QPoint newLocation, Actor* actor)
{
    if (actor)
    {
        actor->setLocation(newLocation);
        int actorIndex = actorList.indexOf(actor);

        //if (dynamic_cast<Train*>(actor))
        // if (Movable* movableActor = dynamic_cast<Movable*>(actor))

        if (dynamic_cast<Movable*>(actor))
        {
           if (dynamic_cast<Train*>(actor))
           {
                   dynamic_cast<QGraphicsItem*>(graphicsItemList[actorIndex])->setPos(newLocation);
           }
           //...new code here - movable "world objects"?
        }
        else //static objects?
        {
           //....
        }
    }
}

Rail* WorldMap::getRailFromList(int index)
{
    return railList[index];
}

Actor* WorldMap::getActorFromList(int index)
{
    return actorList[index];
}

void WorldMap::deleteAllActors()
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

WorldMap::~WorldMap()
{
    deleteAllActors();
    delete worldScene;
    delete worldView; //is needed? Scene is parent! Unchecked destructor...
}



