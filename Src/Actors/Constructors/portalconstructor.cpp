#include "portalconstructor.h"

PortalConstructor::PortalConstructor(QObject* parent, QGraphicsItem* newGraphicItem, Actor *actorToConstructing)
    : ActorConstructor(parent, newGraphicItem, actorToConstructing)
{

}

void PortalConstructor::actualizeConstructor(QPoint newPoint)
{
    QPoint slideLocation = {5,-50};
    setLocation(newPoint + slideLocation, true);
    actualizeGraphicLocation();
}

PortalConstructor::~PortalConstructor()
{

}
