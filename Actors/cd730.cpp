#include "cd730.h"

CD730::CD730(QGraphicsItem* newGraphicItem) : DieselLocomotive(newGraphicItem)
{
    maxSpeed = 220000; //centimeters per tick (1 second)
    mass = 70000;
    firstAxleCenter = {152,334}; //relative
    secondAxleDistance = 1000; //relative
    width = 305;
    length = 1334;
}
