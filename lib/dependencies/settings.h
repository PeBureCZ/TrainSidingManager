#ifndef SETTINGS_H
#define SETTINGS_H

#include "dependencies/Enums/CustomColors.h"

#define BACKGROUND_COLOR 65,80,65

enum settingsEnum
{
    MAX_MAP_SIZE_X = 25000, //MEAN x -25000 TO x 25000
    MAX_MAP_SIZE_Y = 20000, //MEAN x -20000 TO x 20000
    MIN_ZOOM_LEVEL = -5,
    MAX_ZOOM_LEVEL = 18,
    START_ZOOM = 4,
};

enum graphicItemLayer
{
    //QGraphicsItem *myItem = new QGraphicsItem;
    //myItem->setZValue(1);

    BOTTOM_LAYER = 0,
    UNDER_RAIL,
    UNSELECTED_RAIL_LAYER,
    SELECTED_RAIL_LAYER,
    ABOVE_RAIL,
    RED_AREA_LAYER,
    GREEN_AREA_LAYER,
    VEHICLE_LAYER,
    SIGNAL_LAYER,
    TOP_LAYER,
};

#endif // SETTINGS_H
