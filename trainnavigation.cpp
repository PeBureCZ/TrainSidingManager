#include "trainnavigation.h"

TrainNavigation::TrainNavigation(Train *trainObject, Rail *destinationRail)
{
    actualRail = train->getActualRail();
    train = trainObject;
}

QVector<Rail *> TrainNavigation::makePath()
{
    QVector<Rail*> path = {};
    if (actualRail)
    {

    }
    return path;
}
