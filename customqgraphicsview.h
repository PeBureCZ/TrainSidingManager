#ifndef CUSTOMQGRAPHICSVIEW_H
#define CUSTOMQGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QScrollBar>
#include <QRect>
#include <QString> //for test only

#define MAX_ZOOM_LEVEL 28 //NEED TO REBUILD - count relative location not work in zoom level > maxMapSize
#define MIN_ZOOM_LEVEL -2
#define MAX_MAP_X_SIZE 250000 //MEAN -250000 TO 250000
#define MAX_MAP_Y_SIZE 200000 //MEAN -200000 TO 200000

class CustomQGraphicsView : public QGraphicsView
{

protected:
    int zoomLevel;
    int mapSizeX;
    int mapSizeY;

public:
    CustomQGraphicsView(QWidget *parent = nullptr);
    QString testX();
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
