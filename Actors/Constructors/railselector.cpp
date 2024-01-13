#include "railselector.h"

RailSelector::RailSelector(QObject* parent, QGraphicsItem* newGraphicItem, Actor *actorToConstructing)
:
    SelectConstructor(parent, newGraphicItem, actorToConstructing)
{
    nearestRail = nullptr;
    nearestPoint = -1;
    visualP1 = nullptr;
    visualP2 = nullptr;
}

void RailSelector::callSelectEvent(QPoint point)
{
    if (nearestRail != nullptr && nearestPoint != -1)
    {
        if (nearestPoint == 1)
        {
            bool isNear = (250 >= getDistance(point, nearestRail->getLocation() + nearestRail->getP3RelativeLocation().toPoint()));
            if (nearestRail->getLined() && isNear)
            {
                nearestRail->setLined(false);

            }
            else if (isNear)
            {
                QPoint oldP1 = nearestRail->getP1RelativeLocation().toPoint();
                QPoint newP0 = nearestRail->getLocation();
                QPoint newP3 = point - nearestRail->getLocation();
                nearestRail->moveRailPoints(newP0, oldP1, oldP1, newP3);
                nearestRail->setObjectBoxCollider();
                visualP1->setPos(oldP1 + nearestRail->getLocation());
                visualP2->setPos(oldP1 + nearestRail->getLocation());
            }
        }
        else
        {
            bool isNear = (250 >= getDistance(point, nearestRail->getLocation()));
            if (nearestRail->getLined() && isNear)
            {
                nearestRail->setLined(false);

            }
            else if (isNear)
            {
                QPoint newP3 = nearestRail->getP3RelativeLocation().toPoint() + nearestRail->getLocation() - point;
                QPoint newP1 = nearestRail->getP1RelativeLocation().toPoint() + nearestRail->getLocation() - point;
                QPoint newP0 = point;
                nearestRail->moveRailPoints(newP0, newP1, newP1, newP3);
                nearestRail->setObjectBoxCollider();
                visualP1->setPos(newP1 + nearestRail->getLocation());
                visualP2->setPos(newP1 + nearestRail->getLocation());
            }
        }
        for (int connection = 0; connection < 4; connection++)
        {
            Rail* connectedRail = nearestRail->getConnectedRail(connection);
            if (connectedRail != nullptr)
            {
                int connectionOf2 = connectedRail->getConnection(nearestRail);
                if (connectionOf2 == 0 || connectionOf2 == 1)
                {
                    connectedRail->smoothConnectionA0();
                }
                else if (connectionOf2 != -1)
                {

                    connectedRail->smoothConnectionC1();
                }
            }
        }
    }
}

void RailSelector::calledCollisionEvent(const QList<Actor *> isInCollision)
{
    Actor::calledCollisionEvent(isInCollision); //re-fill actors in collide list and run functions "actorEnterInCollision and actorLeaveFromCollision
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
    if (testedNearestRail != nullptr && !underSelectMode)
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
    else if (!underSelectMode)
    {
        if (nearestRail != nullptr) nearestRail->setOccupied(false,true);
        nearestRail = nullptr;
    }
}

void RailSelector::actorLeaveFromCollision(Actor *actor)
{
    if (underSelectMode) return;
    Actor::actorLeaveFromCollision(actor);
    Rail* rail = dynamic_cast<Rail*>(actor);
    rail->setOccupied(false,true);
    rail->setVisibilityOfArea(0, false, nullptr);
    rail->setVisibilityOfArea(1, false, nullptr);
}

void RailSelector::actorEnterInCollision(Actor *actor)
{
    if (underSelectMode) return;
    Actor::actorEnterInCollision(actor);
    if (dynamic_cast<Rail*>(actor))
    {
        Rail* rail = dynamic_cast<Rail*>(actor);
        rail->setVisibilityOfArea(0, true, Qt::red);
        rail->setVisibilityOfArea(1, true, Qt::red);
    }
}

void RailSelector::setUnderSelect(bool newUnderSelect)
{
    underSelectMode = newUnderSelect;
    if (underSelectMode)
    {
        for (auto kickedActor : actorsInCollision)
        {
            if (dynamic_cast<Rail*>(kickedActor) != nearestRail)
            {
                actorsInCollision.removeOne(kickedActor);
                Rail* rail = dynamic_cast<Rail*>(kickedActor);
                rail->setOccupied(false,true);
                rail->setVisibilityOfArea(0, false, nullptr);
                rail->setVisibilityOfArea(1, false, nullptr);
            }
        }
    }
    if (visualP1 != nullptr) delete visualP1;
    if (visualP2 != nullptr) delete visualP2;
    if (nearestRail != nullptr)
    {
        QPen pen;
        pen.setWidth(3);
        pen.setColor(Qt::red);
        QPainterPath rect;
        int size = 30;
        rect.addRect(0, 0, size, size);
        visualP1 = new QGraphicsPathItem(rect);
        visualP2 = new QGraphicsPathItem(rect);
        visualP1->setPen(pen);
        visualP2->setPen(pen);
        visualP1->setPos(nearestRail->getP1RelativeLocation() + nearestRail->getLocation());
        visualP2->setPos(nearestRail->getP2RelativeLocation() + nearestRail->getLocation());
    }
    else
    {
        visualP1 = nullptr;
        visualP2 = nullptr;
    }
}

QGraphicsPathItem* RailSelector::getP1VisualPoint()
{
    return visualP1;
}

QGraphicsPathItem* RailSelector::getP2VisualPoint()
{
    return visualP2;
}

void RailSelector::deleteMiddleVisualPoints()
{
    if (visualP1 != nullptr) delete visualP1;
    if (visualP2 != nullptr) delete visualP2;
}

RailSelector::~RailSelector()
{
    if (nearestRail != nullptr)
    {
        nearestRail->setOccupied(false,true);
        nearestRail->setVisibilityOfArea(0, false, nullptr);
        nearestRail->setVisibilityOfArea(1, false, nullptr);
    }
    deleteMiddleVisualPoints();
}


