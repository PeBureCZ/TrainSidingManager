#include "worldmap.h"

WorldMap::WorldMap()
{
    worldScene = new QGraphicsScene;
    worldView = new CustomQGraphicsView;
    worldCollide = new WorldCollide;
    actualConstructor = nullptr;
    worldView->setScene(worldScene);
    actorList = {};
    railList = {};
    tickedActorsList = {}; //list of actor with any tick event (animation, move, etc.)
    setMap(250000, 200000); //set map x,y border size
}

CustomQGraphicsView *WorldMap::getWorld() //return view of scene (QGraphicsView)
{
    return worldView;
}

QString WorldMap::testFunction()
{
    if (railList.size() > 0)
    {
        addTrainActor(dynamic_cast<Rail*>(railList[0]));
    }
    else
    {
    }
    return "nothing";
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
    if (railList.size() > 0)
    {
        SpriteColection newSprite; //struct
        QGraphicsItem* trainItem = new QGraphicsPixmapItem(newSprite.empty()); //sprite from struct
        Actor* newTrain = new Train(trainItem, spawnOnRail);
        addVehicleActor(dynamic_cast<Train*>(newTrain), 1);
        //invisible = not added to scene, only to list (indexed)
        actorList.push_back(newTrain); //indexed with graphicsItemListIndexed
        tickedActorsList.push_back(newTrain); //actor with tick update
        dynamic_cast<Train*>(newTrain)->setActualSpeed(80);
    }
}

void WorldMap::addVehicleActor(Train *ownerTrain, int indexOfVehicle)
{
    switch (indexOfVehicle)
    {
        case 1:
            {
                SpriteColection newSprite; //struct
                QGraphicsItem* vehicleGraphicsItem = new QGraphicsPixmapItem(newSprite.cd730()); //sprite from struct
                Vehicle* newVehicle = new CD730(vehicleGraphicsItem);
                worldScene->addItem(vehicleGraphicsItem);
                dynamic_cast<Train*>(ownerTrain)->addVehicle(newVehicle, vehicleGraphicsItem); //need for destructor!
                break;
            }
        //case 2: ....
        default: {}
    }
}

void WorldMap::addRailConstructor(QPoint point)
{
    //ADD PATH FOR RAIL ACTOR
    QPainterPath path;
    path.cubicTo(10000, 0, 10000, 10000, 0, 10000); //deffault line -> will be changed immediately
    QGraphicsPathItem* pathItem = new QGraphicsPathItem(path); //add graphics
    pathItem->setPen(QPen(Qt::blue, 144));
    QPoint relativePos = getRelativeWorldPos(point);
    pathItem->setPos(relativePos.toPointF());
    worldScene->addItem(pathItem);

    //ADD RAIL ACTOR
    Actor* rail = new Rail(pathItem); //add actor
    //rail->enableCollision(worldCollide);
    QVector<int>collideChannels = {2};
    rail->addTriggerComponent({0,0},0.0f,0,collideChannels); //add collision trigger at relative loc 0,0, with rotation 0, type 0, with collide channel 2
    addActorToLists(rail);
    rail->setLocation(point);

    //ADD CONSTRUCTOR ACTOR
    SpriteColection newSprite;
    QGraphicsItem* emptyItem = new QGraphicsPixmapItem(newSprite.empty()); //sprite from struct
    Actor* railConstructor = new RailConstructor(emptyItem, rail, relativePos, nullptr, 0); //add actor
    addActorToLists(railConstructor);
    setConstructor(railConstructor);
}

void WorldMap::addStaticlActor(QPoint spawnPos, int indexOfActor)
{
    switch (indexOfActor)
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

void WorldMap::addRailwaylActor(Rail* railActor, int indexOfActor) //need to refract later!
{
    switch (indexOfActor)
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

void WorldMap::addActorToLists(Actor* addedActor)
{
    actorList.push_back(addedActor);
    if (dynamic_cast<Rail*>(addedActor)) railList.push_back(dynamic_cast<Rail*>(addedActor));
}

void WorldMap::deleteActor(Actor *actor)
{
    if (tickedActorsList.contains(actor)) tickedActorsList.remove(tickedActorsList.indexOf(actor));

    if (dynamic_cast<Rail*>(actor))
    {
       int railIndex = railList.indexOf(dynamic_cast<Rail*>(actor));
       railList.remove(railIndex); //actor will be deleted from actor List
    }
    int actorIndex = actorList.indexOf(actor);
    delete actorList[actorIndex];
    actorList.remove(actorIndex);
}

void WorldMap::actualizeAllInWorld() //need to refract later! -> only moving actors!
{
    for (auto actor : tickedActorsList)
    {
       if (dynamic_cast<Train*>(actor))
       {
               dynamic_cast<Train*>(actor)->moveTrain(); //move all vehicles in train
       }
        //.....another to actualize?
    }

    if (actualConstructor != nullptr)
    {
       dynamic_cast<ActorConstructor*>(actualConstructor)->actualizeConstructor(worldView->getRelativeFromCursor());
    }
}

void WorldMap::setMap(int xSize, int ySize)
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
        int actorIndex = actorList.indexOf(actor);

        if (dynamic_cast<Movable*>(actor))
        {
           if (dynamic_cast<Train*>(actor))
           {
           //exceoption - train has not visible graphic
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

Actor *WorldMap::getActorUnderClick(QVector<int> useChannels)
{
    Actor* actorInRadius = nullptr;
    QPoint mousePosition = worldView->getRelativeFromCursor();
    //int zoom = worldView->getZoomLevel();
    int maxRadius = 5000; // * zoom;
    for (auto channel : useChannels)
    {
        switch(channel)
        {
            case 0: //staticChannel
            {
                for (int i = 0; i < worldCollide->getSizeOfStaticChannel(); i++)
                {
                    worldCollide->getTrigger(channel,i);
                }
                break;
            }
            case 1: //trainChannel
            {
                for (int i = 0; i < worldCollide->getSizeOfTrainChannel(); i++)
                {
                    worldCollide->getTrigger(channel,i);
                }
                break;
            }
            case 2: //railChannel
            {
                for (int i = 0; i < worldCollide->getSizeOfRailChannel(); i++)
                {
                    worldCollide->getTrigger(channel,i);
                }
                break;
            }
        }
        //QLineF line(actor->getLocation(), mousePosition);
        //if (line.length() < nearestDistance) actorInRadius = actor;
    }
    return actorInRadius;
}

WorldCollide *WorldMap::getWorldCollide()
{
    return worldCollide;
}

void WorldMap::deleteAllActors()
{  
    while (actorList.size() > 0)
    {
        deleteActor(actorList[0]);
    }
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
    tickedActorsList.push_back(actor);
}

void WorldMap::deleteConstructor(bool deleteCreation) //if deleteCreation = true, delete actor in ActorConstructor too
{
    if (deleteCreation) deleteActor(dynamic_cast<ActorConstructor*>(actualConstructor)->getActorConstructing());
    deleteActor(actualConstructor);
    actualConstructor = nullptr;
}
