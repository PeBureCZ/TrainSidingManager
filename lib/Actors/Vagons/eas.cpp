#include "eas.h"

Eas::Eas(QObject* parent, QGraphicsItem* newGraphicItem)
    : Vagon(parent, newGraphicItem)
{
    mass = 23500; //kg
    firstAxleCenter = {10,25}; //dcm relative
    secondAxleCenter = {10,115}; //dcm
    width = 30; //dcm
    length = 140; //dcm
    maxSpeed = 333;
}
