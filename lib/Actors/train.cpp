#include "train.h"

Train::Train(QObject* parent, QGraphicsItem* newGraphicItem, Rail* spawnedRail) : Movable(parent, newGraphicItem)
{
    onPathValue = 0;
    onPathLength = 0;
    actualRail = spawnedRail;
    vehicles = {}; //list
    vehicleGraphicsItems = {}; //list
    directionToRailEnd = true;
    actualTrainLength = 0; //decimeters
    moveForward = true;
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
    actualizeTrainLenth();
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
    int newOnPathLength = onPathLength; //in decimeters
    bool directionOnEventBegin = directionToRailEnd;
    bool repeat = false;

    if (directionToRailEnd && newOnPathLength + actualSpeed > actualRail->getRailLength()) repeat = true;
    else if (!directionToRailEnd && newOnPathLength - actualSpeed < 0) repeat = true;

    (directionToRailEnd) ? newOnPathLength = onPathLength + actualSpeed : newOnPathLength = onPathLength - actualSpeed;

    while (repeat)
    {
        if (trainPath.size() > 0)
        {
            (directionOnEventBegin) ? newOnPathLength -= actualRail->getRailLength() : newOnPathLength = newOnPathLength + dynamic_cast<Rail*>(trainPath[0])->getRailLength()*10;
            directionToRailEnd = TrainNavigation::checkNewDirection(directionToRailEnd, actualRail, trainPath[0]); //check direction for new path segment
            actualRail = trainPath[0];
            trainPath.remove(0);
            actualPathGraphic = dynamic_cast<QGraphicsPathItem*>(actualRail->getGraphicItem());

            if (directionOnEventBegin && newOnPathLength < actualRail->getRailLength()) break;
            if (!directionOnEventBegin && newOnPathLength > 0) break;
        }
        else
        {
            setActualSpeed(0);
            (directionToRailEnd) ? newOnPathLength = actualPathGraphic->path().length() : newOnPathLength = 0;
            break;
        }
    }

    if (directionOnEventBegin != directionToRailEnd) newOnPathLength = (newOnPathLength - (actualPathGraphic->path().length()))*-1;

    float newPathPercentValue = actualPathGraphic->path().percentAtLength(newOnPathLength);
    if ((newPathPercentValue == 0 || newPathPercentValue == 1) && trainPath.size() == 0) setActualSpeed(0); //train stop at last rail

    QPoint onPathPoint = actualPathGraphic->path().pointAtPercent(newPathPercentValue).toPoint() + actualPathGraphic->pos().toPoint();

    onPathPoint -= dynamic_cast<Vehicle*>(vehicles[0])->axlePos(); //change pos by axle pos (relative pos)
    setGraphicLocation(onPathPoint); //graphic item position change by class WorldMap! (out of QTHREAD)
    onPathValue = newPathPercentValue; //actualize new train value on path (rail track)
    onPathLength = newOnPathLength;
}

void Train::startAutopilot()
{
    trainPath = TrainNavigation::autopilotCheck(10000,10,actualRail,directionToRailEnd);
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

void Train::teleportTrainToRail(Rail *rail)
{
    actualRail = rail;
    setActualPathGraphic(actualRail);
    int railLength = rail->getRailLength();

    if (railLength < actualTrainLength - 10)
    {
        qDebug() << "rail is too short";
        return;
    }

    directionToRailEnd ? onPathLength = 5 : onPathLength = 5 + actualTrainLength;
    int savedSpeed = actualSpeed;
    actualSpeed = 1;
    moveTrain(); //move train by 1 set train in right position
    actualSpeed = savedSpeed;
}

void Train::actualizeTrainLenth()
{
    actualTrainLength = 0;
    for (auto vehicle : vehicles)
    {
        actualTrainLength += vehicle->getLegth();
    }
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
