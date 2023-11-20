#include "rail.h"

Rail::Rail(QGraphicsItem* newGraphicItem) : RailwayObject(newGraphicItem)
{
    P0 = {0,0};
    P1 = {0,0};
    P2 = {0,0};
    P3 = {0,0};
    conectionA0 = {}; //connection 0
    conectionB0 = {}; //connection 1
    conectionC1 = {}; //connection 2
    conectionD1 = {}; //connection 3
    lined = true;
}

QPointF Rail::getP0WorldLocation()
{
    return {P0};
}

QPointF Rail::getP1RelativeLocation()
{
    return {P1};
}

QPointF Rail::getP2RelativeLocation()
{
    return {P2};
}

QPointF Rail::getP3RelativeLocation()
{
    return {P3};
}

Rail *Rail::getConnectedRail(int connection)
{
    switch (connection)
    {
        case 0:
        {
            return conectionA0;
            break;
        }
        case 1:
        {
            return conectionB0;
            break;
        }
        case 2:
        {
            return conectionC1;
            break;
        }
        case 3:
        {
            return conectionD1;
        }
    }
}

void Rail::setConnectedRail(Rail* connectedRail, int connection)
{
    switch (connection)
    {
        case 0:
        {
            conectionA0 = connectedRail;
            break;
        }
        case 1:
        {
            conectionB0 = connectedRail;
            break;
        }
        case 2:
        {
            conectionC1 = connectedRail;
            break;
        }
        case 3:
        {
            conectionD1 = connectedRail;
        }
    }
}

void Rail::setP0WorldLocation(QPoint newPoint)
{
    P0 = newPoint;
}

void Rail::setP1RelativeLocation(QPoint newPoint)
{
    P1 = newPoint;
}

void Rail::setP2RelativeLocation(QPoint newPoint)
{
    P2 = newPoint;
}

void Rail::setP3RelativeLocation(QPoint newPoint)
{
    P3 = newPoint;
}

void Rail::setLined(bool newBool)
{
    lined = newBool;
}

void Rail::connectRails(Rail *connectedRail, bool connectedAtStart) //connectedRail have to be always created by constructor
{
    //conect rail function always conect P3 point from constructor
    QPoint connectedRailP3 = connectedRail->getLocation() + connectedRail->getP3RelativeLocation().toPoint(); //world coordinate
    QPoint connectedRailP0 = connectedRail->getLocation(); //world coordinate
    QLineF distanceOne(connectedRailP0, P0);
    QLineF distanceTwo(connectedRailP3, P0);
    if (connectedAtStart) //connect at start = connect this rail at P0 to connectedRail
    {
        if (distanceOne.length() < distanceTwo.length()) //true --> need connect this(P0) & connectedRail(P0)
        {
            if (conectionA0 == nullptr)
            {
                if (connectedRail->getConnectedRail(0) == nullptr)
                {
                    setConnectedRail(connectedRail, 0);
                    connectedRail->setConnectedRail(dynamic_cast<Rail*>(this), 0);
                }
                else if (connectedRail->getConnectedRail(1) == nullptr)
                {
                    setConnectedRail(connectedRail, 0);
                    connectedRail->setConnectedRail(dynamic_cast<Rail*>(this), 1);
                }
            }
            else if (conectionB0 == nullptr)
            {
                if (connectedRail->getConnectedRail(0) == nullptr)
                {
                    setConnectedRail(connectedRail, 1);
                    connectedRail->setConnectedRail(dynamic_cast<Rail*>(this), 0);
                }
                else if (connectedRail->getConnectedRail(1) == nullptr)
                {
                    setConnectedRail(connectedRail, 1);
                    connectedRail->setConnectedRail(dynamic_cast<Rail*>(this), 1);
                }
            }
            else {} //cant connect...not yet
        }
        else //need connect this(P0) & connectedRail(P3)
        {
            if (conectionA0== nullptr)
            {
                if (connectedRail->getConnectedRail(2) == nullptr)
                {
                    setConnectedRail(connectedRail, 0);
                    connectedRail->setConnectedRail(dynamic_cast<Rail*>(this), 2);
                }
                else if (connectedRail->getConnectedRail(3) == nullptr)
                {
                    setConnectedRail(connectedRail, 0);
                    connectedRail->setConnectedRail(dynamic_cast<Rail*>(this), 3);
                }
            }
            else if (conectionB0 == nullptr)
            {
                if (connectedRail->getConnectedRail(2) == nullptr)
                {
                    setConnectedRail(connectedRail, 1);
                    connectedRail->setConnectedRail(dynamic_cast<Rail*>(this), 2);
                }
                else if (connectedRail->getConnectedRail(3) == nullptr)
                {
                    setConnectedRail(connectedRail, 1);
                    connectedRail->setConnectedRail(dynamic_cast<Rail*>(this), 3);
                }
            }
            else {} //cant connect...not yet
        }
    }
    else //connect at end = connect this rail at P3 to connectedRail
    {
        QLineF distanceOne(connectedRailP0, getLocation() + P3);
        QLineF distanceTwo(connectedRailP3, getLocation() + P3);
        if (distanceOne.length() < distanceTwo.length()) //true --> need connect this(P3) & connectedRail(P0)
        {
            if (conectionC1 == nullptr)
            {
                if (connectedRail->getConnectedRail(0) == nullptr)
                {
                    setConnectedRail(connectedRail, 2);
                    connectedRail->setConnectedRail(dynamic_cast<Rail*>(this), 0);
                }
                else if (connectedRail->getConnectedRail(1) == nullptr)
                {
                    setConnectedRail(connectedRail, 2);
                    connectedRail->setConnectedRail(dynamic_cast<Rail*>(this), 1);
                }
            }
            else if (conectionD1 == nullptr)
            {
                if (connectedRail->getConnectedRail(0) == nullptr)
                {
                    setConnectedRail(connectedRail, 3);
                    connectedRail->setConnectedRail(dynamic_cast<Rail*>(this), 0);
                }
                else if (connectedRail->getConnectedRail(1) == nullptr)
                {
                    setConnectedRail(connectedRail, 3);
                    connectedRail->setConnectedRail(dynamic_cast<Rail*>(this),1);
                }
            }
            else {} //cant connect...not yet
        }
        else //need connect this(P3) & connectedRail(P3)
        {
            if (conectionC1 == nullptr)
            {
                if (connectedRail->getConnectedRail(2) == nullptr)
                {
                    setConnectedRail(connectedRail, 2);
                    connectedRail->setConnectedRail(dynamic_cast<Rail*>(this), 2);
                }
                else if (connectedRail->getConnectedRail(3) == nullptr)
                {
                    setConnectedRail(connectedRail, 2);
                    connectedRail->setConnectedRail(dynamic_cast<Rail*>(this), 3);
                }
            }
            else if (conectionD1 == nullptr)
            {
                if (connectedRail->getConnectedRail(2) == nullptr)
                {
                    setConnectedRail(connectedRail, 3);
                    connectedRail->setConnectedRail(dynamic_cast<Rail*>(this), 2);
                }
                else if (connectedRail->getConnectedRail(3) == nullptr)
                {
                    setConnectedRail(connectedRail, 3);
                    connectedRail->setConnectedRail(dynamic_cast<Rail*>(this), 3);
                }
            }
            else {} //cant connect...not yet
        }
    }
}

