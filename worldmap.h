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

//STATIC OBJECTS
#include "rail.h"

class WorldMap
{
public:
    WorldMap();
    CustomQGraphicsView* getWorld();
    QVector<Actor*> actorList;
    QVector<QGraphicsItem*> graphicsItemList;
    QVector<Rail*> railList;
    QVector<QGraphicsPathItem*> pathList;
    QString test();
    QPoint getRelativeWorldPos(QPoint point);
    void setMap(int xSize, int ySize);
    int getWorldWidth();
    int getWorldHeight();
    void actualizeMap();
    void addTrainActor(Rail *spawnOnRail);
    void addRailActor(QPoint point);
    void moveAllTrains();
    void addRailwaylActor(Rail* railActor, int num);
    void addStaticlActor(QPoint spawnPos, int num);
    void deleteAllActors(); //QGraphicsItem* item, QString name
    void setActorLocation(QPoint newLocation, Actor* actor);

    Rail* getRailFromList(int index);
    Actor* getActorFromList(int index);

    ~WorldMap();

private:
    QGraphicsScene *worldScene;
    CustomQGraphicsView *worldView;

};

#endif // WORLDMAP_H
