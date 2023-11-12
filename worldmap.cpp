#include "worldmap.h"

WorldMap::WorldMap()
{
    worldScene = new QGraphicsScene;
    worldView = new CustomQGraphicsView;
    worldCollide = new WorldCollide;

    actualConstructor = nullptr;
    worldView->setScene(worldScene);
    actorListIndexed = {}; //push actor  - INDEXED WITH graphicsItemList
    graphicsItemListIndexed = {}; //push graphics - INDEXED WITH actorList
    pathListIndexed = {}; //push graphic rail item for find graphic - INDEXED WITH railList (no with actor)
    railListIndexed = {}; //push Rail actor (for find rail actor) - INDEXED WITH pathList (no with actor)
    tickedActorsList = {}; //list of actor with any tick event (animation, move, etc.)
    setMap(250000, 200000); //set map x,y border size
}

CustomQGraphicsView *WorldMap::getWorld() //return view of scene (QGraphicsView)
{
    return worldView;
}

QString WorldMap::test()
{
    addTrainActor(railListIndexed[0]);
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

void WorldMap::addTrainActor(Rail* spawnOnRail)
{
    if (pathListIndexed.size() > 0)
    {
       Actor* newTrain = new Train(spawnOnRail);
       Vehicle* newVehicle = new CD730;
       dynamic_cast<Train*>(newTrain)->addVehicle(newVehicle);
       actorListIndexed.push_back(newTrain);
       tickedActorsList.push_back(newTrain); //actor with tick update
       dynamic_cast<Train*>(newTrain)->setActualPath(pathListIndexed[0]);
       SpriteColection newSprite; //struct
       QGraphicsItem* trainItem = new QGraphicsPixmapItem(newSprite.loco()); //sprite from struct

       worldScene->addItem(trainItem);
       graphicsItemListIndexed.push_back(trainItem);
       QPointF spawnPoint = dynamic_cast<Train*>(newTrain)->getLocationOnPath(0.0) + dynamic_cast<Train*>(newTrain)->getActualPath()->pos();
       trainItem->setPos(spawnPoint);
       newTrain->setLocation(spawnPoint.toPoint());
    }
}

void WorldMap::addActorToLists(Actor* addedActor, QGraphicsItem* graphicsItem)
{
    actorListIndexed.push_back(addedActor); //indexed
    graphicsItemListIndexed.push_back(graphicsItem);//indexed
}

void WorldMap::addRailToLists(Rail* addedRailActor, QGraphicsPathItem* addedPath)
{
    railListIndexed.push_back(dynamic_cast<Rail*>(addedRailActor));//indexed
    pathListIndexed.push_back(addedPath);//indexed
}

void WorldMap::deleteActor(Actor *actor)
{
    if (tickedActorsList.contains(actor)) tickedActorsList.remove(tickedActorsList.indexOf(actor));

    if (dynamic_cast<Rail*>(actor))
    {
       int railIndex = railListIndexed.indexOf(dynamic_cast<Rail*>(actor));
       railListIndexed.remove(railIndex); //actor will be deleted from actor List
       pathListIndexed.remove(railIndex); //path will be deleted from actor List
    }
    int actorIndex = actorListIndexed.indexOf(actor);
    delete actorListIndexed[actorIndex];
    delete graphicsItemListIndexed[actorIndex];
    actorListIndexed.remove(actorIndex);
    graphicsItemListIndexed.remove(actorIndex);
}

void WorldMap::addRailConstructor(QPoint point)
{
    //ADD PATH FOR RAIL ACTOR and CONSTRUCTOR ACTOR
    QPainterPath path;
    path.cubicTo(10000, 0, 10000, 10000, 0, 10000); //deffault line -> will be changed immediately
    QGraphicsPathItem* pathItem = new QGraphicsPathItem(path); //add graphics
    pathItem->setPen(QPen(Qt::blue, 144));
    QPoint relativePos = getRelativeWorldPos(point);
    pathItem->setPos(relativePos.toPointF());
    worldScene->addItem(pathItem);

    QGraphicsPathItem* pathDuplicated = new QGraphicsPathItem(path); //due to indexed - invisible - not added to scene

    //ADD RAIL ACTOR
    Actor* rail = new Rail(pathItem); //add actor
    addActorToLists(rail,pathItem);
    addRailToLists(dynamic_cast<Rail*>(rail),pathItem);
    rail->setLocation(point);

    //ADD CONSTRUCTOR ACTOR
    Actor* railConstructor = new RailConstructor(rail, relativePos, nullptr, 0); //add actor
    addActorToLists(railConstructor,pathDuplicated);
    setConstructor(railConstructor);
    tickedActorsList.push_back(railConstructor);
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

void WorldMap::actualizeAllInWorld() //need to refract later! -> only moving actors!
{

    for (auto actor : tickedActorsList)
    {
       if (dynamic_cast<Train*>(actor))
       {
            //NEW MOVEMENT VERSION
            int currentPathLength = dynamic_cast<Train*>(actor)->getActualLengthOnPath(); //check value on path = % value (e.g. 0.542)
            QGraphicsPathItem* actualPath = dynamic_cast<Train*>(actor)->getActualPath(); //check actual path saved in train
            int newPathLength = currentPathLength + 10; //speed(temporary)
            float newPathPercentValue = actualPath->path().percentAtLength(newPathLength);
            (newPathPercentValue > 1 ) ? newPathPercentValue = 1 : newPathPercentValue; //temporary - train will continue on the new path/rail track, atc.
            (newPathLength > actualPath->path().length() ) ? newPathLength = actualPath->path().length() : newPathLength;
            QPoint onPathPoint = actualPath->path().pointAtPercent(newPathPercentValue).toPoint() + actualPath->pos().toPoint();
            setActorLocation(onPathPoint,actor); //actualize actor location
            dynamic_cast<Train*>(actor)->setActualPathValue(newPathPercentValue); //actualize new train value on path (rail track)
            dynamic_cast<Train*>(actor)->setActualLengthOnPath(newPathLength);


            //OLD MOVEMENT VERSION
           /*
           float currentPathValue = dynamic_cast<Train*>(actor)->getActualPathValue(); //check value on path = % value (e.g. 0.542)
           QGraphicsPathItem* actualPath = dynamic_cast<Train*>(actor)->getActualPath(); //check actual path saved in train
           float newPathValue = currentPathValue + 0.001; //temporary solution - train need speed!
           (newPathValue > 1 ) ? newPathValue = 1 : newPathValue; //temporary - train will continue on the new path/rail track, atc.
           QPoint onPathPoint = actualPath->path().pointAtPercent(newPathValue).toPoint() + actualPath->pos().toPoint(); //get new scene location        
           setActorLocation(onPathPoint,actor); //actualize actor location
           dynamic_cast<Train*>(actor)->setActualPathValue(newPathValue); //actualize new train value on path (rail track)
            */
       }
        //.....another to actualize?
    }

    if (actualConstructor != nullptr)
    {
       dynamic_cast<ActorConstructor*>(actualConstructor)->actualizeConstructor(worldView->getRelativeFromCursor());
    }
}

void WorldMap::setMap(int xSize, int ySize) //need to refract later!
{
    worldView->setWorldMap(xSize, ySize);
    int mapXside = worldView->getMapSizeX();
    int mapYside = worldView->getMapSizeY();
    worldScene->addLine(-mapXside + 150,-mapYside + 150,- mapXside +150, mapYside - 150, QPen(Qt::red,300)); //-150 OR +150 DUE TO line thickness (half from 300 - pen size)
    worldScene->addLine(-mapXside + 150,mapYside - 150,mapXside - 150,mapYside -150, QPen(Qt::red,300));
    worldScene->addLine(mapXside -150,mapYside -150,mapXside -150,-mapYside +150, QPen(Qt::red,300));
    worldScene->addLine(mapXside -150,-mapYside +150,-mapXside +150,-mapYside +150, QPen(Qt::red,300));
    /*
    IMAGES - NEED ADD THIS OPTION! (image instances?!)
    QPixmap pixmap1("C:/.....");
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap1);
    worldScene->addItem(item);
    */
}

void WorldMap::setActorLocation(QPoint newLocation, Actor* actor)
{
    if (actor)
    {
        actor->setLocation(newLocation);
        int actorIndex = actorListIndexed.indexOf(actor);

        //if (dynamic_cast<Train*>(actor))
        // if (Movable* movableActor = dynamic_cast<Movable*>(actor))

        if (dynamic_cast<Movable*>(actor))
        {
           if (dynamic_cast<Train*>(actor))
           {
                   dynamic_cast<QGraphicsItem*>(graphicsItemListIndexed[actorIndex])->setPos(newLocation);
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
    return railListIndexed[index];
}

Actor* WorldMap::getActorFromList(int index)
{
    return actorListIndexed[index];
}

void WorldMap::deleteAllActors()
{
    for (int i = 0; i < actorListIndexed.size(); i++)
    {
        delete actorListIndexed[i];
    }
    for (int i = 0; i < graphicsItemListIndexed.size(); i++)
    {
        delete graphicsItemListIndexed[i];
    }
    actorListIndexed.clear();
    graphicsItemListIndexed.clear();
}

WorldMap::~WorldMap()
{
    deleteAllActors();
    delete worldScene;
    delete worldView;
    delete worldCollide;
}

void WorldMap::setConstructor(Actor * actor)
{
    actualConstructor = actor;
}

void WorldMap::deleteConstructor(bool deleteCreation)
{
    if (deleteCreation) deleteActor(dynamic_cast<ActorConstructor*>(actualConstructor)->getActorConstructing());
    deleteActor(actualConstructor);
    actualConstructor = nullptr;
}
