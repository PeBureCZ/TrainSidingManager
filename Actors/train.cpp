#include "train.h"

Train::Train(Rail* spawnedRail)
{
    actualPath = {};
    onPathValue = 0;
    onPathLength = 0;
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

int Train::getActualLengthOnPath()
{
    return onPathLength;
}

void Train::setActualLengthOnPath(int newValue)
{
    onPathLength = newValue;
}

void Train::addVehicle(Vehicle *newVehicle)
{
    vehicles.push_back(newVehicle);
}

QPointF Train::getLocationOnPath(float percentOnPath)
{
    return actualPath->path().pointAtPercent(percentOnPath);
}

Train::~Train()
{
    for (auto vehicle : vehicles)
    {
        delete vehicle;
    }
}
