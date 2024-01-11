#include "selectconstructor.h"

SelectConstructor::SelectConstructor(QObject* parent, QGraphicsItem* newGraphicItem, Actor *actorToConstructing)
:
ActorConstructor(parent, newGraphicItem, actorToConstructing)
{
    underSelectEvent = false;
}

bool SelectConstructor::getUnderSelect()
{
    return underSelectEvent;
}

void SelectConstructor::setUnderSelect(bool newUnderSelect)
{
    underSelectEvent = newUnderSelect;
}

void SelectConstructor::callSelectEvent(QPoint point)
{}

void SelectConstructor::actualizeConstructor(QPoint newPoint)
{
    setLocation(newPoint,false);
    if (underSelectEvent) callSelectEvent(newPoint);
}
