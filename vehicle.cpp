#include "vehicle.h"


Vehicle::Vehicle()
{
    path = {};
}

void Vehicle::addPath(QGraphicsPathItem* pathItem)
{
    path = pathItem;
}

void Vehicle::movePath(float startPercent)
{

}

