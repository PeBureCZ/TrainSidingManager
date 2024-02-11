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

void Train::addVehicleToTrain(Vehicle *newVehicle, QGraphicsItem* graphicsItem)
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
    if (actualSpeed == 0) return; //no change, no move
    int newOnPathLength = onPathLength; //in centimeters
    bool directionOnEventBegin = directionToEnd;
    bool repeat = false;

    if (directionToEnd && newOnPathLength + actualSpeed > actualRail->getRailLength()*10) repeat = true;
    else if (!directionToEnd && newOnPathLength - actualSpeed < 0) repeat = true;

    (directionToEnd) ? newOnPathLength = onPathLength + actualSpeed : newOnPathLength = onPathLength - actualSpeed;

    while (repeat)
    {
        if (trainPath.size() > 0)
        {
            (directionOnEventBegin) ? newOnPathLength -= actualRail->getRailLength()*10 : newOnPathLength = newOnPathLength + dynamic_cast<Rail*>(trainPath[0])->getRailLength()*10;
            directionToEnd = TrainNavigation::checkNewDirection(directionToEnd, actualRail, trainPath[0]); //check direction for new path segment
            actualRail = trainPath[0];
            trainPath.remove(0);
            actualPathGraphic = dynamic_cast<QGraphicsPathItem*>(actualRail->getGraphicItem());

            if (directionOnEventBegin && newOnPathLength < actualRail->getRailLength()*10) break;
            if (!directionOnEventBegin && newOnPathLength > 0) break;
        }
        else
        {
            setActualSpeed(0);
            (directionToEnd) ? newOnPathLength = actualPathGraphic->path().length()*10 : newOnPathLength = 0;
            break;
        }
    }

    if (directionOnEventBegin != directionToEnd) newOnPathLength = (newOnPathLength - (actualPathGraphic->path().length()*10))*-1;

    float newPathPercentValue = actualPathGraphic->path().percentAtLength(newOnPathLength/10);
    if ((newPathPercentValue == 0 || newPathPercentValue == 1) && trainPath.size() == 0) setActualSpeed(0); //train stop at last rail

    QPoint onPathPoint = actualPathGraphic->path().pointAtPercent(newPathPercentValue).toPoint() + actualPathGraphic->pos().toPoint();

    onPathPoint -= dynamic_cast<Vehicle*>(vehicles[0])->axlePos(); //change pos by axle pos (relative pos)
    setGraphicLocation(onPathPoint); //graphic item position change by class WorldMap! (out of QTHREAD)
    onPathValue = newPathPercentValue; //actualize new train value on path (rail track)
    onPathLength = newOnPathLength;
}

void Train::startAutopilot()
{
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
