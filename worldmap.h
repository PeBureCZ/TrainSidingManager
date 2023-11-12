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
//#include "movable.h"
#include "Actors/train.h"
#include "Actors/cd730.h"
#include "Actors/railconstructor.h"

//STATIC OBJECTS
#include "Actors/rail.h"

class WorldMap
{
public:
    WorldMap();

    //BASIC OBJECTS
    Actor* actualConstructor;
    QGraphicsScene *worldScene;
    WorldCollide* worldCollide;

    //LISTS
    QVector<Actor*> tickedActorsList;

    QVector<Actor*> actorListIndexed; //indexed with graphicsItemList
    QVector<QGraphicsItem*> graphicsItemListIndexed; //indexed with actorList

    QVector<Rail*> railListIndexed; //indexed with pathList
    QVector<QGraphicsPathItem*> pathListIndexed; //indexed with railList

    //FCE - return
    QString test();
    CustomQGraphicsView* getWorld();
    QPoint getRelativeWorldPos(QPoint point);
    Rail* getRailFromList(int index);
    Actor* getActorFromList(int index);
    int getWorldWidth();
    int getWorldHeight();

    //FCE - TICK
    void actualizeAllInWorld();

    //FCE - BASIC
    void setMap(int xSize, int ySize);
    void addTrainActor(Rail *spawnOnRail);
    void addRailConstructor(QPoint point);
    //void addRailActor(QPoint point);
    void addRailwaylActor(Rail* railActor, int num);
    void addStaticlActor(QPoint spawnPos, int num);
    void addVehicleActor(Train* ownerTrain, int num);
    void deleteAllActors(); //QGraphicsItem* item, QString name
    void setActorLocation(QPoint newLocation, Actor* actor);
    void addActorToLists(Actor *addedActor, QGraphicsItem *graphicsItem);
    void addRailToLists(Rail *addedRailActor, QGraphicsPathItem *addedPath);
    void deleteActor(Actor* actor);
    void setConstructor(Actor*actor);
    void deleteConstructor(bool deleteCreation);

    //DESTRUCTOR
    ~WorldMap();

private:
    CustomQGraphicsView *worldView;

};

#endif // WORLDMAP_H
