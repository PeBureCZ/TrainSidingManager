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
    remainingPath = {};
    takenPath = {};
    setActualPathGraphic(actualRail);
    remainToPathEnd = 0;
    breakLevel = 0.2f;
    throttleLevel = 0.07f;
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
    int newMaxSpeed = 99999.9f;
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
    //no change, no move
    if (actualSpeed <= 0.0f) return;

    //calculate the actual position of the train. The actual position corresponds to the last vehicle in direction of movement
    actualizeOnPathLength();

    //calculate the graphic and actor positions for each individual vehicle
    actualizeVehiclesOnPath();

    //Aactualize Train(Actor) location (not Vehicle locations)
    if (moveForward) setLocation(dynamic_cast<Actor*>(vehicles[0])->getLocation(), false);
    else setLocation(dynamic_cast<Actor*>(vehicles.last())->getLocation(), false);
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
        if (remainingPath.size() > 0)
        {
            //get a new position of train
            (directionOnEventBegin) ? newOnPathLength -= actualRail->getRailLength() : newOnPathLength = newOnPathLength + dynamic_cast<Rail*>(remainingPath[0])->getRailLength();

            takenPath.push_back(actualRail);

            //signal: "sekční + odjezdové" - not yet
            if ((directionToRailEnd && actualRail->getSignal(1) != nullptr) || (!directionToRailEnd && actualRail->getSignal(0) != nullptr))
            {
                for (auto rail : takenPath) rail->setOccupied(false, true);
                takenPath.clear();
            }

            directionToRailEnd = TrainNavigation::checkDirectionOnNextRail(directionToRailEnd, actualRail, remainingPath[0]); //check direction for new path segment

            //The already taken path is added to the takenPath, and a new actualRail is set from the remainingPath
            actualRail = remainingPath[0];

            //signal: "vjezdové" - temporary
            if ((directionToRailEnd && actualRail->getSignal(0) != nullptr) || (!directionToRailEnd && actualRail->getSignal(1) != nullptr))
            {
                for (auto rail : takenPath) rail->setOccupied(false, true);
                takenPath.clear();
            }

            remainingPath.remove(0);
            actualPathGraphic = dynamic_cast<QGraphicsPathItem*>(actualRail->getGraphicItem());

            if (directionOnEventBegin && newOnPathLength < actualRail->getRailLength()) break;
            if (!directionOnEventBegin && newOnPathLength > 0) break;
        }
        else
        {
            setActualSpeed(0.0f);
            qDebug() << "1: speed set to 0 in train";
            (directionToRailEnd) ? newOnPathLength = actualPathGraphic->path().length() : newOnPathLength = 0;
            break;
        }
    }

    if (directionOnEventBegin != directionToRailEnd) newOnPathLength = (newOnPathLength - (actualPathGraphic->path().length()))*-1;

    float newPathPercentValue = actualPathGraphic->path().percentAtLength(newOnPathLength);

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
                        if (bonusPathIndex >= remainingPath.size()) break;
                        bool saveDirection = actualVehicleDirection;
                        actualVehicleDirection = TrainNavigation::checkDirectionOnNextRail(actualVehicleDirection, testedRail, remainingPath[bonusPathIndex]);

                        if (saveDirection && actualVehicleDirection) temporalDistance -= testedRail->getRailLength();
                        else if (saveDirection && !actualVehicleDirection) temporalDistance = dynamic_cast<Rail*>(remainingPath[bonusPathIndex])->getRailLength() - (temporalDistance - testedRail->getRailLength());
                        else if (!saveDirection && actualVehicleDirection) temporalDistance *= -1;
                        else if (!saveDirection && !actualVehicleDirection) temporalDistance = dynamic_cast<Rail*>(remainingPath[bonusPathIndex])->getRailLength() + temporalDistance;

                        testedRail = remainingPath[bonusPathIndex];
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

void Train::selectTrain(bool selected)
{
    for (auto vehicle : vehicles)
    {
        vehicle->selectVehicle(selected);
    }
}

void Train::startAutopilot()
{
    remainingPath = TrainNavigation::autopilotCheck(30000,30,actualRail,directionToRailEnd);
    for (auto rail : remainingPath)
    {
        rail->setOccupied(true, true);
    }
    actualRail->setOccupied(true, true);
}

void Train::setTrainPath(QVector<Rail*> newTrainPath)
{
    remainingPath = newTrainPath;
}

void Train::addNextPartOfPath(QVector<Rail *> addedPartOfPath)
{
    remainingPath += addedPartOfPath;
    for (auto rail : addedPartOfPath)
    {
        rail->setOccupied(true, true);
    }
}

void Train::setActualPathGraphic(Rail* actualRail)
{
    if (actualRail != nullptr) actualPathGraphic = dynamic_cast<QGraphicsPathItem*>(dynamic_cast<Actor*>(actualRail)->getGraphicItem());
    else actualPathGraphic = nullptr;
}

bool Train::teleportTrainToRail(Rail *rail)
{
    actualRail = rail;
    setActualPathGraphic(actualRail);
    startAutopilot();
    if (rail->getRailLength() + TrainNavigation::getTrainPathLength(remainingPath) < actualTrainLength - 10)
    {
        qDebug() << "can´t teleport, rail is too short";
        return false;
    }
    directionToRailEnd ? onPathLength = 5 : onPathLength = 5 + actualTrainLength;
    int savedSpeed = actualSpeed;
    actualSpeed = 1;
    moveTrain(); //move train by 1 set train in right position
    actualSpeed = savedSpeed; 
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
    directionToRailEnd ? remainToPathEnd = actualRail->getRailLength() - actualDistanceOnRail : remainToPathEnd = actualDistanceOnRail;
    remainToPathEnd += TrainNavigation::getTrainPathLength(remainingPath);
    if (moveForward) remainToPathEnd -= actualTrainLength;

    if (remainToPathEnd < actualSpeed)
    {
        if (actualSpeed > breakLevel)
        {
            qDebug() << "TRAIN DERAILED OR MOVE VIA RED SIGNAL at speed: " << actualSpeed; //NOT COMPLETED YET
            setActualSpeed(0); //train stop at last rail
            return;
        }
    }
    if (remainToPathEnd - actualSpeed - 80 < (0 - (actualSpeed*actualSpeed)) / (2 * breakLevel*-1)) //checked distance = 12 second - temporary solution
    {
        if (remainToPathEnd > 50 && actualSpeed > breakLevel)  setActualSpeed(actualSpeed - breakLevel);
        else if (remainToPathEnd <= 50) setActualSpeed(0);
    }
    else setActualSpeed(actualSpeed + throttleLevel);
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
    return remainingPath;
}

Train::~Train()
{
    for (auto vehicle : vehicles)
    {
        delete vehicle;
    }
    for (auto rail : takenPath) rail->setOccupied(false, true);
    for (auto rail : remainingPath) rail->setOccupied(false, true);
    actualRail->setOccupied(false, true);
}
