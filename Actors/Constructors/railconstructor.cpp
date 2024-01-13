#include "railconstructor.h"

RailConstructor::RailConstructor
    (QObject* parent, QGraphicsItem* newGraphicItem, Actor *actorToConstructing)
    : ActorConstructor(parent, newGraphicItem, actorToConstructing)
{
    P0 = {0,0};
    P1 = {0,0};
    P2 = {0,0};
    P3 = {0,0};

    ownedRail = nullptr;
    connectedRail = nullptr;
    ownedPath = nullptr;
    lined = true;
    nearestRail = nullptr;
}

void RailConstructor::actualizePathVisual()
{
    ownedPath->setPos(P0.x(),P0.y());
    QPainterPath customPath;
    customPath.cubicTo(P1.x(),P1.y(),P2.x(), P2.y(),P3.x(), P3.y());
    ownedPath->setPath(customPath);
}

void RailConstructor::actualizeRail()
{
    ownedRail->setP0WorldLocation(P0); //ABSOLUTE
    ownedRail->setP1RelativeLocation(P1); //RELATIVE
    ownedRail->setP2RelativeLocation(P2); //RELATIVE
    ownedRail->setP3RelativeLocation(P3); //RELATIVE
}

void RailConstructor::smoothEndPoint()
{
    if (ownedRail != nullptr) ownedRail->smoothConnectionC1();
}

void RailConstructor::actualizeConstructor(QPoint newPoint)
{
    if (ownedRail != nullptr)
    {
        actualizeRail();
        setPoints(newPoint);
        actualizePathVisual();
        if (ownedRail->getAllTriggers().size() > 0)
        {
            dynamic_cast<Component*>(ownedRail->getAllTriggers()[1])->setRelativeLocation(newPoint - ownedRail->getLocation()); //p3 trigger
        }
    }
    else
    {
        setLocation(newPoint,true);
    }
}

void RailConstructor::calledCollisionEvent(const QList<Actor *> isInCollision)
{
    Actor::calledCollisionEvent(isInCollision); //re-fill actors in collide list and run functions "actorEnterInCollision and actorLeaveFromCollision"
    int nearestPoint = -1;
    int distance = 99999999;
    Rail* testedNearestRail = nullptr;
    QPoint correctedLocation = location;
    if (ownedPath != nullptr) correctedLocation += ownedRail->getP3RelativeLocation().toPoint();

    //try to find nearest area (end of actual rail)
    for (auto actor : actorsInCollision)
    {
        if (dynamic_cast<Rail*>(actor) && actor != ownedRail)
        {
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
    }

    //check nearest conected rails (if rail exist in the same point/area)
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

void RailConstructor::actorLeaveFromCollision(Actor *actor)
{
    Actor::actorLeaveFromCollision(actor);
    Rail* rail = dynamic_cast<Rail*>(actor);
    rail->setOccupied(false,true);
    rail->setVisibilityOfArea(0, false, nullptr);
    rail->setVisibilityOfArea(1, false, nullptr);
}

void RailConstructor::actorEnterInCollision(Actor *actor)
{
    Actor::actorEnterInCollision(actor);
    if (dynamic_cast<Rail*>(actor))
    {
        Rail* rail = dynamic_cast<Rail*>(actor);
        rail->setVisibilityOfArea(0, true, Qt::red);
        rail->setVisibilityOfArea(1, true, Qt::red);
    }
}

void RailConstructor::setPoints(QPoint endP)
{
    //P0 = WORLD, P1-3 = RELATIVE
    int x = endP.x() - location.x();
    int y = endP.y() - location.y();
    P0 = location; //world
    P3 = {x,y}; //relative

    //set P1 and P2
    if (connectedRail == nullptr)
    {
        P1 = {(x)/2,y/2}; //relative
        P2 = P1; //relative
    }
    else   //Béziere path
    {
        QLineF line(P0, P3+location); //line between P0/P3 (Rail being created by this constructor.)
        QPoint connectedP2world;
        (P0 == connectedRail->getLocation()) ? connectedP2world = connectedRail->getLocation() + connectedRail->getP1RelativeLocation().toPoint()
        : connectedP2world = connectedRail->getLocation() + connectedRail->getP2RelativeLocation().toPoint();

        QLineF lineP2(connectedP2world, P0);
        float reduction = line.length() / lineP2.length();
        if (reduction < 0.05f)  reduction = 0.05f;
        QPoint negativeVector = lineP2.pointAt(1-reduction).toPoint();
        QPoint vectorP2world = (location - (negativeVector - location));
        QPoint vectorP2Local = vectorP2world  - location;

        P1 = vectorP2Local / 2; //relative
        P2 = P1; //relative
    }
}

QPointF RailConstructor::getP0Point()
{
    return {P0};
}

QPointF RailConstructor::getP1Point()
{
    return {P1};
}

QPointF RailConstructor::getP2Point()
{
    return {P2};
}

QPointF RailConstructor::getP3Point()
{
    return {P3};
}

Rail *RailConstructor::getOwnedRail()
{
    return ownedRail; //for return actor call "getActorConstructing()"
}

Rail *RailConstructor::getConnectedRail()
{
    return connectedRail;
}

Rail *RailConstructor::getNearestRail()
{
    return nearestRail;
}

void RailConstructor::underConstruction(bool constructingNow)
{
    if (constructingNow) graphicItem->setVisible(false);
    else
    {
        setOwnedRail(nullptr);
        setConnectedRail(nullptr);
        graphicItem->setVisible(true);
    }
}

void RailConstructor::setOwnedRail(Rail *newOwnedRail)
{
    ownedRail = newOwnedRail;
    if (newOwnedRail != nullptr)
    {
        ownedPath = dynamic_cast<QGraphicsPathItem*>(ownedRail->getGraphicItem());
        actorConstructing = dynamic_cast<Actor*>(ownedRail);
    }
    else
    {
        ownedPath = nullptr;
        actorConstructing = nullptr;
    }
}

void RailConstructor::setConnectedRail(Rail *newConnectedRail)
{
    connectedRail = newConnectedRail;
}

RailConstructor::~RailConstructor()
{
    for (auto railActor : actorsInCollision)
    {
        Rail* rail = dynamic_cast<Rail*>(railActor);
        rail->setVisibilityOfArea(0, false, nullptr);
        rail->setVisibilityOfArea(1, false, nullptr);
    }
    if (nearestRail != nullptr) nearestRail->setOccupied(false,true);
}


