#include "signalconstructor.h"

SignalConstructor::SignalConstructor(QObject* parent, QGraphicsItem* newGraphicItem, Actor *actorToConstructing)
    : RailobjectConstructor(parent, newGraphicItem, actorToConstructing)
{

    nearestArea = nullptr;
}

void SignalConstructor::actualizeConstructor(QPoint newPoint)
{
    QPoint slideLocation = {5,-50};
    setLocation(newPoint + slideLocation, true);
    actualizeGraphicLocation();
}

void SignalConstructor::actorCollide(const QList<Actor*> isInCollision)
{
    Actor::actorCollide(isInCollision); //re-fill actors in collide list and run functions "leave or enter actors"

    Rail* nearestRail = nullptr;
    int nearestPoint = -1;
    int distance = 120;

    //try to find nearest area (end of rail)
    for (auto actor : actorsInCollision)
    {
        //try to find nearest area (end of rail)
        Rail* rail = dynamic_cast<Rail*>(actor);
        QPoint testedPoint1 = rail->getP0WorldLocation().toPoint();
        QPoint testedPoint2 = (rail->getP0WorldLocation() + rail->getP3RelativeLocation()).toPoint();
        int testedDistance1 = getDistance(location, testedPoint1);
        int testedDistance2 = getDistance(location, testedPoint2);

        if (distance >= testedDistance1 && testedDistance1 <= testedDistance2)
        {
            distance = testedDistance1;
            nearestPoint = 0;
            nearestRail = rail;
        }
        else if (distance > testedDistance2 && testedDistance2 < testedDistance1)
        {
            distance = testedDistance2;
            nearestPoint = 1;
            nearestRail = rail;
        }
    }

    if (nearestRail != nullptr && nearestPoint != -1)
    {
        QGraphicsItem* areaItem = nearestRail->getAreaGraphic(nearestPoint);
        if (nearestArea != areaItem && nearestArea != nullptr)
        {
            QPen newPen(Qt::red);
            newPen.setWidth(3);
            dynamic_cast<QGraphicsPathItem*>(nearestArea)->setPen(newPen);
            nearestArea->setZValue(0);
        }
        nearestArea = areaItem;
        if (nearestArea != nullptr) nearestRail->setVisibilityOfArea(nearestPoint, true, Qt::green);
    }
    else if (nearestArea != nullptr)
    {
        QPen newPen(Qt::red);
        newPen.setWidth(3);
        dynamic_cast<QGraphicsPathItem*>(nearestArea)->setPen(newPen);
        nearestArea->setZValue(0);
        nearestArea = nullptr;
    }
}

void SignalConstructor::actorLeaveFromCollision(Actor *actor)
{
    Actor::actorLeaveFromCollision(actor); //remove actor from list
    Rail* rail = dynamic_cast<Rail*>(actor);
    rail->setVisibilityOfArea(0, false, nullptr);
    rail->setVisibilityOfArea(1, false, nullptr);
}

void SignalConstructor::actorEnterInCollision(Actor *actor)
{
    Actor::actorEnterInCollision(actor); //add actor to list
    if (dynamic_cast<Rail*>(actor))
    {
        Rail* rail = dynamic_cast<Rail*>(actor);
        rail->setVisibilityOfArea(0, true, Qt::red);
        rail->setVisibilityOfArea(1, true, Qt::red);
    }
}

void SignalConstructor::freeHoldedRail()
{
    for (auto railActor : actorsInCollision)
    {
        Rail* rail = dynamic_cast<Rail*>(railActor);
        rail->setVisibilityOfArea(0, false, nullptr);
        rail->setVisibilityOfArea(1, false, nullptr);
    }
    actorsInCollision.clear();
    nearestArea = nullptr;
}

bool SignalConstructor::holdRail()
{
    if (nearestArea != nullptr) return true;
    return false;
}

SignalConstructor::~SignalConstructor()
{
    freeHoldedRail();
}


