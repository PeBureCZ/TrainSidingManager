#include "worldmap.h"

WorldMap::WorldMap()
{
    worldScene = new QGraphicsScene;
    worldView = new QGraphicsView(worldScene);

    setMap();

}

QGraphicsView *WorldMap::getWorld()
{
    return worldView;
}

void WorldMap::setMap()
{
    //nothing yet
}

void WorldMap::addRoute(int x, int y)
{
    QGraphicsRectItem *rectItem = worldScene->addRect(-5,-5,10,10,QPen(Qt::blue,3));
    rectItem->setPos(x,y);
    //worldScene->addPath(path)
}

void WorldMap::setPath(int startx, int starty, int med1x, int med1y, int med2x, int med2y, int endx, int endy)
{

}

