#include "railconstructor.h"

RailConstructor::RailConstructor
    (QGraphicsItem* newGraphicItem, Actor *actorToConstructing, QPoint spawnPos, Rail* connectedRail)
    : ActorConstructor(newGraphicItem,actorToConstructing)
{
    ownedRail = dynamic_cast<Rail*>(actorConstructing);
    connectedRailActor = connectedRail;
    ownedPath = dynamic_cast<QGraphicsPathItem*>(dynamic_cast<Actor*>(ownedRail)->getGraphicItem());
    location = spawnPos;
    P0 = {0,0};
    P1 = {0,0};
    P2 = {0,0};
    P3 = {0,0};

    if (connectedRail == nullptr)
    {
        lined = true;
    }
    else
    {
        lined = false;
        ownedRail->connectRails(connectedRail,true);
        ownedRail->setLined(false);
    }
}

void RailConstructor::actualizePathVisual() // NEED REBUILD
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
    ownedRail->smoothP3PointByC1();
}

void RailConstructor::actualizeConstructor(QPoint newPoint)
{
    actualizeRail();
    setPoints(newPoint);
    actualizePathVisual();
    if (ownedRail->getAllTriggers().size() > 0)
    {
        dynamic_cast<Component*>(ownedRail->getAllTriggers()[1])->setRelativeLocation(newPoint - ownedRail->getLocation()); //p3 trigger
    }
}

QString RailConstructor::testFce()
{
    return QString::number(P3.x());
}

void RailConstructor::setPoints(QPoint endP)
{
    //P0 = WORLD, P1-3 = RELATIVE
    int x = endP.x() - location.x();
    int y = endP.y() - location.y();
    P0 = location; //world
    P3 = {x,y}; //relative

    //set P1 and P2
    if (connectedRailActor == nullptr)
    {
        P1 = {(x)/2,y/2}; //relative
        P2 = P1; //relative
    }
    else   //Béziere path
    {
        /*
        QLineF line(location, {static_cast<qreal>(x),static_cast<qreal>(y)}); //line between P0/P3 (Rail being created by this constructor.)
        QPoint connectedP2world = connectedRailActor->getLocation() + connectedRailActor->getP2RelativeLocation().toPoint();

        //float pathReduction = connectedRailActor->getRailLength() / line.length();
        QPoint vectorP2world =(location - (connectedP2world - location));
        QPoint testPoint = (vectorP2world-location) + location;
        QPoint vectorP2Local = testPoint - location;
        P0 = location;
        P1 = vectorP2Local; //relative
        P2 = P1; //relative
        P3 = {x,y};
        */

        QLineF line(P0, P3+location); //line between P0/P3 (Rail being created by this constructor.)

        QPoint connectedP1world = connectedRailActor->getLocation() + connectedRailActor->getP1RelativeLocation().toPoint();
        QPoint connectedP3world = connectedRailActor->getLocation() + connectedRailActor->getP3RelativeLocation().toPoint();

        QLineF lineP2(connectedP1world, connectedP3world);

        float reduction = line.length() / lineP2.length();
        if (reduction < 0.05f)  reduction = 0.05f;
        QPoint negativeVector = lineP2.pointAt(1-reduction).toPoint();
        QPoint vectorP2world = (location - (negativeVector - location));
        QPoint vectorP2Local = vectorP2world  - location;
        P0 = location;
        P1 = vectorP2Local; //relative
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
    return dynamic_cast<Rail*>(ownedRail);
}

Rail *RailConstructor::getConnectedRail()
{
    return connectedRailActor;
}

RailConstructor::~RailConstructor()
{
}


