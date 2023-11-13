#include "train.h"

Train::Train(QGraphicsItem* newGraphicItem, Rail* spawnedRail) : Movable(newGraphicItem)
{
    onPathValue = 0;
    onPathLength = 0;
    actualRail = spawnedRail;
    actualPath = dynamic_cast<QGraphicsPathItem*>(dynamic_cast<Actor*>(actualRail)->getGraphicItem());
    vehicles = {}; //list
    vehicleGraphicsItems = {}; //list
}

float Train::getActualPathValue()
{
    return onPathValue;
}

void Train::setActualPathValue(float newValue)
{
    onPathValue = newValue;
}

void Train::addVehicle(Vehicle *newVehicle, QGraphicsItem* graphicsItem)
{
    vehicles.push_back(newVehicle);
    vehicleGraphicsItems.push_back(graphicsItem);
    actualizeMaxSpeed();
}

void Train::actualizeMaxSpeed()
{
    int newMaxSpeed = 99999;
    for (auto vehicle : vehicles)
    {
        if (newMaxSpeed > vehicle->getMaxSpeed()) newMaxSpeed = vehicle->getMaxSpeed();
    }
    maxSpeed = newMaxSpeed;
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

void Train::moveTrain()
{
    //NEW MOVEMENT VERSION
    int newOnPathLength = onPathLength + actualSpeed; //speed in centimeters / tick
    float newPathPercentValue = actualPath->path().percentAtLength(newOnPathLength/100);
    (newPathPercentValue > 1 ) ? newPathPercentValue = 1 : newPathPercentValue; //temporary - train will continue on the new path/rail track, atc.
    (newOnPathLength > actualPath->path().length()*100) ? newOnPathLength = actualPath->path().length()*100 : newOnPathLength;
    QPoint onPathPoint = actualPath->path().pointAtPercent(newPathPercentValue).toPoint() + actualPath->pos().toPoint();
    onPathPoint -= dynamic_cast<Vehicle*>(vehicles[0])->axlePos();
    dynamic_cast<QGraphicsItem*>(vehicleGraphicsItems[0])->setPos(onPathPoint); //only index 0 vehicle for now
    onPathValue= newPathPercentValue; //actualize new train value on path (rail track)
    onPathLength = newOnPathLength;
}
