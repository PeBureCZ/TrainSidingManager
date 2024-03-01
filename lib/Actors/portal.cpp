#include "portal.h"

Portal::Portal(QObject *parent, QGraphicsItem *newGraphicItem)
    : Actor{parent, newGraphicItem}
{
    connectedRail = nullptr;
    connectedToArea = -1;
}

void Portal::setConnectedRail(Rail *newConnectedRail)
{
    connectedRail = newConnectedRail;
    int distance = getDistance(getLocation(), connectedRail->getLocation() + connectedRail->getP3RelativeLocation().toPoint());
    if (distance >  getDistance(connectedRail->getLocation(), getLocation()))
    {
        setLocation(connectedRail->getLocation(),false);
        connectedToArea = 0;
    }
    else connectedToArea = 1;
}

Rail *Portal::getConnectedRail()
{
    return connectedRail;
}

int Portal::getConectedArea()
{
    return connectedToArea;
}



//Portal::~Portal(){}
