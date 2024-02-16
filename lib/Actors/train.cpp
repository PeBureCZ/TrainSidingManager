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

    for (int i = 0; i < vehicles.size(); i++)
    {
        dynamic_cast<Vehicle*>(vehicles[i])->actualizeGraphicLocation();
    }
}

Rail *Train::getActualRail() const
{
    return actualRail;
}

float Train::getActualPathValue() const
{
    return onPathValue;
}

void Train::setActualPathValue(float newValue)
{
    onPathValue = newValue;
}

void Train::addMultipleVehicleToTrain(QList<Vehicle *> newVehicles)
{
    for (auto vehicleActor : newVehicles)
    {
        vehicles.push_back(vehicleActor);
        vehicleGraphicsItems.push_back(vehicleActor->getGraphicItem());
    }
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

    recalculateSpeed(newOnPathLength);

    directionToRailEnd ? newOnPathLength = onPathLength + actualSpeed : newOnPathLength = onPathLength - actualSpeed;

    while (repeat)
    {
        if (trainPath.size() > 0)
        {
            (directionOnEventBegin) ? newOnPathLength -= actualRail->getRailLength() : newOnPathLength = newOnPathLength + dynamic_cast<Rail*>(trainPath[0])->getRailLength();
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
    if (((newPathPercentValue == 0 && !directionToRailEnd) || (newPathPercentValue == 1 && directionToRailEnd)) && trainPath.size() == 0)
    {
        setActualSpeed(0); //train stop at last rail
    }

    onPathValue = newPathPercentValue; //actualize new train value on path (rail track)
    onPathLength = newOnPathLength;

    //TEMPORARY
    QPoint onPathPoint;
    Vehicle* vehicle = dynamic_cast<Vehicle*>(vehicles[0]);
    onPathPoint = actualPathGraphic->path().pointAtPercent(newPathPercentValue).toPoint() + actualPathGraphic->pos().toPoint();
    onPathPoint -= vehicle->firstAxlePos(); //change pos by axle pos (relative pos)
    vehicle->setLocation(onPathPoint + QPoint(0,newOnPathLength),false);
    vehicle->setGraphicLocation(onPathPoint);

    /*
    if ( vehicles.size() > 1)
    {
        directionToRailEnd ? newOnPathLength -= dynamic_cast<Vehicle*>(vehicles[0])->getLegth() : newOnPathLength += dynamic_cast<Vehicle*>(vehicles[0])->getLegth();
        for (auto vehicle : vehicles)
        {
            directionToRailEnd ? newOnPathLength += vehicle->getLegth() : newOnPathLength -= vehicle->getLegth();
            newPathPercentValue = actualPathGraphic->path().percentAtLength(newOnPathLength);
            onPathPoint = actualPathGraphic->path().pointAtPercent(newPathPercentValue).toPoint() + actualPathGraphic->pos().toPoint();
            onPathPoint -= vehicle->firstAxlePos(); //change pos by axle pos (relative pos)

            vehicle->setLocation(onPathPoint + QPoint(0,newOnPathLength),false);
            vehicle->setGraphicLocation(onPathPoint);
        }
    }
    */
}

void Train::startAutopilot()
{
    trainPath = TrainNavigation::autopilotCheck(30000,10,actualRail,directionToRailEnd);
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

void Train::recalculateSpeed(int actualDistanceOnRail)
{
    int remainToRailEnd;
    directionToRailEnd ? remainToRailEnd = actualRail->getRailLength() - actualDistanceOnRail : remainToRailEnd = actualDistanceOnRail;
    if (moveForward) remainToRailEnd -= actualDistanceOnRail;
    for (auto path : trainPath)
    {
        remainToRailEnd += path->getRailLength();
    }
    if (!moveForward) remainToRailEnd -= actualTrainLength;
    if (remainToRailEnd < actualSpeed*12) //checked distance = 12 second - temporary solution
    {
        actualSpeed -= 10; //apply breaks - temporary
        if (actualSpeed < 0) actualSpeed = 1;
        if (remainToRailEnd <= 0) actualSpeed = 0;
    }
    else
    {
        actualSpeed += 4; //apply throtle power - temporary
        if (actualSpeed > maxSpeed) actualSpeed = maxSpeed;
    }
}

bool Train::getDirectionToRailEnd() const
{
    return directionToRailEnd;
}

const bool Train::getMoveDirection()
{
    return moveForward;
}

void Train::tickEvent()
{
    moveTrain();
}

QVector<Rail *> Train::getTrainPath() const
{
    return trainPath;
}

Train::~Train()
{
    for (auto vehicle : vehicles)
    {
        delete vehicle;
    }
}
