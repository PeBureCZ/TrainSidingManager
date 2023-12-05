#include "vehicle.h"


Vehicle::Vehicle(QObject* parent, QGraphicsItem* newGraphicItem) :Movable(parent, newGraphicItem)
{
    mass = 0;
    firstAxleCenter = {0,0};
    secondAxleDistance = 0;
    width = 0;
    length = 0;
}

QPoint Vehicle::axlePos()
{
    return firstAxleCenter;
}



