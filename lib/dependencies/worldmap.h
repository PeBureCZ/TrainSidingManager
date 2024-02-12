#ifndef WORLDMAP_H
#define WORLDMAP_H

#include "worldviewmap.h"
#include <QPainterPath>
#include <QPen>
#include <QThread>
#include "mwComponents/customqgraphicsview.h"

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
#include "Actors/Vagons/eas.h"
#include "Actors/signal.h"
#include "Actors/Constructors/signalconstructor.h"
#include "Actors/Constructors/railconstructor.h"
#include "Actors/Constructors/railselector.h"
#include "Actors/Constructors/portalconstructor.h"

//STATIC OBJECTS
#include "Actors/rail.h"

//ENUMS
#include "Enums/TrainsEnum.h"
#include "Enums/BlockChannels.h"
#include "Enums/ActorsEnum.h"

class LIB_EXPORT WorldMap : public QObject
{
Q_OBJECT
private:
    CustomQGraphicsView *worldView;
    ActorConstructor* actualConstructor;
    QGraphicsScene *worldScene;
    WorldCollide* worldCollide;

    //WorldActorLogic.cpp
    void addActorToLists(Actor *addedActor);

    //constructors
    Actor* addRailConstructor();
    Actor* addSignalConstructor();
    Actor* addPortalConstructor();

    //selectors
    Actor* addRailSelector();

    //specific-actors
    Actor* addTrain(Rail *spawnOnRail);
    Actor* addRail(QPoint point);
    Actor* addPortal(QPoint point);
    Actor* addSignal(QPoint point);

    //multi-type actor switch
    Actor* addStaticlActor(QPoint spawnPos, int indexOfActor);
    void *addVehicleActor(Train* ownerTrain, int indexOfVehicle);

public:
    WorldMap(QObject *parent = nullptr
            , QGraphicsScene* scene = nullptr
            , CustomQGraphicsView* view = nullptr
            , WorldCollide* collide = nullptr);

    //LISTS
    QVector<Actor*> tickedActorsList;
    QVector<Actor*> actorList;
    QVector<Rail*> railList;

    //FCE - BASIC
    void setMap(int xSize, int ySize);

    //WorldActorLogic.cpp
    Actor* addActor(int indexOfActor);
    void deleteAllActors(); //QGraphicsItem* item, QString name
    void setActorLocation(QPoint newLocation, Actor* actor);
    void deleteActor(Actor* actor);
    void setConstructor(Actor*actor);
    void deleteConstructor(bool deleteCreation);

    //FCE - RETURN
    QString testFunction();
    CustomQGraphicsView* getWorldView();
    QGraphicsScene* getWorldScene();
    QPoint getRelativeWorldPos(QPoint point, int xBarValue, int yBarValue, int zoomLevel);
    Rail* getRailFromList(int index);
    Actor* getActorFromList(int index);
    Actor* getActorFromTriggersInCollide(Actor* testedActor, QPoint position, int channel);
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

    //DESTRUCTORs
    ~WorldMap();

public slots:

};

#endif // WORLDMAP_H
