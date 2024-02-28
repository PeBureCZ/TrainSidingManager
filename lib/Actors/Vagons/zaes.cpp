#include "zaes.h"

Zaes::Zaes(QObject* parent, QGraphicsItem* newGraphicItem)
    : Vagon(parent, newGraphicItem)
{
    mass = 23500; //kg
    firstAxleCenter = {15,25}; //dcm relative
    secondAxleCenter = {15,108}; //dcm
    width = 30; //dcm
    length = 133; //dcm
    maxSpeed = 83.7f; //dcm / 0,2s
    selectedSpriteEnum = ZAES_SELECTED_SPRITE;
    unselectedSpriteEnum = ZAES_ACTIVE_SPRITE;
    unactiveSpriteEnum = ZAES_ACTIVE_SPRITE;
}
