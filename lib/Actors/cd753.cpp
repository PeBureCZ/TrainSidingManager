#include "cd753.h"

CD753::CD753(QObject* parent, QGraphicsItem* newGraphicItem) : DieselLocomotive(parent, newGraphicItem)
{
    maxSpeed = 44; //decimeters per tick (1 second) 80km/h = 22,22m/s = 222dm/s
    mass = 72000;
    firstAxleCenter = {15,24}; //relative in decimeters
    secondAxleCenter = {15,144}; //relative in decimeters
    width = 31; //relative in decimeters
    length = 168; //relative in decimeters
}
