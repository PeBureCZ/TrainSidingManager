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

void Rail::connectRails(Rail *connectedRail) //connectedRail have to be always created by constructor
{
    //conect rail function always conect P3 point from constructor
    QPoint connectedRailP3 = connectedRail->getLocation() + connectedRail->getP3RelativeLocation().toPoint(); //world coordinate
    QLineF distanceOne(connectedRailP3, P0);
    QLineF distanceTwo(connectedRailP3, P3);
    if (distanceOne.length() < distanceTwo.length()) //true --> need connect this(P0) & connectedRail(P3)
    {
        if (conectionA0 == nullptr)
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

void Rail::unconnectRails(Rail *unconnectedRail)
{

}

void Rail::smoothP3Point()
{
    if (conectionC1 != nullptr)
    {
        qDebug() << "need smooth";
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

