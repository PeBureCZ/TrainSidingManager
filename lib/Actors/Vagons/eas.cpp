#include "eas.h"

Eas::Eas(QObject* parent, QGraphicsItem* newGraphicItem)
    : Vagon(parent, newGraphicItem)
{
    mass = 23500; //kg
    firstAxleCenter = {15,25}; //dcm relative
    secondAxleDistance = 90; //dcm
    width = 140; //dcm
    length = 300; //dcm
    maxSpeed = 333;
}
