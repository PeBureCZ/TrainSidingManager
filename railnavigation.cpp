#include "railnavigation.h"

RailNavigation::RailNavigation(Train *trainObject, Rail *destinationRail)
{
    actualRail = train->getActualRail();
    train = trainObject;
}

QVector<Rail *> RailNavigation::makePath()
{
    QVector<Rail*> path = {};
    if (actualRail)
    {

    }
    return path;
}
