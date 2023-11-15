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
    }
    else
    {
        lined = false;
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
    }
}

QString RailConstructor::testFce()
{
    return QString::number(P3.x());
}

void RailConstructor::setPoints(QPoint endP) //GET WORLD (SCENE) POS!
{
    //P0 = ABSOLUTE
    //P1-3 = RELATIVE!
    int x = endP.x() - location.x();
    int y = endP.y() - location.y();

    //set start (P0) and end (P3)
    if (true) //
    {
        P0 = location; //ABOLUTE COORD
        P3 = {x,y}; //relative
    }
    else //changed direction, not use yet
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
    else    //Béziere path
    {
        Rail* connectedRail = {};
        if (connectedRailA0 != nullptr) connectedRail = connectedRailA0;
        else if (connectedRailB0 != nullptr) connectedRail = connectedRailB0;
        else if (connectedRailC1 != nullptr) connectedRail = connectedRailC1;
        else if (connectedRailD1 != nullptr) connectedRail = connectedRailD1;
        if (connectedRail->getLined()) //conected to "(simulted) line" path
        {
            /*
                mirror vector...
                x' = x2 - (x1 - x2)
                y' = y2 - (y1 - y2)
                ...
                b1=(1, 2) &  b2=(4, 5)
                vector b1b2 = (4-1, 5-2) = (3, 3).
                x' = 4 - (1-4) = 7
                y' = 5 - (2-5) = 8
            */
            QPoint connectedP3 = connectedRail->getP3Point().toPoint(); //get P3 point from previous (connected) path
            QPoint connectedP2 = connectedRail->getP2Point().toPoint(); //get P2 point from previous (connected) path
            //P0 = {connectedRail->getLocation().x() + connectedP2.x(), connectedRail->getLocation().y() + connectedP2.y()};
            //P1 = {(x)/2,y/2}; //relative
            //P2 = connectedP3; //relative
            //P3 = {x,y};
        }
        else; //...conected to béziere
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


