#ifndef CUSTOMQGRAPHICSVIEW_H
#define CUSTOMQGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QScrollBar>
#include <QRect>
#include <QGraphicsRectItem>
#include "dependencies/settings.h"

class CustomQGraphicsView : public QGraphicsView
{
Q_OBJECT
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
