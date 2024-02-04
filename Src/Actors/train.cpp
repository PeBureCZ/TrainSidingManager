#include "train.h"

Train::Train(QObject* parent, QGraphicsItem* newGraphicItem, Rail* spawnedRail) : Movable(parent, newGraphicItem)
{
    onPathValue = 0;
    onPathLength = 0;
    actualRail = spawnedRail;
    vehicles = {}; //list
    vehicleGraphicsItems = {}; //list
    directionToEnd = true;
    trainPath = {};
    setActualPathGraphic(actualRail);
}

void Train::actualizeGraphicLocation()
{
    //this function is called from worldmap (class) with function "updateWorld"
    //location (graphicLocation variable) is changed in QThreads and have to be visually changed in main thread
    dynamic_cast<QGraphicsItem*>(vehicleGraphicsItems[0])->setPos(graphicLocation); //only index 0 vehicle for now
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
    //It will recalculate the maximum speed based on the train's weight...

    if (vehicles.size() == 0) maxSpeed = 0;
    int newMaxSpeed = 999999;
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

QVector<Vehicle *> Train::getVehicles() const
{
    return vehicles;
}

QPointF Train::getLocationOnPath(float percentOnPath)
{
    return actualPathGraphic->path().pointAtPercent(percentOnPath);
}

void Train::moveTrain()
{
    if (actualSpeed == 0) return; //no change
    bool lastRail = false;
    bool directionOnEventBegin = directionToEnd;
    int newOnPathLength; //speed in centimeters / tick (1 second)
    (directionToEnd) ? newOnPathLength = onPathLength + actualSpeed : newOnPathLength = onPathLength - actualSpeed;
    int endPointValue;
    (directionToEnd) ? endPointValue = 1 : endPointValue = 0;
    float newPathPercentValue;
    int loop = 0; //if train on tick end "stop" exactly on percent 1.00 or 0.00
    do
    {
        newPathPercentValue = actualPathGraphic->path().percentAtLength(newOnPathLength/10); //transfer to decimeters (unit on map)
        if (newPathPercentValue == endPointValue)
        {
            if (trainPath.size() > 0)
            {
                (directionToEnd) ? newOnPathLength -= actualRail->getRailLength()*10 : newOnPathLength = newOnPathLength + dynamic_cast<Rail*>(trainPath[0])->getRailLength()*10;
                directionToEnd = TrainNavigation::checkNewDirection(directionToEnd, actualRail, trainPath[0]); //check direction for new path segment
                actualRail = trainPath[0];
                trainPath.remove(0);
                actualPathGraphic = dynamic_cast<QGraphicsPathItem*>(actualRail->getGraphicItem());
            }
            else
            {
                setActualSpeed(0);
                (directionToEnd) ? newOnPathLength = actualPathGraphic->path().length()*10 : newOnPathLength = 0;
                (directionToEnd) ? newPathPercentValue = 1 : newPathPercentValue = 0;
                lastRail = true;
            }
        }
        loop++;
    }
    while(loop < 4 && (newPathPercentValue == 1 || newPathPercentValue == 0) && lastRail == false);
    if (directionOnEventBegin != directionToEnd)
    {
        newOnPathLength = (newOnPathLength - (actualPathGraphic->path().length()*10))*-1;
        newPathPercentValue = actualPathGraphic->path().percentAtLength(newOnPathLength/10);
    }
    QPoint onPathPoint = actualPathGraphic->path().pointAtPercent(newPathPercentValue).toPoint() + actualPathGraphic->pos().toPoint();
    onPathPoint -= dynamic_cast<Vehicle*>(vehicles[0])->axlePos(); //change pos by axle pos (relative pos)
    setGraphicLocation(onPathPoint); //graphic item position change by class WorldMap! (out of QTHREAD)
    onPathValue = newPathPercentValue; //actualize new train value on path (rail track)
    onPathLength = newOnPathLength;
}

void Train::startAutopilot()
{
    //TrainNavigation navigation;
    //trainPath = navigation.autopilotCheck(1000,5,actualRail,directionToEnd);
    trainPath = TrainNavigation::autopilotCheck(10000,10,actualRail,directionToEnd);
}

void Train::setTrainPath(QVector<Rail*> newTrainPath)
{
    trainPath = newTrainPath;
}

void Train::setActualPathGraphic(Rail* actualRail)
{
    if (actualRail != nullptr) actualPathGraphic = dynamic_cast<QGraphicsPathItem*>(dynamic_cast<Actor*>(actualRail)->getGraphicItem());
    else actualPathGraphic = nullptr;
}

void Train::tickEvent()
{
    moveTrain();
}

Train::~Train()
{
    for (auto vehicle : vehicles)
    {
        delete vehicle;
    }
}
