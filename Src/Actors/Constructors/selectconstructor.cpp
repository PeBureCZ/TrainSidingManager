#include "selectconstructor.h"

SelectConstructor::SelectConstructor(QObject* parent, QGraphicsItem* newGraphicItem, Actor *actorToConstructing)
:
ActorConstructor(parent, newGraphicItem, actorToConstructing)
{
    underSelectMode = false;
    underEditMode = false;
}

bool SelectConstructor::getUnderSelect()
{
    return underSelectMode;
}

bool SelectConstructor::getUnderEdit()
{
    return underEditMode;
}

void SelectConstructor::setUnderSelect(bool newUnderSelect)
{
    underSelectMode = newUnderSelect;
}

void SelectConstructor::setUnderEdit(bool newUnderEdit)
{
    underEditMode = newUnderEdit;
}

void SelectConstructor::callSelectEvent(QPoint point)
{}

void SelectConstructor::actualizeConstructor(QPoint newPoint)
{
    setLocation(newPoint,false);
    if (underEditMode) callSelectEvent(newPoint);
}
