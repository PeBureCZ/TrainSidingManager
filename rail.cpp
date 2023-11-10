#include "rail.h"


Rail::Rail(QGraphicsPathItem *pathObj) : path{pathObj}
{

}

QGraphicsPathItem *Rail::getPathItem()
{
    return path;
}

