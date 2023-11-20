#include "train.h"

Train::Train(QGraphicsItem* newGraphicItem, Rail* spawnedRail) : Movable(newGraphicItem)
{
    onPathValue = 0;
    onPathLength = 0;
    actualRail = spawnedRail;
    actualPath = dynamic_cast<QGraphicsPathItem*>(dynamic_cast<Actor*>(actualRail)->getGraphicItem());
    vehicles = {}; //list
    vehicleGraphicsItems = {}; //list
    directionToEnd = true;
    trainPath = {};
}

Rail *Train::getActualRail()
{
    return actualRail;
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
    int newMaxSpeed = 0;
    for (auto vehicle : vehicles)
    {
        if (newMaxSpeed < vehicle->getMaxSpeed()) newMaxSpeed = vehicle->getMaxSpeed();
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
    bool stopped = false;
    if (directionToEnd)
    {
        int newOnPathLength = onPathLength + actualSpeed; //speed in centimeters / tick
        float newPathPercentValue;
        do
        {
            newPathPercentValue = actualPath->path().percentAtLength(newOnPathLength/100);
            if (newPathPercentValue == 1)
            {            
                if (trainPath.size() > 1)
                {
                    newOnPathLength -= actualRail->getRailLength()*100;
                    trainPath.remove(0);
                    actualRail = trainPath[0];
                    actualPath = dynamic_cast<QGraphicsPathItem*>(actualRail->getGraphicItem());
                }
                else
                {
                    setActualSpeed(0);
                    break;
                }
            }
        }
        while(newPathPercentValue == 1);
        if (!stopped)
        {
            QPoint onPathPoint = actualPath->path().pointAtPercent(newPathPercentValue).toPoint() + actualPath->pos().toPoint();
            onPathPoint -= dynamic_cast<Vehicle*>(vehicles[0])->axlePos();
            dynamic_cast<QGraphicsItem*>(vehicleGraphicsItems[0])->setPos(onPathPoint); //only index 0 vehicle for now
            onPathValue= newPathPercentValue; //actualize new train value on path (rail track)
            onPathLength = newOnPathLength;
        }

    }
    else
    {
        //reverse
    }



}

void Train::setTrainPath(QVector<Rail *> newTrainPath)
{
    trainPath = newTrainPath;
}
