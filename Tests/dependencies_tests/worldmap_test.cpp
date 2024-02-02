#include "worldmap_test.h"

WorldMap_test::WorldMap_test(QObject *parent)
    : QObject{parent}
{
}

void WorldMap_test::getRelativeWorldPos_test()
{
    WorldMap world;
    QVERIFY(world.getRelativeWorldPos(QPoint(0,0), 0, 0, 0) == QPoint(-160,-20));
    QVERIFY(world.getRelativeWorldPos(QPoint(10,0), 0, 0, 10) == QPoint(-1396,-186));
    QVERIFY(world.getRelativeWorldPos(QPoint(-100,0), 50, 50, -1) == QPoint(-168,24));
    QVERIFY(world.getRelativeWorldPos(QPoint(0,-100), 10, 10, 10) == QPoint(-1397,-1024));
    QVERIFY(world.getRelativeWorldPos(QPoint(0,0), -10, 0, 10) == QPoint(-1583,-186));
    QVERIFY(world.getRelativeWorldPos(QPoint(10,0), 0, -10, 10) == QPoint(-1396,-279));
}
