#include "worldmap.h"

WorldMap::WorldMap()
{
    worldScene = new QGraphicsScene;
    worldView = new QGraphicsView(worldScene);
    zoomLevel = 0;
    setMap();
}

QGraphicsView *WorldMap::getWorld()
{
    return worldView;
}

int WorldMap::test() //return left left corner +100 +100
{
    QScrollBar* xBar = worldView->horizontalScrollBar();
    QScrollBar* yBar = worldView->verticalScrollBar();
    int xBarValue = xBar->value();
    int yBarValue = yBar->value();
    return yBarValue;
}

QPoint WorldMap::getRelativeWorldPos(int x, int y) //NEED TO REBUILD -100/-20 => map window (layout) in mainwindow
{
    QScrollBar* xBar = worldView->horizontalScrollBar();
    QScrollBar* yBar = worldView->verticalScrollBar();
    QPoint point = {0,0};
    if (zoomLevel > 0)
    {
        int xBarValue = xBar->value()*pow(1.25,zoomLevel);
        int yBarValue = yBar->value()*pow(1.25,zoomLevel);
        point = {(x-100)*pow(1.25,zoomLevel) + xBarValue,(y-20)*pow(1.25,zoomLevel) + yBarValue};
    }
    else if (zoomLevel == 0)
    {
        int xBarValue = xBar->value();
        int yBarValue = yBar->value();
        point = {x-100 + xBarValue,y-20 + yBarValue};
    }
    else
    {
        int xBarValue = xBar->value()*pow(0.8,zoomLevel*-1);
        int yBarValue = yBar->value()*pow(0.8,zoomLevel*-1);
        point = {(x-100)*pow(0.8,zoomLevel*-1) + xBarValue,(y-20)*pow(0.8,zoomLevel*-1) + yBarValue};
    }
    return point;
}



void WorldMap::setMap()
{
    //set world border and world size
    int mapXside = MAP_X_SIZE/2;
    int mapYside = MAP_Y_SIZE/2;
    worldScene->addLine(-mapXside + 15,-mapYside + 15,- mapXside +15, mapYside - 15, QPen(Qt::red,30)); //-15 OR +15 DUE TO line thickness
    worldScene->addLine(-mapXside + 15,mapYside - 15,mapXside - 15,mapYside -15, QPen(Qt::red,30));
    worldScene->addLine(mapXside -15,mapYside -15,mapXside -15,-mapYside +15, QPen(Qt::red,30));
    worldScene->addLine(mapXside -15,-mapYside +15,-mapXside +15,-mapYside +15, QPen(Qt::red,30));
}

void WorldMap::addPoint(int x, int y)
{
    QGraphicsRectItem *rectItem = worldScene->addRect(-5,-5,10,10,QPen(Qt::blue,3));
    QPoint relativePos = getRelativeWorldPos(x,y);
    rectItem->setPos(relativePos);
}

void WorldMap::addRoute(int startx, int starty, int med1x, int med1y, int med2x, int med2y, int endx, int endy)
{
    QPainterPath path;
    path.cubicTo(med1x,med1y,med2x,med2y,endx,endy);

    QGraphicsPathItem *item = worldScene->addPath(path, QPen(Qt::blue, 5));
    QPoint relativePos = getRelativeWorldPos(startx,starty);
    item->setPos(relativePos);
}

int WorldMap::getWorldWidth()
{
    return worldScene->width();
}

int WorldMap::getWorldHeight()
{
    return worldScene->height();
}

void WorldMap::zoomIn()
{
    if (zoomLevel > MIN_ZOOM_LEVEL)
    {
       worldView->scale(1.25,1.25);
       zoomLevel--;

    }
}

void WorldMap::zoomOut()
{
    if (zoomLevel < MAX_ZOOM_LEVEL)
    {
       worldView->scale(0.8,0.8);
       zoomLevel++;
    }
}

