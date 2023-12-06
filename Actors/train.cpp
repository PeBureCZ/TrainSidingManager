#include "train.h"

Train::Train(QObject* parent, QGraphicsItem* newGraphicItem, Rail* spawnedRail) : Movable(parent, newGraphicItem)
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

void Train::actualizeGraphicLocation()
{
    //this function is called from world with function "updateWorld"
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
    qDebug() << "move train start";
    if (actualSpeed == 0) return; //no change
    bool lastRail = false;
    bool directionOnEventBegin = directionToEnd;
    int newOnPathLength; //speed in centimeters / tick (1 second)
    (directionToEnd) ? newOnPathLength = onPathLength + actualSpeed : newOnPathLength = onPathLength - actualSpeed;
    int endPointValue;
    (directionToEnd) ? endPointValue = 1 : endPointValue = 0;
    float newPathPercentValue;
    int loop = 0; //if train on tick end "stop" exactly on percent 1 or 0
    do
    {
        newPathPercentValue = actualPath->path().percentAtLength(newOnPathLength/100);
        if (newPathPercentValue == endPointValue)
        {
            if (trainPath.size() > 0)
            {
                (directionToEnd) ? newOnPathLength -= actualRail->getRailLength()*100 : newOnPathLength = newOnPathLength + dynamic_cast<Rail*>(trainPath[0])->getRailLength()*100;
                TrainNavigation navigation;
                directionToEnd = navigation.checkNewDirection(directionToEnd, actualRail, trainPath[0]); //check direction for new path segment
                actualRail = trainPath[0];
                trainPath.remove(0);
                actualPath = dynamic_cast<QGraphicsPathItem*>(actualRail->getGraphicItem());
            }
            else
            {
                setActualSpeed(0);
                (directionToEnd) ? newOnPathLength = actualPath->path().length()*100 : newOnPathLength = 0;
                (directionToEnd) ? newPathPercentValue = 1 : newPathPercentValue = 0;
                lastRail = true;
            }
        }
        loop++;
    }
    while(loop < 4 && newPathPercentValue == 1 || newPathPercentValue == 0 && lastRail == false);
    if (directionOnEventBegin != directionToEnd)
    {
        newOnPathLength = (newOnPathLength - (actualPath->path().length()*100))*-1;
        newPathPercentValue = actualPath->path().percentAtLength(newOnPathLength/100);
    }
    QPoint onPathPoint = actualPath->path().pointAtPercent(newPathPercentValue).toPoint() + actualPath->pos().toPoint();
    onPathPoint -= dynamic_cast<Vehicle*>(vehicles[0])->axlePos();
    setGraphicLocation(onPathPoint); //graphic item position change by class WorldMap! (out of QTHREAD)
    onPathValue = newPathPercentValue; //actualize new train value on path (rail track)
    onPathLength = newOnPathLength;
}

void Train::setTrainPath(QVector<Rail *> newTrainPath)
{
    trainPath = newTrainPath;
}

void Train::tickEvent()
{
    moveTrain();
}
