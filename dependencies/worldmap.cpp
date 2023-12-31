#include "worldmap.h"
#include <QDebug>


void actualizeActor(Actor* actor) //global function - threated
{
    actor->tickEvent();
}

WorldMap::WorldMap(QObject* parent) : QObject(parent)
{
    worldScene = new QGraphicsScene;
    worldView = new CustomQGraphicsView;
    worldView->setBackgroundBrush(QBrush(Qt::gray));
    worldView->setViewportUpdateMode(QGraphicsView::NoViewportUpdate); //stop update screen automatically
    worldCollide = new WorldCollide;
    actualConstructor = nullptr;
    worldView->setScene(worldScene);
    actorList = {};
    railList = {};
    tickedActorsList = {}; //list of actor with any tick event (animation, move, etc.)
    setMap(25000, 20000); //set map x,y border size
}

CustomQGraphicsView *WorldMap::getWorldView() //return view of scene (QGraphicsView)
{
    return worldView;
}

QString WorldMap::testFunction()
{
    if (railList.size() > 0)
    {
        addTrainActor(dynamic_cast<Rail*>(railList[0]));
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
        newPoint = {static_cast<int>((x-160)*pow(1.25,zoomLevel) + xBarValue),static_cast<int>((y-20)*pow(1.25,zoomLevel) + yBarValue)};
    }
    else if (zoomLevel == 0)
    {
        int xBarValue = xBar->value();
        int yBarValue = yBar->value();
        newPoint = {x-160 + xBarValue,y-20 + yBarValue};
    }
    else
    {
        int xBarValue = xBar->value()*pow(0.8,zoomLevel*-1);
        int yBarValue = yBar->value()*pow(0.8,zoomLevel*-1);
        newPoint = {static_cast<int>((x-160)*pow(0.8,zoomLevel*-1) + xBarValue),static_cast<int>((y-20)*pow(0.8,zoomLevel*-1) + yBarValue)};
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
        Actor* newTrain = new Train(nullptr, trainItem, spawnOnRail);
        addVehicleActor(dynamic_cast<Train*>(newTrain), 1);
        //invisible = not added to scene, only to list (indexed)
        actorList.push_back(newTrain); //indexed with graphicsItemListIndexed
        tickedActorsList.push_back(newTrain); //actor with tick update
        dynamic_cast<Train*>(newTrain)->setActualSpeed(1300); //centimeters/s
        if (railList.size()>1)
        {
            QVector<Rail*> temporaryTrainPath(railList.begin()+1,railList.end()); //will be changed with RailNavigation
            dynamic_cast<Train*>(newTrain)->setTrainPath(temporaryTrainPath);
        }
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
                Vehicle* newVehicle = new CD730(nullptr, vehicleGraphicsItem);
                worldScene->addItem(vehicleGraphicsItem);
                dynamic_cast<Train*>(ownerTrain)->addVehicle(newVehicle, vehicleGraphicsItem); //need for destructor!
                break;
            }
        //case 2: ....
        default: {}
    }
}

void WorldMap::addRailConstructor(QPoint mapLocation, Rail* connectedRail)
{
    Actor* rail = addRailwaylActor(1, mapLocation, connectedRail); //rail created

    //ADD CONSTRUCTOR ACTOR
    SpriteColection newSprite;
    QGraphicsItem* emptyItem = new QGraphicsPixmapItem(newSprite.empty()); //sprite from struct
    Actor* railConstructor = new RailConstructor(nullptr, emptyItem, rail, mapLocation, connectedRail); //add actor
    addActorToLists(railConstructor);
    setConstructor(railConstructor);
}

void WorldMap::addSignalConstructor(QPoint mapLocation)
{
    //ADD GRAPHIC FOR SIGNAL_CONSTRUCTOR
    SpriteColection newSprite;
    QGraphicsItem* signalConstructorGraphic = new QGraphicsPixmapItem(newSprite.redSignal()); //sprite from struct
    worldScene->addItem(signalConstructorGraphic);
    //ADD CONSTRUCTOR ACTOR
    Actor* signalConstructor = new SignalConstructor(nullptr, signalConstructorGraphic, nullptr); //without acttor to construct
    addActorToLists(signalConstructor);
    setConstructor(signalConstructor);
}

