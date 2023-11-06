#ifndef WORLDMAP_H
#define WORLDMAP_H

#include <QGraphicsScene>
#include "worldviewmap.h"
#include <QPainterPath>
#include <QPen>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QScrollBar>
#include <QVector>
#include <QApplication>


#include "actor.h"

//MOVABLE OBJECTS
//#include "movable.h"
#include "train.h"
#include "diesellocomotive.h"

//STATIC OBJECTS
#include "rail.h"

#define MAX_ZOOM_LEVEL 20 //NEED TO REBUILD - count relative location not work in zoom level >4
#define MIN_ZOOM_LEVEL -10
#define MAP_X_SIZE 250000
#define MAP_Y_SIZE 200000

class WorldMap
{
public:
    WorldMap();

    QGraphicsView* getWorld();

    int zoomLevel;
    QVector<Actor*> actorList;

    QVector<QGraphicsItem*> graphicsItemList;

    QVector<Rail*> railList;
    QVector<QGraphicsPathItem*> pathList;


    QString test();
    QPoint getRelativeWorldPos(QPoint point);
    QPoint getAbsoluteWorldPos(QPoint point);
    void setMap();
    int getWorldWidth();
    int getWorldHeight();
    void zoomIn();
    void zoomOut();
    void actualizeMap();
    void createTrain();
    void moveAllTrains();
    void addActor(QPoint spawnPos, int num);
    void deleteAllActors(); //QGraphicsItem* item, QString name
    void setActorLocation(QPoint newLocation, Actor* actor);
    ~WorldMap();

private:
    QGraphicsScene *worldScene;
    QGraphicsView *worldView;

};

#endif // WORLDMAP_H
