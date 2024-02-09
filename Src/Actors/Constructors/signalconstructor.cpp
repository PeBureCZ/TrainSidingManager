#include "signalconstructor.h"

SignalConstructor::SignalConstructor(QObject* parent, QGraphicsItem* newGraphicItem, Actor *actorToConstructing)
    : RailobjectConstructor(parent, newGraphicItem, actorToConstructing)
{
    nearestAreaGraphicItem = nullptr;
    nearestEndArea = -1;
    nearestRail = nullptr;
}

void SignalConstructor::actualizeConstructor(QPoint newPoint)
{
    QPoint slideLocation = {5,-50};
    setLocation(newPoint + slideLocation, true);
}

void SignalConstructor::calledCollisionEvent(const QList<Actor*> isInCollision)
{
    Actor::calledCollisionEvent(isInCollision); //re-fill actors in collide list and run functions "actorEnterInCollision and actorLeaveFromCollision"
    int testedNearestEndArea = -1;
    int distance = 99999999;
    Rail* testedNearestRail = nullptr;
    QPoint correctedLocation = location + QPoint(-5,50); //graphics is slided

    //try to find nearest area (end of actual rail)
    for (auto actor : actorsInCollision)
    {
        Rail* rail = dynamic_cast<Rail*>(actor);
        QPoint testedPoint1 = rail->getP0WorldLocation().toPoint();
        QPoint testedPoint2 = (rail->getP0WorldLocation() + rail->getP3RelativeLocation()).toPoint();
        int testedDistance1 = getDistance(correctedLocation, testedPoint1);
        int testedDistance2 = getDistance(correctedLocation, testedPoint2);
        if (distance > testedDistance1 && testedDistance1 <= testedDistance2)
        {
            distance = testedDistance1;
            testedNearestEndArea = 0;
            testedNearestRail = rail;
        }
        else if (distance > testedDistance2 && testedDistance2 < testedDistance1)
        {
            distance = testedDistance2;
            testedNearestEndArea = 1;
            testedNearestRail = rail;
        }
    }

    //check nearest conected rails (if rail exist in the same point/area)
    if (testedNearestEndArea != -1)
    {
        Rail* retestedRail = nullptr;
        QPoint retestedPoint;
        int testedDistance = 99999999;
        for (int i = 0; i < 2; i++)
        {
            int conectionValue = i;
            if (testedNearestEndArea == 1) conectionValue +=2;
            if(testedNearestRail->getConnectedRail(conectionValue) != nullptr)
            {
                retestedRail = testedNearestRail->getConnectedRail(conectionValue);
                int newTestedNearestPoint = (retestedRail->getConnection(testedNearestRail)+2)/2-1; //transfer connection point(0-3) to endPoint (0-1)
                retestedPoint = dynamic_cast<QGraphicsPathItem*>(retestedRail->getGraphicItem())->path().pointAtPercent(0.01f).toPoint() + retestedRail->getLocation();
                testedDistance = getDistance(correctedLocation, retestedPoint);
                if (distance > testedDistance)
                {
                    testedNearestRail = retestedRail;
                    testedNearestEndArea = newTestedNearestPoint;
                    distance = testedDistance;
                }
                retestedPoint = dynamic_cast<QGraphicsPathItem*>(retestedRail->getGraphicItem())->path().pointAtPercent(0.99f).toPoint() + retestedRail->getLocation();
                testedDistance = getDistance(correctedLocation, retestedPoint);
                if (distance > testedDistance)
                {
                    testedNearestRail = retestedRail;
                    testedNearestEndArea = newTestedNearestPoint;
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
    if (nearestRail != nullptr && testedNearestEndArea != -1 && distance <= 120)
    {
        QGraphicsItem* areaItem = nearestRail->getAreaGraphic(testedNearestEndArea);
        if (nearestAreaGraphicItem != areaItem && nearestAreaGraphicItem != nullptr)
        {
            QPen newPen(Qt::red);
            newPen.setWidth(3);
            dynamic_cast<QGraphicsPathItem*>(nearestAreaGraphicItem)->setPen(newPen);
            nearestAreaGraphicItem->setZValue(0);
        }   
        if (areaItem != nullptr && nearestAreaGraphicItem != areaItem)
        {
            QPen newPen(Qt::green);
            newPen.setWidth(3);
            nearestRail->setVisibilityOfArea(testedNearestEndArea, true, Qt::green);
            areaItem->setZValue(3);
        }
        nearestAreaGraphicItem = areaItem;
    }
    else if (nearestAreaGraphicItem != nullptr)
    {
        QPen newPen(Qt::red);
        newPen.setWidth(3);
        dynamic_cast<QGraphicsPathItem*>(nearestAreaGraphicItem)->setPen(newPen);
        nearestAreaGraphicItem->setZValue(0);
        nearestAreaGraphicItem = nullptr;
    }
    nearestEndArea = testedNearestEndArea;
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

int SignalConstructor::getNearestEndArea()
{
    return nearestEndArea;
}

Rail *SignalConstructor::getNearestRail()
{
    return nearestRail;
}

QGraphicsItem *SignalConstructor::getNearestAreaGraphic()
{
    return nearestAreaGraphicItem;
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