void Rail::unconnectRails(Rail *unconnectedRail)
{
    if (conectionA0 == unconnectedRail) conectionA0 = {};
    if (conectionB0 == unconnectedRail) conectionB0 = {};
    if (conectionC1 == unconnectedRail) conectionC1 = {};
    if (conectionD1 == unconnectedRail) conectionD1 = {};
}

void Rail::smoothP3PointByC1() //call only if conected to C1 point
{
    if (conectionC1 != nullptr)
    {
        QLineF distanceOne(conectionC1->getP0WorldLocation(), getLocation() + P3); //P3 to connectedP0
        QLineF distanceTwo(conectionC1->getLocation() + conectionC1->getP3RelativeLocation(), getLocation() + P3); //P3 to connected P3
        float reduction = 0.05f;
        QLineF vectorDistance;
        if (distanceOne.length() < distanceTwo.length()) //P3 to connectedP0
        {
            P3 = conectionC1->getLocation() - location;
            vectorDistance.setPoints(conectionC1->getP1RelativeLocation() + conectionC1->getLocation(), P0 + P3 ); //in world coordinate
        }
        else //P3 to connected P3
        {
            QPoint connectedP3world = conectionC1->getLocation() + conectionC1->getP3RelativeLocation().toPoint();
            P3 = connectedP3world - location;
            vectorDistance.setPoints(conectionC1->getP2RelativeLocation() + conectionC1->getLocation(), P0 + P3); //in world coordinate
        }
        QLineF fromP0ToP3(P0, P0 + P3);
        reduction = fromP0ToP3.length() / 2 / vectorDistance.length();
        if (reduction < 0.05f)  reduction = 0.05f;
        QPoint negativeVector = vectorDistance.pointAt(1-reduction).toPoint();
        QPoint vectorP2world = ((P0 + P3) - (negativeVector - (P0 + P3)));
        P2 = vectorP2world  - location;
        QPainterPath smoothPath;
        smoothPath.cubicTo(P1.x(),P1.y(),P2.x(), P2.y(),P3.x(), P3.y());
        dynamic_cast<QGraphicsPathItem*>(graphicItem)->setPath(smoothPath);
    }
}

bool Rail::getLined()
{
    return lined;
}

int Rail::getRailLength()
{
    return dynamic_cast<QGraphicsPathItem*>(graphicItem)->path().length();
}

int Rail::getConnection(Rail *rail)
{
    if (conectionA0 = rail) return 0; //connection 0
    if (conectionB0 = rail) return 1; //connection 1
    if (conectionC1 = rail) return 2; //connection 2
    if (conectionD1 = rail) return 3; //connection 3
    return -1;
}

Rail::~Rail()
{
    if (conectionA0 != nullptr) conectionA0->unconnectRails(dynamic_cast<Rail*>(this));
    if (conectionB0 != nullptr) conectionB0->unconnectRails(dynamic_cast<Rail*>(this));
    if (conectionC1 != nullptr) conectionC1->unconnectRails(dynamic_cast<Rail*>(this));
    if (conectionD1 != nullptr) conectionD1->unconnectRails(dynamic_cast<Rail*>(this));
}

