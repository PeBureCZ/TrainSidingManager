#ifndef CUSTOMQGRAPHICSVIEW_H
#define CUSTOMQGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QScrollBar>
#include <QRect>
#include <QGraphicsRectItem>

#define MAX_ZOOM_LEVEL 18 //NEED TO REBUILD - count relative location not work in zoom level > maxMapSize
#define MIN_ZOOM_LEVEL -5
#define MAX_MAP_X_SIZE 25000 //MEAN x -25000 TO x 25000
#define MAX_MAP_Y_SIZE 20000 //MEAN y -20000 TO y 20000
#define START_ZOOM 4

class CustomQGraphicsView : public QGraphicsView
{

protected:
    int zoomLevel;
    int mapSizeX;
    int mapSizeY;

public:
    CustomQGraphicsView(QWidget *parent = nullptr);
    void zoomIn(bool sideways);
    void zoomOut();
    int getZoomLevel();
    void setWorldMap(int xSize, int ySize);
    int getMapSizeX();
    int getMapSizeY();
    QPoint getRelativeFromCursor();
    void wheelEvent(QWheelEvent *event) override;
};

#endif // CUSTOMQGRAPHICSVIEW_H
