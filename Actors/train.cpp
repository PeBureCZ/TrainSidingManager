#include "train.h"

Train::Train(Rail* spawnedRail)
{
    actualPath = {};
    onPathValue = 0;
    onPathLength = 0;
    actualRail = spawnedRail;
    vehicles = {}; //list
    vehicleGraphicsItems = {}; //list
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

void Train::addVehicle(Vehicle *newVehicle, QGraphicsItem* graphicsItem)
{
    vehicles.push_back(newVehicle);
    vehicleGraphicsItems.push_back(graphicsItem);
}

Vehicle *Train::getVehicleActor(int indexOfVehicle)
{
    if (vehicles.length() >= indexOfVehicle)
    {
        return vehicles[indexOfVehicle];
    }
    return nullptr;
}

QGraphicsItem *Train::getVehicleGraphics(int indexOfVehicle)
{
    if (vehicleGraphicsItems.length() >= indexOfVehicle)
    {
        return vehicleGraphicsItems[indexOfVehicle];
    }
    return nullptr;
}

QPoint Train::getVehicleWorldPos(int indexOfVehicle)
{
    //WILL RETURN POS OF VEHICLE BY INDEX
    /*
    int vehicleOnPathLength = onPathLength + 10; //speed(temporary)
    float newPathPercentValue = actualPath->path().percentAtLength(vehicleOnPathLength);
    (newPathPercentValue > 1 ) ? newPathPercentValue = 1 : newPathPercentValue; //temporary - train will continue on the new path/rail track, atc.
    (vehicleOnPathLength > actualPath->path().length() ) ? vehicleOnPathLength = actualPath->path().length() : vehicleOnPathLength;
    QPoint onPathPoint = actualPath->path().pointAtPercent(newPathPercentValue).toPoint() + actualPath->pos().toPoint();
    setActorLocation(onPathPoint,actor); //actualize actor location

    dynamic_cast<Train*>(actor)->setActualPathValue(newPathPercentValue); //actualize new train value on path (rail track)
    dynamic_cast<Train*>(actor)->setActualLengthOnPath(vehicleOnPathLength);
    */
    return location;
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
    for (auto graphicItem : vehicleGraphicsItems)
    {
        delete graphicItem;
    }
}

void Train::moveTrain()
{
    //NEW MOVEMENT VERSION
    int newPathLength = onPathLength + 10; //speed(temporary)
    float newPathPercentValue = actualPath->path().percentAtLength(newPathLength);
    (newPathPercentValue > 1 ) ? newPathPercentValue = 1 : newPathPercentValue; //temporary - train will continue on the new path/rail track, atc.
    (newPathLength > actualPath->path().length() ) ? newPathLength = actualPath->path().length() : newPathLength;
    QPoint onPathPoint = actualPath->path().pointAtPercent(newPathPercentValue).toPoint() + actualPath->pos().toPoint();
    //setActorLocation(onPathPoint,actor); //actualize actor location
    dynamic_cast<QGraphicsItem*>(vehicleGraphicsItems[0])->setPos(onPathPoint); //only index 0 vehicle for now
    onPathValue= newPathPercentValue; //actualize new train value on path (rail track)
    onPathLength = newPathLength;
}
