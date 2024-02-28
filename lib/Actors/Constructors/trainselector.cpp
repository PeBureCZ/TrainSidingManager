#include "trainselector.h"


TrainSelector::TrainSelector(QObject* parent, QGraphicsItem* newGraphicItem, Actor *actorToConstructing)
    : SelectConstructor(parent, newGraphicItem, actorToConstructing)
{
    selectedTrain = nullptr;
    nearestSignal = nullptr;
    nearestTrain = nullptr;
    nearestRail = nullptr;
}

void TrainSelector::actualizeConstructor(QPoint newPoint, int zoomLevel)
{
    ActorConstructor::actualizeConstructor(newPoint, zoomLevel);
    if (selectedTrain == nullptr) findNearestTrain();
    else findNearestSignal();
}

Train* TrainSelector::getSelectedTrain()
{
    return selectedTrain;
}

void TrainSelector::setSelectedTrain()
{
    selectedTrain = nearestTrain;
}

Signal *TrainSelector::getNearestSignal()
{
    return nearestSignal;
}

Train *TrainSelector::getNearestTrain()
{
    return nearestTrain;
}

void TrainSelector::findPathToSignal()
{
    if (selectedTrain != nullptr && nearestSignal != nullptr)
    {
        Rail* lastRail;

        if (selectedTrain->getTrainPath().size() > 0) lastRail = selectedTrain->getTrainPath().last();
        else lastRail = selectedTrain->getActualRail();

        bool direction = TrainNavigation::checkDirectionOnLatestRail(selectedTrain->getTrainPath(), selectedTrain->getActualRail(), selectedTrain->getDirectionToRailEnd());
        Rail* railToFind = dynamic_cast<Rail*>(nearestSignal->getRailActor());
        QList<Rail*> needTestRails = {lastRail};
        QList<bool> testedRailDirection = {direction};

        QList<Rail*> findedRails = {};
        //QList<Rail*> findedDirections = {};

        int repeat = 300; //number of rails to check in order to find the path
        bool finded = false;
        while (repeat > 0 && needTestRails.size() > 0)
        {
            Rail* testedRail = needTestRails[0];
            if (testedRail == railToFind)
            {
                finded = true;
                break; // rail is finded!
            }
            direction = testedRailDirection[0];

            //if direction is true -> try to find rail on connection C1 or D1 (2,3), else on A0, B0 (0,1)
            int testedRailConnection = 0;
            if (direction) testedRailConnection += 2;

            int firstIndex = testedRailConnection;
            int lastIndex = testedRailConnection + 2;

            for (int i = firstIndex; i < lastIndex; i++)
            {
                //scan connected rail of testedRail
                if (testedRail->getConnectedRail(i) != nullptr) //true = on connection is rail
                {
                    Rail* newRailFinded = testedRail->getConnectedRail(i);
                    if (newRailFinded->getOccupied()) continue;

                    int conectionToPreviousRail = newRailFinded->getConnection(testedRail);
                    if (conectionToPreviousRail <=1) conectionToPreviousRail = 0;
                    else conectionToPreviousRail  = 1;

                    bool newDirection;
                    (conectionToPreviousRail == 0) ? newDirection = true : newDirection = false;

                    if (newRailFinded == railToFind)
                    {
                        //check if the track is in opposite direction
                        int railEndOfSignal;
                        (newRailFinded->getSignal(0) == nearestSignal) ? railEndOfSignal = 0 : railEndOfSignal = 1;
                        if (railEndOfSignal != newDirection)
                        {
                            //It is necessary to remove the wrong rail because it may be prioritized over the rail with the correct direction during reverse pathfinding
                            int indexOfWrongRail = findedRails.indexOf(testedRail);
                            if (indexOfWrongRail != -1) findedRails.removeAt(indexOfWrongRail);
                            continue;
                        }
                    }

                    int connectionToRailToFind = newRailFinded->getConnection(railToFind);
                    if (connectionToRailToFind != -1)
                    {
                        //newRailFinded is connected to railToFind! but is direction right?
                        if (connectionToRailToFind <=1) connectionToRailToFind = 0;
                        else connectionToRailToFind = 1;

                        if (conectionToPreviousRail == connectionToRailToFind) continue; //finded rail is in wrong direction
                    }
                    testedRailDirection.push_back(newDirection);
                    findedRails.push_back(newRailFinded); //add to temporal list
                    needTestRails.push_back(newRailFinded);
                }
            }
            repeat--;
            needTestRails.removeAt(0);
            testedRailDirection.removeAt(0);
        }

        if (finded)
        {
            //REVERSED PATHFINDING
            while(true) // remove other found rails at the end of the list if they are not the Rails looking for
            {
                Rail* lastRailInList = findedRails.last();
                if (railToFind == lastRailInList) break;
                else findedRails.removeLast();
            }
            for (int i = findedRails.size() - 1; i > 0; i--)
            {
                Rail* railFromList = findedRails[i];

                if (railFromList->getConnection(findedRails[i-1]) != -1); //part of path finded! Skip code...
                else if (railFromList != railToFind )
                {
                    //not first and not last rails
                    int connectionToPrevious = railFromList->getConnection(findedRails[i-1]);
                    int connectionToNext = railFromList->getConnection(findedRails[i+1]);

                    //transfer to railEnds number
                    if (connectionToPrevious != -1 && connectionToPrevious <= 1) connectionToPrevious = 0;
                    if (connectionToNext != -1 && connectionToNext <= 1) connectionToPrevious = 0;
                    if (connectionToPrevious != -1 && connectionToPrevious >= 2) connectionToPrevious = 1;
                    if (connectionToNext != -1 && connectionToNext >= 2) connectionToPrevious = 1;

                    if (connectionToNext != -1 && connectionToPrevious == connectionToNext) findedRails.removeAt(i-1);
                    else findedRails.removeAt(i-1);
                }
                else findedRails.removeAt(i-1);
            }

            //check first rail in list
            if (findedRails.size() > 1 && dynamic_cast<Rail*>(findedRails[0])->getConnection(dynamic_cast<Rail*>(findedRails[1])) == -1)
            {
                findedRails.removeAt(0);
            }
            selectedTrain->addNextPartOfPath(findedRails);
            selectedTrain->setActualSpeed(selectedTrain->getActualSpeed()+1);
        }
        else qDebug() << "the path was not found!";
    }
}