void WorldMap::addStaticlActor(QPoint spawnPos, int indexOfActor)
{
    switch (indexOfActor)
    {
        case 1:
        {
           //nothing yet
           break;
        }
        case 2:
        {
           //nothing yet
           break;
        }
        default:{}
        }
}

Actor *WorldMap::addRailwaylActor(int indexOfActor, QPoint mapLocation, Actor* connectedRail) //need to refract later!
{
    switch (indexOfActor)
    {
        case 1:
        {
           //ADD PATH FOR RAIL ACTOR = GRAPHIC ITEM
           QPainterPath path;
           path.cubicTo(0, 0, 0, 0, 0, 0); //deffault line -> will be changed immediately
           QGraphicsPathItem* pathItem = new QGraphicsPathItem(path); //add graphics
           pathItem->setPen(QPen(Qt::blue, 14));
           pathItem->setPos(mapLocation.toPointF());
           worldScene->addItem(pathItem);

           //ADD RAIL ACTOR
           Actor* rail = new Rail(nullptr, pathItem); //add actor
           addActorToLists(rail);
           if (connectedRail != nullptr) dynamic_cast<Rail*>(rail)->setLined(false); // = rail is connected, start as béziere
           rail->setLocation(mapLocation, true);
           return rail;
        }
        case 2:
        {
            //ADD GRAPHIC FOR SIGNAL
            SpriteColection newSprite;
            QGraphicsItem* signalGraphic = new QGraphicsPixmapItem(newSprite.redSignal()); //sprite from struct
            worldScene->addItem(signalGraphic);

            //ADD SIGNAL ACTOR
            Actor* newSignal = new Signal(nullptr, signalGraphic);
            newSignal->setLocation(mapLocation, true);
            newSignal->actualizeGraphicLocation();
            addActorToLists(newSignal);
            qDebug() << "SIGNAL CREATED";
            return newSignal;
        }
        default:{}
    }
}

void WorldMap::addActorToLists(Actor* addedActor)
{
    actorList.push_back(addedActor);
    if (dynamic_cast<Rail*>(addedActor)) railList.push_back(dynamic_cast<Rail*>(addedActor));
}

