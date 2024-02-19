#include "cd730.h"

CD730::CD730(QObject* parent, QGraphicsItem* newGraphicItem) : DieselLocomotive(parent, newGraphicItem)
{
    maxSpeed = 222; //decimeters per tick (1 second) 80km/h = 22,22m/s = 222dm/s
    mass = 70000;
    firstAxleCenter = {15,22}; //relative in decimeters
    secondAxleCenter = {15,89}; //relative in decimeters
    width = 30; //relative in decimeters
    length = 133; //relative in decimeters
}
