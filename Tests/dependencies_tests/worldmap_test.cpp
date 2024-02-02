#include "worldmap_test.h"


#include  <QGraphicsScene>
#include "dependencies/worldcollide.h"
#include "mainWindow/customqgraphicsview.h"

WorldMap_test::WorldMap_test(QObject *parent)
    : QObject{parent}
{

}

void WorldMap_test::getRelativeWorldPos_test()
{
    qDebug() << "1";
    //QGraphicsScene myScene;
    //WorldMap* world = new WorldMap(nullptr, new QGraphicsScene, new CustomQGraphicsView, new WorldCollide);
    qDebug() << "2";
    //qDebug() << world.getRelativeWorldPos(QPoint(0,0), 0, 0);
    QVERIFY(true == true);
    //delete world;
}

/*
    int zoomLevel = worldView->getZoomLevel();
    int x = point.x();
    int y = point.y();
    QScrollBar* xBar = worldView->horizontalScrollBar();
    QScrollBar* yBar = worldView->verticalScrollBar();
    QPoint newPoint = {0,0};
    if (zoomLevel > 0)
    {
        int xBarValue = xBar->value()*pow(1.25,zoomLevel);
        int yBarValue = yBar->value()*pow(1.25,zoomLevel);
        newPoint = {static_cast<int>((x-160)*pow(1.25,zoomLevel) + xBarValue),static_cast<int>((y-20)*pow(1.25,zoomLevel) + yBarValue)};
    }
    else if (zoomLevel == 0)
    {
        int xBarValue = xBar->value();
        int yBarValue = yBar->value();
        newPoint = {x-160 + xBarValue,y-20 + yBarValue};
    }
    else
    {
        int xBarValue = xBar->value()*pow(0.8,zoomLevel*-1);
        int yBarValue = yBar->value()*pow(0.8,zoomLevel*-1);
        newPoint = {static_cast<int>((x-160)*pow(0.8,zoomLevel*-1) + xBarValue),static_cast<int>((y-20)*pow(0.8,zoomLevel*-1) + yBarValue)};
    }
    return newPoint;
 */
