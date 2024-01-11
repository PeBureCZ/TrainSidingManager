#include "railselector.h"

RailSelector::RailSelector(QObject* parent, QGraphicsItem* newGraphicItem, Actor *actorToConstructing)
:
    SelectConstructor(parent, newGraphicItem, actorToConstructing)
{
    nearestRail = nullptr;
    nearestPoint = -1;
}

void RailSelector::callSelectEvent(QPoint point)
{
    qDebug() << "try";
    if (nearestRail != nullptr && nearestPoint != -1)
    {
        if (nearestPoint == 1)
        {
            if (nearestRail->getLined())
            {
                qDebug() << "newLoc";

                QPoint newP0 = nearestRail->getLocation();
                QPoint newP3 = point - nearestRail->getLocation();

                QPoint newP1 = {newP3.x()/2,newP3.y()/2};
                QPoint newP2 = newP1;

                nearestRail->moveRailPoint(newP0, newP1, newP2, newP3);
            }
            else
            {

            }

        }

    }
}

void RailSelector::calledCollisionEvent(const QList<Actor *> isInCollision)
{
    Actor::calledCollisionEvent(isInCollision); //re-fill actors in collide list and run functions "actorEnterInCollision and actorLeaveFromCollision"
    int testedNearestPoint = -1;
    int distance = 99999999;
    Rail* testedNearestRail = nullptr;

    //try to find nearest area (end of actual rail)
    for (auto actor : actorsInCollision)
    {
        if (dynamic_cast<Rail*>(actor))
        {
            Rail* rail = dynamic_cast<Rail*>(actor);
            QPoint testedPoint1 = rail->getP0WorldLocation().toPoint();
            QPoint testedPoint2 = (rail->getP0WorldLocation() + rail->getP3RelativeLocation()).toPoint();
            int testedDistance1 = getDistance(location, testedPoint1);
            int testedDistance2 = getDistance(location, testedPoint2);
            if (distance > testedDistance1 && testedDistance1 <= testedDistance2)
            {
                distance = testedDistance1;
                testedNearestPoint = 0;
                testedNearestRail = rail;
            }
            else if (distance > testedDistance2 && testedDistance2 < testedDistance1)
            {
                distance = testedDistance2;
                testedNearestPoint = 1;
                testedNearestRail = rail;
            }
        }
    }

    //check nearest conected rails (if rail exist in the same point/area)
    if (testedNearestPoint != -1)
    {
        Rail* retestedRail = nullptr;
        QPoint retestedPoint;
        int testedDistance = 99999999;
        for (int i = 0; i < 2; i++)
        {
            int conectionValue = i;
            if (testedNearestPoint == 1) conectionValue +=2;
            if(testedNearestRail->getConnectedRail(conectionValue) != nullptr)
            {
                retestedRail = testedNearestRail->getConnectedRail(conectionValue);
                retestedPoint = dynamic_cast<QGraphicsPathItem*>(retestedRail->getGraphicItem())->path().pointAtPercent(0.01f).toPoint() + retestedRail->getLocation();
                testedDistance = getDistance(location, retestedPoint);
                if (distance > testedDistance)
                {
                    testedNearestPoint = 0;
                    testedNearestRail = retestedRail;
                    distance = testedDistance;
                }
                retestedPoint = dynamic_cast<QGraphicsPathItem*>(retestedRail->getGraphicItem())->path().pointAtPercent(0.99f).toPoint() + retestedRail->getLocation();
                testedDistance = getDistance(location, retestedPoint);
                if (distance > testedDistance)
                {
                    testedNearestPoint = 1;
                    testedNearestRail = retestedRail;
                    distance = testedDistance;
                }
            }
        }
    }

    //if nearestPoint is <= 20, points can be mooved by RailSelector
    (distance <= 20) ? nearestPoint = testedNearestPoint : nearestPoint = -1;

    //set visual change (occupied rail)
    if (testedNearestRail != nullptr)
    {
        if (nearestRail != nullptr)
        {
            if (testedNearestRail != nearestRail)
            {
                nearestRail->setOccupied(false,true);
                nearestRail = testedNearestRail;
                nearestRail->setOccupied(true,true);
            }
            //else = no change
        }
        else
        {
            nearestRail = testedNearestRail;
            nearestRail->setOccupied(true,true);
        }
    }
    else
    {
        if (nearestRail != nullptr) nearestRail->setOccupied(false,true);
        nearestRail = nullptr;
    }
}

void RailSelector::actorLeaveFromCollision(Actor *actor)
{
    Actor::actorLeaveFromCollision(actor);
    Rail* rail = dynamic_cast<Rail*>(actor);
    rail->setOccupied(false,true);
    rail->setVisibilityOfArea(0, false, nullptr);
    rail->setVisibilityOfArea(1, false, nullptr);
}

void RailSelector::actorEnterInCollision(Actor *actor)
{
    Actor::actorEnterInCollision(actor);
    if (dynamic_cast<Rail*>(actor))
    {
        Rail* rail = dynamic_cast<Rail*>(actor);
        rail->setVisibilityOfArea(0, true, Qt::red);
        rail->setVisibilityOfArea(1, true, Qt::red);
    }
}

RailSelector::~RailSelector()
{
}
