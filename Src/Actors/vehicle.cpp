#include "vehicle.h"


Vehicle::Vehicle(QObject* parent, QGraphicsItem* newGraphicItem) :Movable(parent, newGraphicItem)
{
    mass = 0; //in kg
    firstAxleCenter = {0,0};  //relative in decimeters
    secondAxleDistance = 0;  //relative in decimeters
    width = 0;  //relative in decimeters
    length = 0;  //relative in decimeters
}

QPoint Vehicle::axlePos()
{
    return firstAxleCenter;
}



