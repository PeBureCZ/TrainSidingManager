#include "diesellocomotive.h"


DieselLocomotive::DieselLocomotive(QGraphicsItem* newGraphicItem) : Locomotive(newGraphicItem)
{
    fuel = 100;
    name = "diesel locomotive";
}

