#include "railconstructor.h"

RailConstructor::RailConstructor(QPoint spawnPos, Rail* connectedRail, Rail* ownRail, int connection) : ownedRail(ownRail)
{
    location = spawnPos;
    P0 = {0,0};
    P1 = {0,0};
    P2 = {0,0};
    P3 = {0,0};
    ownedPath = ownedRail->getPathItem();
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

    //ownedPath->path().cubicTo(P1.x(),P1.y(),P2.x(), P2.y(),P3.x(), P3.y()); //NOT WORK NOW!!!
    //ownedPath->path().setElementPositionAt(1,P1.x(),P1.y()); - NOT WORK

    //TRY SET ELEMENTS VIA POINTERS???
    /*
    QPainterPath p = item->path();
    p.setElementPositionAt(0, 0, -5);
    item->setPath(p);
    */
}

void RailConstructor::actualizeConstructor(QPoint newPoint)
{
    setPoints(newPoint);
    actualizePathVisual();
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

}

QPointF RailConstructor::getP1Point()
{

}

QPointF RailConstructor::getP2Point()
{

}

QPointF RailConstructor::getP3Point()
{

}


