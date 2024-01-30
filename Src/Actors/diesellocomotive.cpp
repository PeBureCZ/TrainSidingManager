#include "diesellocomotive.h"


DieselLocomotive::DieselLocomotive(QObject* parent, QGraphicsItem* newGraphicItem) : Locomotive(parent, newGraphicItem)
{
    fuel = 100;
    name = "diesel locomotive";
}

