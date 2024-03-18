#include "worldmap.h"
#include <QDebug>

void actualizeActor(Actor* actor) //global function - threated
{
    actor->threadedTickEvent();
}

WorldMap::WorldMap(QObject* parent, QGraphicsScene* scene, CustomQGraphicsView* view, WorldCollide* collide)
{
    actualConstructor = nullptr;    
    actorList = {};
    railList = {};
    tickedActorsList = {}; //list of actor with any tick event (animation, move, etc.)

    if (scene != nullptr) //inicialize graphic elements
    {
        worldScene = scene;
        worldView = view;
        worldCollide =collide;

        worldView->setScene(worldScene);
        worldView->setBackgroundBrush(QBrush(QColor(BACKGROUND_COLOR)));
        worldView->setViewportUpdateMode(QGraphicsView::NoViewportUpdate); //stop update screen automatically
        setMap(MAX_MAP_SIZE_X, MAX_MAP_SIZE_Y); //set map x,y border size
    }
    else //for example - in unit testing
    {
        worldScene = nullptr;
        worldView = nullptr;
        worldCollide = nullptr;
    }
}

void WorldMap::actualizeEditor()
{
    actualizeConstructorPerTick();
}

void WorldMap::actualizePlayMode()
{
    for (auto actor : tickedActorsList)
    {
        QThread *thread = QThread::create(actualizeActor, actor);
        connect(thread, SIGNAL(finished()), thread, SLOT(quit()));
        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
        thread->start();
    }
}

void WorldMap::updateWorld()
{
    for (auto actor : tickedActorsList)
    {
        actor->actualizeGraphicLocation();
        actor->actualizeGraphicRotation();
        actor->tickEvent();
        /*
        //NOT USED NOW - NOT USEFULL FOR ANYTHING NOW
        if (actor->canCallCollision())
        {
            QVector<int> collideChannels = actor->callCollideChannels();
            QVector<Actor*> actors = getActorsCollideInLocation(collideChannels, worldView->getRelativeFromCursor());
            actor->calledCollisionEvent(actors);
        }
        */
    }
    worldScene->update();
    worldView->update();
}

void WorldMap::actualizeConstructorPerTick()
{
    if (actualConstructor != nullptr)
    {
        actualConstructor->actualizeConstructor(worldView->getRelativeFromCursor(), getWorldView()->getZoomLevel()); //worldView->getZoomLevel
        if (actualConstructor->canCallCollision())
        {
            QVector<int> collideChannels = actualConstructor->callCollideChannels();
            QVector<Actor*> actors = getActorsCollideInLocation(collideChannels, worldView->getRelativeFromCursor());
            actualConstructor->calledCollisionEvent(actors);
        }
    }
}

CustomQGraphicsView *WorldMap::getWorldView() //return view of scene (QGraphicsView)
{
    return worldView;
}

QGraphicsScene *WorldMap::getWorldScene()
{
    return worldScene;
}

QString WorldMap::testFunction()
{
    return "nothing";
}

QPoint WorldMap::getRelativeWorldPos(QPoint point, int xBarValue, int yBarValue, int zoomLevel)
//transfer position from (e.g.) mouse click event in mainwindow (relative to scene) to scene coordination
{
    int x = point.x();
    int y = point.y();
    QPoint newPoint = {0,0};
    if (zoomLevel > 0)
    {
        xBarValue = xBarValue*pow(1.25,zoomLevel);
        yBarValue = yBarValue*pow(1.25,zoomLevel);
        newPoint = {static_cast<int>((x-160)*pow(1.25,zoomLevel) + xBarValue),static_cast<int>((y-20)*pow(1.25,zoomLevel) + yBarValue)};
    }
    else if (zoomLevel == 0)
    {
        newPoint = {x-160 + xBarValue,y-20 + yBarValue};
    }
    else
    {
        xBarValue = xBarValue*pow(0.8,zoomLevel*-1);
        yBarValue = yBarValue*pow(0.8,zoomLevel*-1);
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

QVector<Actor*> WorldMap::getActorsCollideInLocation(QVector<int> useBlockChannels, QPoint point)
{
    QVector<Actor*> actorsToReturn = {};
    for (auto channel : useBlockChannels)
    {
        switch(channel)
        {
            case STATIC_CHANNEL:
            {
                for (int i = 0; i < worldCollide->getSizeOfStaticChannel(); i++)
                {
                   Actor* testedActor = getActorFromTriggersInCollide(worldCollide->getActorFromTriggerList(channel,i), point, channel);
                    if (testedActor != nullptr) actorsToReturn.push_back(testedActor);
                }
                break;
            }
            case TRAIN_CHANNEL:
            {
                for (int i = 0; i < worldCollide->getSizeOfTrainChannel(); i++)
                {
                    Actor* testedActor = getActorFromTriggersInCollide(worldCollide->getActorFromTriggerList(channel,i), point, channel);
                    if (testedActor != nullptr) actorsToReturn.push_back(testedActor);
                }
                break;
            }
            case RAIL_CHANNEL:
            {
                for (int i = 0; i < worldCollide->getSizeOfRailChannel(); i++)
                {
                    Actor* testedActor = getActorFromTriggersInCollide(worldCollide->getActorFromTriggerList(channel,i), point, channel);
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
        QVector<Trigger*> testedTriggers = testedActor->getTriggers();
        for (auto trigger : testedTriggers)
        {
            for (auto usedChannel : trigger->getBlockChannels())
            {
                if (usedChannel != channel) continue;
                if (dynamic_cast<SphereCollider*>(trigger))
                {
                    QPoint relativePosition = testedActor->getLocation() + trigger->getRelativeLocation();
                    int radius = dynamic_cast<SphereCollider*>(trigger)->getRadius();
                    if (getWorldDistance(relativePosition, position) <= radius) return testedActor;
                }
                else if (dynamic_cast<BoxCollider*>(trigger))
                {
                    QPoint transferedPosition = position - testedActor->getLocation();
                    QPoint relativeRotatedPos = testedActor->getRotatedPointArountPivot(transferedPosition, QPoint(0,0), testedActor->getRotation()+trigger->getRelativeRotation());
                    if (dynamic_cast<BoxCollider*>(trigger)->isInCollision(relativeRotatedPos)) return testedActor;
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
    QVector<Trigger*> testedTriggers = actor->getTriggers();
    QPoint actorLocation = actor->getLocation();
    int nearestDistance = radius;
    Trigger* nearestTrigger = nullptr;
    for (auto trigger : testedTriggers)
    {
        int testedDistance = getWorldDistance(actorLocation + trigger->getRelativeLocation(), position);
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

int WorldMap::getWorldDistance(QPoint pointOne, QPoint pointTwo)
{
    QLineF line(pointOne, pointTwo);
    return line.length();
}

WorldMap::~WorldMap()
{
    //constructor have to delete first! (contains a ptr* to a deleted Actor = just "constructed actor")
    if (getActualConstructor() != nullptr) deleteConstructor();

    deleteAllActors();
    delete worldScene;
    delete worldView;
    delete worldCollide;
}
