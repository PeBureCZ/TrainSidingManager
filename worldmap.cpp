#include "worldmap.h"

WorldMap::WorldMap()
{
    worldScene = new QGraphicsScene;
    worldView = new QGraphicsView(worldScene);
    zoomLevel = 0;
    actorList = {};
    graphicsItemList = {};
    //railList = {};
    setMap();
}

QGraphicsView *WorldMap::getWorld()
{
    return worldView;

}

QString WorldMap::test()
{
    return "";
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
        point = {static_cast<int>((x-100)*pow(1.25,zoomLevel) + xBarValue),static_cast<int>((y-20)*pow(1.25,zoomLevel) + yBarValue)};
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
        point = {static_cast<int>((x-100)*pow(0.8,zoomLevel*-1) + xBarValue),static_cast<int>((y-20)*pow(0.8,zoomLevel*-1) + yBarValue)};
    }
    return point;
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
    /*
    DieselLocomotive* train1 = new DieselLocomotive;
    actorList.push_back(train1);
    DieselLocomotive* x = actorList.last();
    x->setName("train: " + QString::number(x->count));
    */
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

    //addRoute(0,0,10000,0,10000,10000,0,10000, false);
    //addRoute(0,10000,-10000,0,-10000,-10000,0,-10000, false);
}

void WorldMap::addActor(int num, QPoint spawnPos)
{
    switch (num)
    {
    case 1:
        {
           Actor* rail = new Rail;
           actorList.push_back(rail);

           QPainterPath path;
           path.cubicTo(10000, 0, 10000, 10000, 0, 10000);

           QGraphicsPathItem* railItem = new QGraphicsPathItem(path);
           railItem->setPen(QPen(Qt::blue, 144));
           QPoint relativePos = getRelativeWorldPos(spawnPos.x(), spawnPos.y());
           railItem->setPos(relativePos);
           worldScene->addItem(railItem);
           graphicsItemList.push_back(railItem);
           break;
        }
    case 2:
        {
           Actor* train = new DieselLocomotive;
           actorList.push_back(train);

           QPixmap pixmap("C:/QT_Projects/TrainSidingManager/loco.png");
           QGraphicsItem* trainItem = new QGraphicsPixmapItem(pixmap);
           trainItem->setPos(spawnPos);
           worldScene->addItem(trainItem);
           graphicsItemList.push_back(trainItem);
           break;
        }
    default:
        {}
    }
}

void WorldMap::deleteAllActors()  //QGraphicsItem* item, QString name
{
    for (int i = 0; i < actorList.size(); i++)
    {
       delete actorList[i];
    }
    for (int i = 0; i < graphicsItemList.size(); i++)
    {
       delete graphicsItemList[i];
    }
    actorList.clear();
    graphicsItemList.clear();
}

WorldMap::~WorldMap()
{
    delete worldScene;
    delete worldView;
    deleteAllActors();
}



