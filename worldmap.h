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
#include <QDir>

#include "diesellocomotive.h"
#include "rail.h"
#include "actor.h"

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
    QVector<Actor> actorList;
    QVector<QGraphicsPixmapItem*> pixmapList;
    QVector<Rail> railList;

    QString test();
    QPoint getRelativeWorldPos(int x, int y);
    void setMap();
    void addPoint(int x, int y);
    void addRoute(int startx, int starty, int med1x, int med1y, int med2x, int med2y, int endx, int endy, bool relative);
    int getWorldWidth();
    int getWorldHeight();
    void zoomIn();
    void zoomOut();
    void actualizeMap();
    void createTrain();
    void moveAllTrains();
    void deleteActor();


private:
    QGraphicsScene *worldScene;
    QGraphicsView *worldView;

};

#endif // WORLDMAP_H
