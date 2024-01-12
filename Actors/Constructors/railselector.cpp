#include "railselector.h"

RailSelector::RailSelector(QObject* parent, QGraphicsItem* newGraphicItem, Actor *actorToConstructing)
:
    SelectConstructor(parent, newGraphicItem, actorToConstructing)
{
    nearestRail = nullptr;
    nearestPoint = -1;
    qDebug() << "need add boxColider update!";
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
        else
        {
            bool isNear = (250 >= getDistance(point, nearestRail->getLocation()));
            if (nearestRail->getLined() && isNear)
            {
                QPoint P3world = nearestRail->getLocation() + nearestRail->getP3RelativeLocation().toPoint();
                QPoint newP0 = point;
                QPoint newP3 = P3world - newP0;

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
}

void RailSelector::resetObjectBoxCollider()
{
    if (nearestRail == nullptr) return;
    BoxCollider* boxCollider = {};
    for (auto trigger : nearestRail->getAllTriggers())
    {
        if (dynamic_cast<BoxCollider*>(trigger))
        {
            boxCollider = dynamic_cast<BoxCollider*>(trigger);
            break;
        }
    }
    if (boxCollider != nullptr)
    {
        //get and make rotation
        QPoint copyOfP3 = nearestRail->getP3RelativeLocation().toPoint();
        float radian = atan2(static_cast<double>(copyOfP3.y()),copyOfP3.x());
        float basicRotation = qRadiansToDegrees(radian);
        float correctedRotation = fmod(360 - basicRotation, 360);

        QTransform rotationTransform;
        rotationTransform.rotate(correctedRotation);

        QVector<QPoint> relativeLocations = {};

        //make 10 points on path declare box (still in "rotated" coordinate)
        for (int i = 0; i <= 10; i++)
        {
            float percent = i*0.1f;
            relativeLocations.push_back(dynamic_cast<QGraphicsPathItem*>(nearestRail->getGraphicItem())->path().pointAtPercent(percent).toPoint()); //relative
        }

        //make points "unrotated" to check bounds
        for (auto &point : relativeLocations)
        {
            point = rotationTransform.map(point);
        }

        //make size of box
        int maxX = 0;
        int minX = 0;
        int maxY = 0;
        int minY = 0;
        for (auto point : relativeLocations)
        {
            if (maxX < point.x()) maxX = point.x();
            if (minX > point.x()) minX = point.x();
            if (maxY < point.y()) maxY = point.y();
            if (minY > point.y()) minY = point.y();
        }

        maxX += 40; //decimeters
        minX -= 40; //decimeters
        maxY += 40; //decimeters
        minY -= 40; //decimeters

        QPoint leftUpCorner = {minX, minY};
        QPoint rightDownCorner = {maxX, maxY};

        //set coordination and rotations
        boxCollider->setBoxCollider(leftUpCorner, rightDownCorner, correctedRotation);
    }
}

RailSelector::~RailSelector()
{
    if (nearestRail != nullptr)
    {
        nearestRail->setOccupied(false,true);
        nearestRail->setVisibilityOfArea(0, false, nullptr);
        nearestRail->setVisibilityOfArea(1, false, nullptr);
    }
}


