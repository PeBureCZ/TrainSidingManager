#include "cd730.h"

CD730::CD730(QGraphicsItem* newGraphicItem) : DieselLocomotive(newGraphicItem)
{
    maxSpeed = 6660; //centimeters per tick
    mass = 70000;
    firstAxleCenter = {152,334}; //relative
    secondAxleDistance = 1000; //relative
    width = 305;
    length = 1334;
}
