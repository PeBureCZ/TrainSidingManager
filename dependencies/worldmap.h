#ifndef WORLDMAP_H
#define WORLDMAP_H

#include "worldviewmap.h"
#include <QPainterPath>
#include <QPen>
#include <QThread>
#include "mainWindow/customqgraphicsview.h"

//BASIC OBJECTS
#include <QGraphicsView>
#include "Actors/actor.h"
#include "spritecolection.h"
#include "worldcollide.h"
#include "railnavigation.h"

//MOVABLE OBJECTS
#include "Actors/actor.h"
#include "Actors/train.h"
#include "Actors/cd730.h"
#include "Actors/signal.h"
#include "Actors/Constructors/signalconstructor.h"
#include "Actors/Constructors/railconstructor.h"
#include "Actors/Constructors/railselector.h"

//STATIC OBJECTS
#include "Actors/rail.h"

class WorldMap : public QObject
{
Q_OBJECT
private:
    CustomQGraphicsView *worldView;
    ActorConstructor* actualConstructor;
    QGraphicsScene *worldScene;
    WorldCollide* worldCollide;

public:
    WorldMap(QObject *parent = nullptr);

    //LISTS
    QVector<Actor*> tickedActorsList;
    QVector<Actor*> actorList; //indexed with graphicsItemList
    QVector<Rail*> railList; //indexed with pathList

    //FCE - BASIC
    void setMap(int xSize, int ySize);
    void addTrainActor(Rail *spawnOnRail);
    void addRailConstructor();
    void addSignalConstructor();
    void addRailSelector();
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
    CustomQGraphicsView* getWorldView();
    QPoint getRelativeWorldPos(QPoint point);
    Rail* getRailFromList(int index);
    Actor* getActorFromList(int index);
    Actor* getActorFromTriggersInCollide(Actor* testedActor, QPoint position, int channel);
    Actor* addRailwaylActor(int indexOfActor, QPoint mapLocation, Actor *connectedRail);
    ActorConstructor *getActualConstructor();
    QVector<Actor *> getActorsCollideInLocation(QVector<int> useBlockChannels, QPoint point);
    QVector<Rail*> findPath(Train* train, Rail* destinationRail);
    WorldCollide* getWorldCollide();
    Trigger *getNearestTriggerInRange(Actor *actor, QPoint position, int radius);
    int getWorldWidth();
    int getWorldHeight();
    int getWorldDistance(QPoint pointOne, QPoint pointTwo);
    int getActorListSize();

    //FCE - TICK
    void actualizeEditor();
    void actualizePlayMode();
    void updateWorld();

    //DESTRUCTOR
    ~WorldMap();

public slots:
    void printMessage();

};

#endif // WORLDMAP_H
