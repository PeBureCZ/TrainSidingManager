#include "cd730.h"

CD730::CD730(QObject* parent, QGraphicsItem* newGraphicItem) : DieselLocomotive(parent, newGraphicItem)
{
    maxSpeed = 2222; //centimeters per tick (1 second) 80km/h = 22,22m/s = 2222cm/s
    mass = 70000;
    firstAxleCenter = {15,22}; //relative in decimeters
    secondAxleDistance = 89; //relative in decimeters
    width = 30; //relative in decimeters
    length = 133; //relative in decimeters
}
