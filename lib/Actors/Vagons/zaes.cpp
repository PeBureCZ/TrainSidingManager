#include "zaes.h"

Zaes::Zaes(QObject* parent, QGraphicsItem* newGraphicItem)
    : Vagon(parent, newGraphicItem)
{
    mass = 23500; //kg
    firstAxleCenter = {15,25}; //dcm relative
    secondAxleCenter = {15,108}; //dcm
    width = 30; //dcm
    length = 133; //dcm
    maxSpeed = 83; //dcm / 0,2s
}
