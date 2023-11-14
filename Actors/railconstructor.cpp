#include "railconstructor.h"

RailConstructor::RailConstructor
    (QGraphicsItem* newGraphicItem, Actor *actorToConstructing, QPoint spawnPos, Rail* connectedRail, int connection)
    : ActorConstructor(newGraphicItem,actorToConstructing)
{
    ownedRail = dynamic_cast<Rail*>(actorToConstructing);
    ownedPath = dynamic_cast<QGraphicsPathItem*>(dynamic_cast<Actor*>(ownedRail)->getGraphicItem());
    location = spawnPos;
    P0 = {0,0};
    P1 = {0,0};
    P2 = {0,0};
    P3 = {0,0};

    if (connectedRail == nullptr)
    {
        lined = true;
        connectedRailA0 = {}; //connection 0
        connectedRailB0 = {}; //connection 1
        connectedRailC1 = {}; //connection 2
        connectedRailD1 = {}; //connection 3
        startAtSpawnPos = true; //define if start (percent 0 in percentRange 0-1) is at spawn position (=click pos) or at "tick mouse target" position
    }
    else
    {
        lined = false;
        startAtSpawnPos = false;  //define if start (percent 0 in percentRange 0-1) is at spawn position (=click pos) or at "tick mouse target" position
        switch (connection)
        {
            case 0:
            {
                connectedRailA0 = connectedRail; //connection 0
                break;
            }
            case 1:
            {
                connectedRailB0 = connectedRail; //connection 1
                break;
            }
            case 2:
            {
                connectedRailC1 = connectedRail; //connection 2
                break;
            }
            case 3:
            {
                connectedRailD1 = connectedRail; //connection 3
                break;
            }
            default:
            {
                connectedRailA0 = connectedRail; //connection 0
            }
        }
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
    ownedRail->setP0(P0); //ABSOLUTE
    ownedRail->setP1(P1); //RELATIVE
    ownedRail->setP2(P2); //RELATIVE
    ownedRail->setP3(P3); //RELATIVE
}

void RailConstructor::actualizeConstructor(QPoint newPoint)
{
    actualizeRail(); //refact?! Actualize rail every tick - but it´s not necessary (only once at the end is sufficient)
    setPoints(newPoint);
    actualizePathVisual();
    if (ownedRail->getAllTriggers().size() > 0)
    {
        dynamic_cast<Component*>(ownedRail->getAllTriggers()[1])->setRelativeLocation(newPoint - ownedRail->getLocation()); //p3 trigger
        qDebug() << "actualize rel. loc.";
    }
}

QString RailConstructor::testFce()
{
    return QString::number(P3.x());
}

void RailConstructor::setPoints(QPoint endP) //GET ABSOLUTE POS!
{
    //P0 = ABSOLUTE
    //P1-3 = RELATIVE!
    int x = endP.x() - location.x();
    int y = endP.y() - location.y();

    //set start (P0) and end (P3)
    if (startAtSpawnPos)
    {
        P0 = location; //ABOLUTE COORD
        P3 = {x,y}; //relative
    }
    else
    {
        P3 = {x,y}; //relative
        P0 = endP; //end = START LOCATION - ABSOLUTE COORD
    }

    //set P1 and P2
    if (lined)
    {
        P1 = {(x)/2,y/2}; //relative
        P2 = P1; //relative
    }
    else
    {
        //Béziere...
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

RailConstructor::~RailConstructor()
{

}


