#include "worldmap.h"

WorldMap::WorldMap()
{
    worldScene = new QGraphicsScene;
    worldView = new QGraphicsView(worldScene);
    zoomLevel = 0;
    actorList = {};
    railList = {};
    setMap();
}

QGraphicsView *WorldMap::getWorld()
{
    return worldView;
}

QString WorldMap::test()
{
    return "actorList[0];";
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

void WorldMap::addPoint(int x, int y)
{
    QGraphicsRectItem *rectItem = worldScene->addRect(-50,-50,100,100,QPen(Qt::blue,3));
    QPoint relativePos = getRelativeWorldPos(x,y);
    rectItem->setPos(relativePos);
}

void WorldMap::addRoute(int startx, int starty, int med1x, int med1y, int med2x, int med2y, int endx, int endy, bool relative)
{
    /*
    add route in absolute coordinate

    https://en.wikipedia.org/wiki/B%C3%A9zier_curve

    startx = start point in scene, x coord. P0          (absolute)
    starty = start point in scene, Y coord. P0          (absolute)

    med1x = 1st point of bézier curve, x coord. (P1)    (relative)
    med1y = 1st point of bézier curve, y coord. (P1)    (relative)
    med2x = 2nd point of bézier curve, x coord. (P2)    (relative)
    med2y = 2nd point of bézier curve, y coord. (P2)    (relative)
    endx = end point of bézier curve, x coord.  (P3)    (relative)
    endy = end point of bézier curve, y coord.  (P3)    (relative)
    */
    QPainterPath path;
    path.cubicTo(med1x,med1y,med2x,med2y,endx,endy);
    QPoint spawnPos;
    QGraphicsPathItem *item = worldScene->addPath(path, QPen(Qt::blue, 144));

    if (relative) spawnPos = getRelativeWorldPos(startx,starty); //transfer to relative (mainWindow)
    else spawnPos = {startx,starty};

    item->setPos(spawnPos);
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

void WorldMap::actualizeMap()
{

}

void WorldMap::createTrain()
{
    DieselLocomotive *train1;
    actorList.push_back(train1);
    //train1->setPixMap(worldScene);
    //train1->setName("xxxy");

}

void WorldMap::moveAllTrains()
{

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

    //set prefered zoom def1 + 15 = 16/20
    for (int i = 0; i < 10; i++) zoomOut();

    //images
    //QPixmap pixmap1("C:/Users/Bureš/Desktop/Dočasné dokumenty/C++/Screenshots/1.jpg");
    //QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap1);
    //worldScene->addItem(item);

    addRoute(0,0,1000,0,1000,1000,0,1000, false);
    addRoute(0,1000,-1000,0,-1000,-1000,0,-1000, false);
    createTrain();
}

void WorldMap::deleteActor()
{

}



