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

Actor *SelectConstructor::getSelectedActor(){return nullptr;} //overrided

void SelectConstructor::actualizeConstructor(QPoint newPoint, int zoomLevel)
{
    ActorConstructor::actualizeConstructor(newPoint, zoomLevel);
    if (underEditMode) callSelectEvent(newPoint);
}
