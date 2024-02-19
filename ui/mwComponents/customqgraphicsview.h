#ifndef CUSTOMQGRAPHICSVIEW_H
#define CUSTOMQGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QScrollBar>
#include <QRect>
#include <QGraphicsRectItem>

class CustomQGraphicsView : public QGraphicsView
{
Q_OBJECT
protected:
    int zoomLevel;
    int mapSizeX;
    int mapSizeY;
    const int MAX_ZOOM_LEVEL = 18;
    const int MIN_ZOOM_LEVEL = -5;
    const int MAX_MAP_X_SIZE = 25000; //MEAN x -25000 TO x 25000
    const int MAX_MAP_Y_SIZE = 20000; //MEAN y -20000 TO y 20000
    const int START_ZOOM = 4;

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