#include "locomotive.h"


Locomotive::Locomotive(QObject* parent, QGraphicsItem* newGraphicItem) : Vehicle(parent, newGraphicItem)
{
    power = 0;
}

