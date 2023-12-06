#include "railnavigation.h"

RailNavigation::RailNavigation(Train *trainObject, Rail *destinationRail)
{
    train = trainObject;
    actualRail = train->getActualRail();
}

QVector<Rail *> RailNavigation::makePath()
{
    QVector<Rail*> path = {};
    if (actualRail)
    {

    }
    return path;
}
