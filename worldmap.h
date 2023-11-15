#ifndef WORLDMAP_H
#define WORLDMAP_H

#include "worldviewmap.h"
#include <QPainterPath>
#include <QPen>

#include <customqgraphicsview.h>

//BASIC OBJECTS
#include <QGraphicsView>
#include "Actors/actor.h"
#include "spritecolection.h"
#include "worldcollide.h"

//MOVABLE OBJECTS
#include "Actors/actor.h"
#include "Actors/train.h"
#include "Actors/cd730.h"
#include "Actors/railconstructor.h"

//STATIC OBJECTS
#include "Actors/rail.h"

class WorldMap
{
public:
    WorldMap();

    //LISTS
    QVector<Actor*> tickedActorsList;
    QVector<Actor*> actorList; //indexed with graphicsItemList
    QVector<Rail*> railList; //indexed with pathList

    //FCE - BASIC
    void setMap(int xSize, int ySize);
    void addTrainActor(Rail *spawnOnRail);
    void addRailConstructor(QPoint mapLocation, Rail *connectedRail);
    void addRailwaylActor(Rail* railActor, int indexOfActor);
    void addStaticlActor(QPoint spawnPos, int indexOfActor);
    void addVehicleActor(Train* ownerTrain, int indexOfVehicle);
    void deleteAllActors(); //QGraphicsItem* item, QString name
    void setActorLocation(QPoint newLocation, Actor* actor);
    void addActorToLists(Actor *addedActor);
    void deleteActor(Actor* actor);
    void setConstructor(Actor*actor);
    void deleteConstructor(bool deleteCreation);

    //FCE - RETURN
    QString testFunction();
    CustomQGraphicsView* getWorld();
    QPoint getRelativeWorldPos(QPoint point);
    Rail* getRailFromList(int index);
    Actor* getActorFromList(int index);
    Actor* checkTriggersInRange(Actor* testedActor, QPoint position, int radius);
    Actor *getActualConstructor();
    QVector<Actor *> getActorUnderClick(QVector<int> useBlockChannels, int radius);
    WorldCollide* getWorldCollide();
    Trigger *getTriggerInRange(Actor *actor, QPoint position, int radius);
    int getWorldWidth();
    int getWorldHeight();
    int getDistance(QPoint pointOne, QPoint pointTwo);

    //FCE - TICK
    void actualizeAllInWorld();

    //DESTRUCTOR
    ~WorldMap();
private:
    CustomQGraphicsView *worldView;
    Actor* actualConstructor;
    QGraphicsScene *worldScene;
    WorldCollide* worldCollide;
};

#endif // WORLDMAP_H