void WorldMap::deleteActor(Actor *actor)
{
    if (dynamic_cast<Actor*>(actor))
    {
        if (actor->canCollide())
        {
            worldCollide->removeActorFromCollideLists(actor);
        }
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
}

void WorldMap::actualizeEditor()
{
    if (actualConstructor != nullptr)
    {
       dynamic_cast<ActorConstructor*>(actualConstructor)->actualizeConstructor(worldView->getRelativeFromCursor());
    }
}

void WorldMap::actualizePlayMode()
{
    for (auto actor : tickedActorsList)
    {
       QThread *thread = QThread::create(actualizeActor, actor);
       connect(thread, SIGNAL(finished()), thread, SLOT(quit()));
       connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
       //connect(thread, &QThread::destroyed, this, &WorldMap::printMessage);
       thread->start();
    }
}

void WorldMap::updateWorld()
{
    for (auto actor : tickedActorsList)
    {
        actor->actualizeGraphicLocation();
    }
    worldScene->update();
    worldView->update();
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
}

void WorldMap::setActorLocation(QPoint newLocation, Actor* actor)
{
    actor->setLocation(newLocation, true);
    qDebug() << "setActorLoc";
}

Rail* WorldMap::getRailFromList(int index)
{
    return railList[index];
}

Actor* WorldMap::getActorFromList(int index)
{
    if (index < actorList.size()) return actorList[index];
}

int WorldMap::getActorListSize()
{
    return actorList.size();
}

QVector<Actor*> WorldMap::getActorUnderClick(QVector<int> useBlockChannels)
{
    QVector<Actor*> actorsToReturn = {};
    QPoint mousePosition = worldView->getRelativeFromCursor();
    for (auto channel : useBlockChannels)
    {
        switch(channel)
        {
            case 0: //staticChannel
            {
                for (int i = 0; i < worldCollide->getSizeOfStaticChannel(); i++)
                {
                   Actor* testedActor = getActorFromTriggersInCollide(worldCollide->getActorFromTriggerList(channel,i), mousePosition, channel);
                    if (testedActor != nullptr) actorsToReturn.push_back(testedActor);
                }
                break;
            }
            case 1: //trainChannel
            {
                for (int i = 0; i < worldCollide->getSizeOfTrainChannel(); i++)
                {
                    Actor* testedActor = getActorFromTriggersInCollide(worldCollide->getActorFromTriggerList(channel,i), mousePosition, channel);
                    if (testedActor != nullptr) actorsToReturn.push_back(testedActor);
                }
                break;
            }
            case 2: //railChannel
            {
                for (int i = 0; i < worldCollide->getSizeOfRailChannel(); i++)
                {
                    Actor* testedActor = getActorFromTriggersInCollide(worldCollide->getActorFromTriggerList(channel,i), mousePosition, channel);
                    if (testedActor != nullptr) actorsToReturn.push_back(testedActor);
                }
                break;
            }
        }
    }
    return actorsToReturn;
}

Actor *WorldMap::getActorFromTriggersInCollide(Actor *testedActor, QPoint position, int channel)
{
    if (testedActor != nullptr)
    {
        QVector<Trigger*> testedTriggers = testedActor->getAllTriggers();
        for (auto trigger : testedTriggers)
        {
            for (auto usedChannel : trigger->getBlockChannels())
            {
                if (usedChannel != channel) continue;
                if (dynamic_cast<SphereCollider*>(trigger))
                {
                    QPoint relativePosition = testedActor->getLocation() + trigger->getRelativeLocation();
                    int radius = dynamic_cast<SphereCollider*>(trigger)->getRadius();
                    if (getDistance(relativePosition, position) <= radius) return testedActor;
                }
                else if (dynamic_cast<BoxCollider*>(trigger))
                {
                    if (dynamic_cast<BoxCollider*>(trigger)->isInCollision(position - testedActor->getLocation())) return testedActor;
                }
            }
        }
    }
    return nullptr;
}

ActorConstructor *WorldMap::getActualConstructor()
{
    return actualConstructor;
}

Trigger *WorldMap::getNearestTriggerInRange(Actor *actor, QPoint position, int radius)
{
    QVector<Trigger*> testedTriggers = actor->getAllTriggers();
    QPoint actorLocation = actor->getLocation();
    int nearestDistance = radius;
    Trigger* nearestTrigger = {};
    for (auto trigger : testedTriggers)
    {
        int testedDistance = getDistance(actorLocation + trigger->getRelativeLocation(), position);
        if (testedDistance <= nearestDistance)
        {
            nearestTrigger = trigger;
            nearestDistance = testedDistance;
        }
    }
    return nearestTrigger;
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

WorldMap::printMessage()
{
    qDebug() << "message send";
}

void WorldMap::setConstructor(Actor * actor)
{
    actualConstructor = dynamic_cast<ActorConstructor*>(actor);
    tickedActorsList.push_back(actor);
}

void WorldMap:: deleteConstructor(bool deleteCreation) //if deleteCreation = true, delete actor in ActorConstructor too
{
    if (actualConstructor != nullptr && dynamic_cast<ActorConstructor*>(actualConstructor))
    {
        Actor* actorConstructed = dynamic_cast<ActorConstructor*>(actualConstructor)->getActorConstructing();
        if (deleteCreation && actorConstructed != nullptr) deleteActor(actorConstructed);
        deleteActor(actualConstructor);
    }
    actualConstructor = nullptr;
}

QVector<Rail*> WorldMap::findPath(Train *train, Rail* destinationRail)
{
    QVector<Rail*> rails = {};
    RailNavigation navigation(train, destinationRail);
    return rails;
}

int WorldMap::getDistance(QPoint pointOne, QPoint pointTwo)
{
    QLineF line(pointOne, pointTwo);
    return line.length();
}
