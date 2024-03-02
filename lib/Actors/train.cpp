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
    releasePath = false;
    setActualPathGraphic(actualRail);
    remainToPathEnd = 0;
    breakLevel = 0.2f;
    throttleLevel = 0.07f;
    lastRailChecked = nullptr;
    occupiedByFirstVehicle = nullptr;
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

    if (directionToRailEnd && newOnPathLength + actualSpeed > actualRail->getLengthOfRail()) repeat = true;
    else if (!directionToRailEnd && newOnPathLength - actualSpeed < 0) repeat = true;

    recalculateSpeed(newOnPathLength);

    directionToRailEnd ? newOnPathLength = onPathLength + actualSpeed : newOnPathLength = onPathLength - actualSpeed;

    while (repeat)
    {
        if (remainingPath.size() > 0)
        {
            //get a new position of train
            (directionOnEventBegin) ? newOnPathLength -= actualRail->getLengthOfRail() : newOnPathLength = newOnPathLength + dynamic_cast<Rail*>(remainingPath[0])->getLengthOfRail();

            takenPath.push_back(actualRail);

            //signal: "sekční + odjezdové" - not yet
            if ((directionToRailEnd && actualRail->getSignal(1) != nullptr) || (!directionToRailEnd && actualRail->getSignal(0) != nullptr))
            {
                 releasePath = true; //will release path after tick in tickEvent();
            }

            directionToRailEnd = TrainNavigation::checkDirectionOnNextRail(directionToRailEnd, actualRail, remainingPath[0]); //check direction for new path segment

            //The already taken path is added to the takenPath, and a new actualRail is set from the remainingPath
            actualRail = remainingPath[0];

            //signal: "vjezdové" - temporary
            if ((directionToRailEnd && actualRail->getSignal(0) != nullptr) || (!directionToRailEnd && actualRail->getSignal(1) != nullptr))
            {
                releasePath = true; //will release path after tick in tickEvent();
            }

            remainingPath.remove(0);
            actualPathGraphic = dynamic_cast<QGraphicsPathItem*>(actualRail->getGraphicItem());

            if (directionOnEventBegin && newOnPathLength < actualRail->getLengthOfRail()) break;
            if (!directionOnEventBegin && newOnPathLength > 0) break;
        }
        else
        {
            setActualSpeed(0.0f);
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
    if (directionToRailEnd && onPathLength + actualTrainLength > actualRail->getLengthOfRail()) repeat = true;
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
        occupiedByFirstVehicle = actualRail;
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
                    if ((actualVehicleDirection && temporalDistance > testedRail->getLengthOfRail()) || (!actualVehicleDirection && temporalDistance < 0))
                    {
                        if (bonusPathIndex >= remainingPath.size()) break;
                        bool saveDirection = actualVehicleDirection;
                        actualVehicleDirection = TrainNavigation::checkDirectionOnNextRail(actualVehicleDirection, testedRail, remainingPath[bonusPathIndex]);

                        if (saveDirection && actualVehicleDirection) temporalDistance -= testedRail->getLengthOfRail();
                        else if (saveDirection && !actualVehicleDirection) temporalDistance = dynamic_cast<Rail*>(remainingPath[bonusPathIndex])->getLengthOfRail() - (temporalDistance - testedRail->getLengthOfRail());
                        else if (!saveDirection && actualVehicleDirection) temporalDistance *= -1;
                        else if (!saveDirection && !actualVehicleDirection) temporalDistance = dynamic_cast<Rail*>(remainingPath[bonusPathIndex])->getLengthOfRail() + temporalDistance;

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

        occupiedByFirstVehicle = testedRail;

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

void Train::setdirectionToRailEnd(bool newDirection)
{
    directionToRailEnd = newDirection;
}

void Train::setMoveDirection(bool forwardDirection)
{
    //moveForward
    qDebug() << "start reverse!";

    //recalculateSpeed(newOnPathLength);

    //remainingPath.clear();
    //takenPath.clear();

    /*
    bool toActualRail = true;
    for (auto rail : fullOccupiedRailPath)
    {
        if (toActualRail)
        {
            if (rail == actualRail)
            {
                toActualRail = false;
                continue;
            }
            remainingPath.push_back(rail);
        }
        else takenPath.push_back(rail);
    }
    */
    int newOnPathLength = onPathLength; //in decimeters
    bool directionOnEventBegin = directionToRailEnd;
    bool repeat = false;

    if (directionToRailEnd && newOnPathLength + actualTrainLength > actualRail->getLengthOfRail()) repeat = true;
    else if (!directionToRailEnd && newOnPathLength - actualTrainLength < 0) repeat = true;

    directionToRailEnd ? newOnPathLength = onPathLength + actualTrainLength : newOnPathLength = onPathLength - actualTrainLength;

    while (repeat)
    {
        if (remainingPath.size() > 0)
        {
            //get a new position of train
            (directionOnEventBegin) ? newOnPathLength -= actualRail->getLengthOfRail() : newOnPathLength = newOnPathLength + dynamic_cast<Rail*>(remainingPath[0])->getLengthOfRail();

            takenPath.push_back(actualRail);

            directionToRailEnd = TrainNavigation::checkDirectionOnNextRail(directionToRailEnd, actualRail, remainingPath[0]); //check direction for new path segment

            //The already taken path is added to the takenPath, and a new actualRail is set from the remainingPath
            actualRail = remainingPath[0];

            remainingPath.remove(0);
            actualPathGraphic = dynamic_cast<QGraphicsPathItem*>(actualRail->getGraphicItem());

            if (directionOnEventBegin && newOnPathLength < actualRail->getLengthOfRail()) break;
            if (!directionOnEventBegin && newOnPathLength > 0) break;
        }
        else qDebug() << "error in setMoveDiretion";
    }

    if (directionOnEventBegin != directionToRailEnd) newOnPathLength = (newOnPathLength - (actualPathGraphic->path().length()))*-1;

    float newPathPercentValue = actualPathGraphic->path().percentAtLength(newOnPathLength);

    onPathValue = newPathPercentValue; //actualize new train value on path (rail track)
    onPathLength = newOnPathLength;


    //change taken path & remainingPath
    QList<Rail*> savedTakenPath = takenPath;
    takenPath = remainingPath;
    remainingPath = savedTakenPath;

    //change actual rail and occupiedByFirstVehicle rail
    //Rail* savedActualRail = actualRail;
    //actualRail = occupiedByFirstVehicle;
    //occupiedByFirstVehicle = savedActualRail;

    QList<Vehicle*> reversedVehicles = {};
    for (int i = vehicles.size() - 1; i >= 0; i--)
    {
        reversedVehicles.push_back(vehicles[i]);
        qDebug() << "reversed vehicle: " << i;
    }
    vehicles = reversedVehicles;
    directionToRailEnd = !directionToRailEnd;

    actualizeVehiclesOnPath();
    setActualSpeed(1);
}

void Train::makePathFromPortal()
{
    remainingPath = TrainNavigation::autopilotCheck(30000,100,actualRail,directionToRailEnd);
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
    lastRailChecked = nullptr; //will actualize signals
    remainToPathEnd = -1;
}

void Train::setActualPathGraphic(Rail* actualRail)
{
    if (actualRail != nullptr) actualPathGraphic = dynamic_cast<QGraphicsPathItem*>(dynamic_cast<Actor*>(actualRail)->getGraphicItem());
    else actualPathGraphic = nullptr;
}

bool Train::teleportTrainToRail(Rail *rail, bool direction)
{
    if (rail->getOccupied() == true)
    {
        qDebug() << "can´t teleport, rail is occupied";
        return false;
    }
    actualRail = rail;
    directionToRailEnd = direction;
    directionToRailEnd ? onPathLength = 5 : onPathLength = actualRail->getLengthOfRail() - 5;
    setActualPathGraphic(actualRail);
    int savedSpeed = actualSpeed;
    setActualSpeed(15);
    moveTrain(); //move train by 1 set train in right position
    setActualSpeed(savedSpeed);
    makePathFromPortal();
    if (rail->getLengthOfRail() + TrainNavigation::getTrainPathLength(remainingPath) < actualTrainLength - 10)
    {
        qDebug() << "can´t teleport, rail is too short";
        return false;
    }
    return true;
}

int Train::getTrainLength()
{
    return actualTrainLength;
}

int Train::getRemainToPathEnd()
{
    return remainToPathEnd;
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
    directionToRailEnd ? remainToPathEnd = actualRail->getLengthOfRail() - actualDistanceOnRail : remainToPathEnd = actualDistanceOnRail;
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

void Train::threadedTickEvent()
{
    moveTrain();
}

void Train::tickEvent()
{
    if (releasePath == true)
    {
        for (auto rail : takenPath)
        {
            rail->setOccupied(false, true);
            if (rail->getSignal(0) != nullptr) rail->getSignal(0)->setState(SIGNAL_STOP, STOP_SIGNAL_SPRITE);
            if (rail->getSignal(1) != nullptr) rail->getSignal(1)->setState(SIGNAL_STOP, STOP_SIGNAL_SPRITE);
        }
        takenPath.clear();
        releasePath = false; 
    }
    if (lastRailChecked != occupiedByFirstVehicle && remainToPathEnd != -1)
    {
        //train go throw new rail - need actualize signals
        TrainNavigation::checkSignalsOnPath(actualRail, remainingPath,directionToRailEnd,remainToPathEnd-actualSpeed);
        lastRailChecked = occupiedByFirstVehicle;
    }
}

QVector<Rail *> Train::getRemainingPath() const
{
    return remainingPath;
}

QVector<Rail *> Train::getTakenPath() const
{
    return takenPath;
}

Train::~Train()
{
    for (auto vehicle : vehicles)
    {
        delete vehicle;
    }
    for (auto rail : takenPath) rail->setOccupied(false, true);
    for (auto rail : remainingPath) rail->setOccupied(false, true);
    if (actualRail != nullptr) actualRail->setOccupied(false, true);
}
