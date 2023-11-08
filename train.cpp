#include "train.h"

Train::Train(Rail* spawnedRail)
{
    actualPath = {};
    onPathValue = 0;
    actualRail = spawnedRail;
}

void Train::setActualPath(QGraphicsPathItem* newPath)
{
    actualPath = newPath;
}

QGraphicsPathItem* Train::getActualPath()
{
    return actualPath;
}

float Train::getActualPathValue()
{
    return onPathValue;
}

void Train::setActualPathValue(float newValue)
{
    onPathValue = newValue;
}

QPointF Train::getLocationOnPath(float percentOnPath)
{
    return actualPath->path().pointAtPercent(percentOnPath);
}
