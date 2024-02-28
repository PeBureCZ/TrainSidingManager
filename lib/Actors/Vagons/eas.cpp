#include "eas.h"

Eas::Eas(QObject* parent, QGraphicsItem* newGraphicItem)
    : Vagon(parent, newGraphicItem)
{
    mass = 23500; //kg
    firstAxleCenter = {15,25}; //dcm relative
    secondAxleCenter = {15,115}; //dcm
    width = 30; //dcm
    length = 140; //dcm
    maxSpeed = 83.7f; //dcm / 200ms
}
