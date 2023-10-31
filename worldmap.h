#ifndef WORLDMAP_H
#define WORLDMAP_H

#include <QGraphicsScene>
#include "worldviewmap.h"
#include <QPainterPath>
#include <QPen>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QScrollBar>

#define MAX_ZOOM_LEVEL 4 //NEED TO REBUILD - count relative location not work in zoom level >4
#define MIN_ZOOM_LEVEL -10
#define MAP_X_SIZE 2500
#define MAP_Y_SIZE 2000

class WorldMap
{
public:
    WorldMap();
    QGraphicsView* getWorld();

    int zoomLevel;

    int test();
    QPoint getRelativeWorldPos(int x, int y);
    void setMap();
    void addPoint(int x, int y);
    void addRoute(int startx, int starty, int med1x, int med1y, int med2x, int med2y, int endx, int endy);
    int getWorldWidth();
    int getWorldHeight();
    void zoomIn();
    void zoomOut();


private:
    QGraphicsScene *worldScene;
    QGraphicsView *worldView;

};

#endif // WORLDMAP_H
