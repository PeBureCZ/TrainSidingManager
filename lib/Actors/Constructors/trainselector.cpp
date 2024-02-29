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
    RailNavigation::makePath(selectedTrain, getNearestSignal());
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
