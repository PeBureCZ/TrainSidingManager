#ifndef SETTINGS_H
#define SETTINGS_H

#include <QColor>

#define BACKGROUND_COLOR 65,80,65

enum settingsEnum
{
    MAX_MAP_SIZE_X = 25000, //MEAN x -25000 TO x 25000
    MAX_MAP_SIZE_Y = 20000, //MEAN x -20000 TO x 20000
    MIN_ZOOM_LEVEL = -5,
    MAX_ZOOM_LEVEL = 18,
    START_ZOOM = 4,
};

namespace customQColors
{
    inline const QColor SELECTED_RAIL_COLOR = QColor(0, 255, 255, 255);
    inline const QColor UNSELECTED_RAIL_COLOR = QColor(Qt::blue);
}

#endif // SETTINGS_H