void TrainSelector::findNearestTrain()
{
    Train* retestedNearestTrain = nullptr;
    int distance;
    (nearestTrain == nullptr) ? distance = 9999999 : distance = getDistance(getLocation(), nearestTrain->getLocation());
    for (auto actor : actorsInCollision)
    {
        if (dynamic_cast<Train*>(actor))
        {
            Train* testedTrain = dynamic_cast<Train*>(actor);
            int testedDistance = getDistance(getLocation(), testedTrain->getLocation());
            if (distance >= testedDistance)
            {
                distance = testedDistance;
                retestedNearestTrain = testedTrain;
            }
        }
    }
    if(nearestTrain == nullptr && retestedNearestTrain != nullptr)
    {
        nearestTrain = retestedNearestTrain;
        nearestTrain->selectTrain(true);
    }
    else if (retestedNearestTrain != nullptr && nearestTrain != nullptr && retestedNearestTrain != nearestTrain)
    {
        nearestTrain->selectTrain(false);
        nearestTrain = retestedNearestTrain;
        nearestTrain->selectTrain(true);
    }
    else if (nearestTrain != nullptr && retestedNearestTrain == nullptr)
    {
        nearestTrain->selectTrain(false);
        nearestTrain = nullptr;
    }
}

void TrainSelector::findNearestSignal()
{
    int nearestSignalDistance = 99999999;
    Signal* retestedNearestSignal = nullptr;
    //try to find nearest signal (from picture location!)
    for (auto actor : actorsInCollision)
    {
        if (dynamic_cast<Rail*>(actor))
        {
            Rail* nearRail = dynamic_cast<Rail*>(actor);
            if (nearRail->getOccupied()) continue;

            int testedDistance = 99999999;

            int testedRailEnd = 0;
            while(testedRailEnd < 2)
            {
                if (nearRail->getSignal(testedRailEnd) != nullptr)
                {
                    testedDistance = getDistance(getLocation(), nearRail->getSignal(testedRailEnd)->getLocation());
                    if (testedDistance < nearestSignalDistance)
                    {
                        nearestSignalDistance = testedDistance;
                        retestedNearestSignal = nearRail->getSignal(testedRailEnd);
                    }
                }
                testedRailEnd++;
            }
        }
    }
    if(nearestSignal == nullptr && retestedNearestSignal != nullptr)
    {
        nearestSignal = retestedNearestSignal;
        nearestRail = dynamic_cast<Rail*>(retestedNearestSignal->getRailActor());
        nearestRail->setVisualOccupied(true);
        nearestSignal->setState(nearestSignal->getState(), FULL_SIGNAL_SPRITE);
    }
    else if (retestedNearestSignal != nullptr && nearestSignal != nullptr && retestedNearestSignal != nearestSignal)
    {
        qDebug() << "need set signalstate correctly";
        nearestSignal->setState(nearestSignal->getState(), RED_SIGNAL_SPRITE); //NEED CHANGE TO TRUE VISUAL STATE - NOT RED ONLY
        nearestRail->setVisualOccupied(false);

        nearestSignal = retestedNearestSignal;
        nearestRail = dynamic_cast<Rail*>(retestedNearestSignal->getRailActor());
        nearestSignal->setState(nearestSignal->getState(), FULL_SIGNAL_SPRITE);
        nearestRail->setVisualOccupied(true);
    }
    else if (nearestSignal != nullptr && retestedNearestSignal == nullptr)
    {
        qDebug() << "need set signalstate correctly";
        nearestSignal->setState(nearestSignal->getState(),RED_SIGNAL_SPRITE); //NEED CHANGE TO TRUE VISUAL STATE - NOT RED ONLY
        nearestSignal = nullptr;
        nearestRail->setVisualOccupied(false);
    }
}

void TrainSelector::unselectSignal()
{
    //called when train path is set
    nearestRail = nullptr;
    qDebug() << "need set signalstate correctly";
    nearestSignal->setState(nearestSignal->getState(), RED_SIGNAL_SPRITE); //NEED CHANGE TO TRUE VISUAL STATE - NOT RED ONLY
    nearestSignal = nullptr;
}

void TrainSelector::calledCollisionEvent(const QList<Actor *> isInCollision)
{
    Actor::calledCollisionEvent(isInCollision); //re-fill actors in collide list and run functions "actorEnterInCollision and actorLeaveFromCollision"
}

void TrainSelector::actorLeaveFromCollision(Actor *actor)
{;
    Actor::actorLeaveFromCollision(actor); //remove actor from list
}

void TrainSelector::actorEnterInCollision(Actor *actor)
{
    Actor::actorEnterInCollision(actor); //add actor to list
}

TrainSelector::~TrainSelector()
{
    if(nearestTrain != nullptr) nearestTrain->selectTrain(false);
    if(nearestSignal != nullptr) nearestSignal->setState(nearestSignal->getState(),RED_SIGNAL_SPRITE);
    if (nearestRail != nullptr) nearestRail->setVisualOccupied(false);
}
