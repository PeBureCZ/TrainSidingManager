#include "signalconstructor.h"

SignalConstructor::SignalConstructor(QObject* parent, QGraphicsItem* newGraphicItem, Actor *actorToConstructing)
    : RailobjectConstructor(parent, newGraphicItem, actorToConstructing)
{
    nearestArea = nullptr;
    nearestRail = nullptr;
}

void SignalConstructor::actualizeConstructor(QPoint newPoint)
{
    //QPoint slideLocation = {5,-50};
    QPoint slideLocation = {0,0};
    setLocation(newPoint + slideLocation, true);
    actualizeGraphicLocation();
}

void SignalConstructor::actorCollide(const QList<Actor*> isInCollision)
{
    Actor::actorCollide(isInCollision); //re-fill actors in collide list and run functions "actorEnterInCollision and actorLeaveFromCollision"
    int nearestPoint = -1;
    int distance = 99999999;
    Rail* testedNearestRail = nullptr;
    QPoint correctedLocation = location + QPoint(0,0);

    //try to find nearest area (end of actual rail)
    for (auto actor : actorsInCollision)
    {
        //try to find nearest area (end of rail)
        Rail* rail = dynamic_cast<Rail*>(actor);

        QPoint testedPoint1 = rail->getP0WorldLocation().toPoint();
        QPoint testedPoint2 = (rail->getP0WorldLocation() + rail->getP3RelativeLocation()).toPoint();
        int testedDistance1 = getDistance(correctedLocation, testedPoint1);
        int testedDistance2 = getDistance(correctedLocation, testedPoint2);
        if (distance > testedDistance1 && testedDistance1 <= testedDistance2)
        {
            distance = testedDistance1;
            nearestPoint = 0;
            testedNearestRail = rail;
        }
        else if (distance > testedDistance2 && testedDistance2 < testedDistance1)
        {
            distance = testedDistance2;
            nearestPoint = 1;
            testedNearestRail = rail;
        }
    }

    //check nearest conected rails (= rail exist in the same point/area)
    if (nearestPoint != -1)
    {
        Rail* retestedRail = nullptr;
        QPoint retestedPoint;
        int testedDistance = 99999999;
        for (int i = 0; i < 2; i++)
        {
            int conectionValue = i;
            if (nearestPoint == 1) conectionValue +=2;
            if(testedNearestRail->getConnectedRail(conectionValue) != nullptr)
            {
                retestedRail = testedNearestRail->getConnectedRail(conectionValue);
                retestedPoint = dynamic_cast<QGraphicsPathItem*>(retestedRail->getGraphicItem())->path().pointAtPercent(0.01f).toPoint() + retestedRail->getLocation();
                testedDistance = getDistance(correctedLocation, retestedPoint);
                if (distance > testedDistance)
                {
                    testedNearestRail = retestedRail;
                    distance = testedDistance;
                }
                retestedPoint = dynamic_cast<QGraphicsPathItem*>(retestedRail->getGraphicItem())->path().pointAtPercent(0.99f).toPoint() + retestedRail->getLocation();
                testedDistance = getDistance(correctedLocation, retestedPoint);
                if (distance > testedDistance)
                {
                    testedNearestRail = retestedRail;
                    distance = testedDistance;
                }
            }
        }
    }

    //set visual change (occupied rail)
    if (testedNearestRail != nullptr)
    {
        if (nearestRail != nullptr && testedNearestRail != nearestRail) nearestRail->setOccupied(false,true);
        nearestRail = testedNearestRail;
        nearestRail->setOccupied(true,true);
    }
    else if (nearestRail != nullptr)
    {
        nearestRail->setOccupied(false,true);
        nearestRail = nullptr;
    }

    //set visual area of nearest rail
    if (nearestRail != nullptr && nearestPoint != -1 && distance <= 120)
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
    rail->setOccupied(false,true);
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

bool SignalConstructor::holdRail()
{
    if (nearestArea != nullptr) return true;
    return false;
}

SignalConstructor::~SignalConstructor()
{
    for (auto railActor : actorsInCollision)
    {
        Rail* rail = dynamic_cast<Rail*>(railActor);
        rail->setVisibilityOfArea(0, false, nullptr);
        rail->setVisibilityOfArea(1, false, nullptr);
    }
    if (nearestRail != nullptr) nearestRail->setOccupied(false,true);
}


