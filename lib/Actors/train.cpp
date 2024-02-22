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

void Train::actualizeGraphicRotation()
{
    //this function is called from worldmap (class) with function "updateWorld"
    //location (graphicLocation variable) is changed in QThreads and have to be visually changed in main thread

    for (int i = 0; i < vehicles.size(); i++)
    {
        dynamic_cast<Vehicle*>(vehicles[i])->actualizeGraphicRotation();
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

void Train::actualizeOnPathLength()
{
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

    /*
    if (((newPathPercentValue == 0 && !directionToRailEnd) || (newPathPercentValue == 1 && directionToRailEnd)) && trainPath.size() == 0)
    {
        setActualSpeed(0); //train stop at last rail
    }
    */

    onPathValue = newPathPercentValue; //actualize new train value on path (rail track)
    onPathLength = newOnPathLength;
}

void Train::actualizeVehiclesOnPath()
{
    bool repeat = false;
    if (directionToRailEnd && onPathLength + actualTrainLength > actualRail->getRailLength()) repeat = true;
    else if (!directionToRailEnd && onPathLength - actualTrainLength < 0) repeat = true;
    if (!repeat)
    {
        int temporalDistance = onPathLength;
        QPoint onPathPoint;
        if (moveForward)
        {
            for (int i = vehicles.size()-1; i >= 0; i--)
            {
                Vehicle* vehicle = dynamic_cast<Vehicle*>(vehicles[i]);

                //front axle
                float percentOnRail = actualPathGraphic->path().percentAtLength(temporalDistance);
                onPathPoint = actualPathGraphic->path().pointAtPercent(percentOnRail).toPoint() + actualPathGraphic->pos().toPoint();

                //second axle
                int secondAxleDistance = temporalDistance;
                directionToRailEnd ? secondAxleDistance += vehicle->getLegth() : secondAxleDistance -= vehicle->getLegth();
                percentOnRail = actualPathGraphic->path().percentAtLength(secondAxleDistance);
                QPoint onPathSecondPoint = actualPathGraphic->path().pointAtPercent(percentOnRail).toPoint() + actualPathGraphic->pos().toPoint();

                qreal angle = qAtan2(onPathPoint.y() - onPathSecondPoint.y(), onPathPoint.x() - onPathSecondPoint.x()) * 180.0 / M_PI;

                vehicle->setRotation(angle+90.f,false);
                vehicle->setGraphicRotation(angle+90.f);

                QPoint rotatedFirstAxlePoint = getRotatedPointArountPivot(onPathPoint+QPoint(vehicle->getWidth()/2,0),onPathPoint, angle+90);
                //mirror point P_new = pivot + (pivot - P_old)
                QPoint newLocation = onPathPoint + (onPathPoint - rotatedFirstAxlePoint);

                vehicle->setLocation(newLocation,false);
                vehicle->setGraphicLocation(newLocation);

                directionToRailEnd ? temporalDistance += vehicle->getLegth() : temporalDistance -= vehicle->getLegth();
            }
        }
        else //move backward
        {
            for (int i = 0; i <= vehicles.size()-1; i++)
            {

            }
        }
    }
    else //front (or back) of train vehicle is on next rail/s
    {
        if (trainPath.size() == 0)
        {
            qDebug() << "path is too short!";
            setActualSpeed(0); //train stop at last rail
            return;
        }

        QPoint onPathPoint;
        int temporalDistance = onPathLength;

        Rail* testedRail = actualRail;
        QGraphicsPathItem* testedGraphicItem = actualPathGraphic;
        int bonusPathIndex = 0;
        bool actualVehicleDirection = directionToRailEnd;
        temporalDistance = onPathLength;

        QList<QPoint>firstAxlePositionOnRail = {};
        QList<QPoint>secondAxlePositionOnRail = {};
        QList<Vehicle*> sortedVehicles = {};

        if (moveForward)
        {
            for (int i = vehicles.size()-1; i >= 0; i--)
            {
                Vehicle* actualVehicle = dynamic_cast<Vehicle*>(vehicles[i]);
                sortedVehicles.push_back(actualVehicle);
                while (true)
                {
                    if ((actualVehicleDirection && temporalDistance > testedRail->getRailLength()) || (!actualVehicleDirection && temporalDistance < 0))
                    {
                        if (bonusPathIndex >= trainPath.size()) break;
                        bool saveDirection = actualVehicleDirection;
                        actualVehicleDirection = TrainNavigation::checkNewDirection(actualVehicleDirection, testedRail, trainPath[bonusPathIndex]);

                        if (saveDirection && actualVehicleDirection) temporalDistance -= testedRail->getRailLength();
                        else if (saveDirection && !actualVehicleDirection) temporalDistance = dynamic_cast<Rail*>(trainPath[bonusPathIndex])->getRailLength() - (temporalDistance - testedRail->getRailLength());
                        else if (!saveDirection && actualVehicleDirection) temporalDistance *= -1;
                        else if (!saveDirection && !actualVehicleDirection) temporalDistance = dynamic_cast<Rail*>(trainPath[bonusPathIndex])->getRailLength() + temporalDistance;

                        testedRail = trainPath[bonusPathIndex];
                        testedGraphicItem = dynamic_cast<QGraphicsPathItem*>(testedRail->getGraphicItem());
                        bonusPathIndex++;
                    }
                    else
                    {
                        float percentOnRail = testedGraphicItem->path().percentAtLength(temporalDistance);
                        onPathPoint = testedGraphicItem->path().pointAtPercent(percentOnRail).toPoint() + testedGraphicItem->pos().toPoint();

                        if (secondAxlePositionOnRail.size() != sortedVehicles.size())
                        {
                            //will be on axle position
                            actualVehicleDirection ? temporalDistance += actualVehicle->getLegth() : temporalDistance -= actualVehicle->getLegth();
                            secondAxlePositionOnRail.push_back(onPathPoint);
                        }
                        else
                        {
                            firstAxlePositionOnRail.push_back(onPathPoint);
                            //will be on axle position
                            //actualVehicleDirection ? temporalDistance += actualVehicle->getLegth() : temporalDistance -= actualVehicle->getLegth();
                            break;
                        }
                    }
                }
            }
        }
        else //move backward
        {
            for (int i = 0; i <= vehicles.size()-1; i++)
            {

            }
        }
        int sortedIndex = 0;
        if (!moveForward) sortedIndex = sortedVehicles.size()-1;
        for (auto vehicle : sortedVehicles)
        {
            qreal angle = qAtan2(firstAxlePositionOnRail[sortedIndex].y() - secondAxlePositionOnRail[sortedIndex].y(), firstAxlePositionOnRail[sortedIndex].x() - secondAxlePositionOnRail[sortedIndex].x()) * 180.0 / M_PI;

            vehicle->setRotation(angle+90.f,false);
            vehicle->setGraphicRotation(angle+90.f);

            QPoint rotatedFirstAxlePoint = getRotatedPointArountPivot(firstAxlePositionOnRail[sortedIndex]+QPoint(vehicle->getWidth()/2,0),firstAxlePositionOnRail[sortedIndex], angle+90);
            //mirror point P_new = pivot + (pivot - P_old)
            QPoint newLocation = firstAxlePositionOnRail[sortedIndex] + (firstAxlePositionOnRail[sortedIndex] - rotatedFirstAxlePoint);

            vehicle->setLocation(newLocation,false);
            vehicle->setGraphicLocation(newLocation); //actualize graphic in world tick

            moveForward ? sortedIndex++ : sortedIndex--;
        }
    }
}

void Train::moveTrain()
{
    //no change, no move
    if (actualSpeed == 0) return;

    //calculate the actual position of the train. The actual position corresponds to the last vehicle in direction of movement
    actualizeOnPathLength();

    //calculate the graphic and actor positions for each individual vehicle
    actualizeVehiclesOnPath();
    if (moveForward) setLocation(dynamic_cast<Actor*>(vehicles[0])->getLocation(), false);
    else setLocation(dynamic_cast<Actor*>(vehicles.last())->getLocation(), false);
}

void Train::startAutopilot()
{
    trainPath = TrainNavigation::autopilotCheck(30000,30,actualRail,directionToRailEnd);
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

bool Train::teleportTrainToRail(Rail *rail)
{
    if (rail->getRailLength() < actualTrainLength - 10)
    {
        qDebug() << "can´t teleport, rail is too short";
        return false;
    }

    actualRail = rail;
    setActualPathGraphic(actualRail);

    directionToRailEnd ? onPathLength = 5 : onPathLength = 5 + actualTrainLength;
    int savedSpeed = actualSpeed;
    actualSpeed = 1;
    moveTrain(); //move train by 1 set train in right position
    actualSpeed = savedSpeed;
    startAutopilot();
    return true;
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
        actualSpeed -= 4; //apply breaks - temporary
        if (actualSpeed < 0) actualSpeed = 1;
        if (remainToRailEnd <= 0) actualSpeed = 0;
    }
    else
    {
        actualSpeed += 2; //apply throtle power - temporary
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
