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
    if (nearestTrain != nullptr) unselectSignal();
    if (selectedTrain->getAutopilot())
    {
        selectedTrain->recalculateRemainToPathEnd();
        selectedTrain->setTravelDistance(selectedTrain->getRemainToPathEnd());
        if (selectedTrain->getRemainToPathEnd() > 50 && selectedTrain->getActualSpeed() == 0.0f) selectedTrain->setActualSpeed(1.0f);
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
            if (nearestTrain->getShunt() && nearRail->getShuntAllowed() == false) continue;
            else if (!nearestTrain->getShunt() && nearRail->getOccupied()) continue;

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
    using namespace customQColors;
    if(nearestSignal == nullptr && retestedNearestSignal != nullptr)
    {
        nearestSignal = retestedNearestSignal;
        nearestRail = dynamic_cast<Rail*>(retestedNearestSignal->getRailActor());
        nearestRail->setRailColor(SELECTED_RAIL_COLOR, SELECTED_RAIL_LAYER);
        nearestSignal->setState(nearestSignal->getState(), SELECTED_SIGNAL_SPRITE);
        nearestSignal->setLocation(nearestSignal->getLocation()+QPoint(-17,-12),true);
    }
    else if (retestedNearestSignal != nullptr && nearestSignal != nullptr && retestedNearestSignal != nearestSignal)
    {
        nearestSignal->setState(nearestSignal->getState(), STOP_SIGNAL_SPRITE); //NEED CHANGE TO TRUE VISUAL STATE - NOT RED ONLY
        nearestSignal->setLocation(nearestSignal->getLocation()+QPoint(17,12),true);
        nearestRail->setRailColor(DEFAULT_RAIL_COLOR, UNSELECTED_RAIL_LAYER);

        nearestSignal = retestedNearestSignal;
        nearestRail = dynamic_cast<Rail*>(retestedNearestSignal->getRailActor());
        nearestSignal->setState(nearestSignal->getState(), SELECTED_SIGNAL_SPRITE);
        nearestSignal->setLocation(nearestSignal->getLocation()+QPoint(-17,-12),true);
        nearestRail->setRailColor(SELECTED_RAIL_COLOR, SELECTED_RAIL_LAYER);
    }
    else if (nearestSignal != nullptr && retestedNearestSignal == nullptr)
    {
        nearestSignal->setState(nearestSignal->getState(),STOP_SIGNAL_SPRITE); //NEED CHANGE TO TRUE VISUAL STATE - NOT RED ONLY
        nearestSignal->setLocation(nearestSignal->getLocation()+QPoint(17,12),true);
        nearestSignal = nullptr;
        if (nearestRail->getOccupied()) nearestRail->setRailColor(OCCUPIED_RAIL_COLOR, SELECTED_RAIL_LAYER);
        else nearestRail->setRailColor(DEFAULT_RAIL_COLOR, UNSELECTED_RAIL_LAYER);
    }
}

void TrainSelector::unselectSignal()
{
    //called when train path is set
    nearestRail = nullptr;
    nearestSignal->setState(nearestSignal->getState(), STOP_SIGNAL_SPRITE); //NEED CHANGE TO TRUE VISUAL STATE - NOT RED ONLY
    nearestSignal->setLocation(nearestSignal->getLocation()+QPoint(17,12),true);
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
    using namespace customQColors;
    if(nearestTrain != nullptr) nearestTrain->selectTrain(false);
    if(nearestSignal != nullptr) nearestSignal->setState(nearestSignal->getState(),STOP_SIGNAL_SPRITE);
    if (nearestRail != nullptr)
    {
        if (nearestRail->getOccupied()) nearestRail->setRailColor(OCCUPIED_RAIL_COLOR, SELECTED_RAIL_LAYER);
        else nearestRail->setRailColor(DEFAULT_RAIL_COLOR, UNSELECTED_RAIL_LAYER);
    }
}
