#ifndef WORLDMAP_H
#define WORLDMAP_H


#include "worldviewmap.h"
#include <QPainterPath>
#include <QPen>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QVector>
#include <QApplication>

#include <customqgraphicsview.h>
#include "actor.h"

//MOVABLE OBJECTS
//#include "movable.h"
#include "train.h"
#include "diesellocomotive.h"
#include "railconstructor.h"

//STATIC OBJECTS
#include "rail.h"

class WorldMap
{
public:
    WorldMap();

    //VARIABLES

    QGraphicsScene *worldScene;

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
    void deleteAllActors(); //QGraphicsItem* item, QString name
    void setActorLocation(QPoint newLocation, Actor* actor);
    void addActorToLists(Actor *addedActor, QGraphicsItem *graphicsItem);
    void addRailToLists(Rail *addedRailActor, QGraphicsPathItem *addedPath);

    //DESTRUCTOR
    ~WorldMap();

private:
    CustomQGraphicsView *worldView;

};

#endif // WORLDMAP_H
