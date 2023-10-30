#ifndef WORLDMAP_H
#define WORLDMAP_H

#include <QGraphicsScene>
#include <QGraphicsView>

#include <QPainterPath>
#include <QPen>

#include <QGraphicsRectItem>

class WorldMap
{
public:
    WorldMap();
    QGraphicsView* getWorld();
    void setMap();
    void addRoute(int x, int y);
    void setPath(int startx, int starty, int med1x, int med1y, int med2x, int med2y, int endx, int endy);

private:
    QGraphicsScene *worldScene;
    QGraphicsView *worldView;

};

#endif // WORLDMAP_H
