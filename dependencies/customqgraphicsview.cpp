#include "customqgraphicsview.h"

CustomQGraphicsView::CustomQGraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    zoomLevel = 0;
    mapSizeX = 0;
    mapSizeY = 0;
}

void CustomQGraphicsView::wheelEvent(QWheelEvent *event)
{
    int delta = event->angleDelta().y();

    if (delta > 0)
    {
        zoomIn(true); //true = sideways by mouse
    }
    else if (delta < 0)
    {
        zoomOut();
    }
    else
    {
    }
}

void CustomQGraphicsView::zoomIn(bool sideways)
{    
    if (zoomLevel > MIN_ZOOM_LEVEL)
    {
        if (sideways)
        {
            //ZOOM IN MOUSE DIRECTION
            QPoint globalPos = QCursor::pos();

            QScrollBar* horizontalBar = horizontalScrollBar();
            QScrollBar* verticalBar = verticalScrollBar();

            int xBarValue = horizontalBar->value();
            int yBarValue = verticalBar->value();

            //CALCULATE RELATIVE MOUSE POSITION TO THE MAINWINDOW (in range from -1 to 1)
            QRectF worldRect = sceneRect();
            QPointF sceneTopLeft = mapToGlobal(worldRect.topLeft().toPoint());
            int sceneGlobalX = sceneTopLeft.x();
            int sceneGlobalY = sceneTopLeft.y();
            QSize viewSize = viewport()->size();
            int pixPositionLeftX = sceneGlobalX + mapSizeX;
            int PixPositionMiddleX = pixPositionLeftX + viewSize.width()/2;
            int pixPositionLeftY = sceneGlobalY + mapSizeY;
            int PixPositionMiddleY = pixPositionLeftY + viewSize.height()/2;
            int xm = 140; // Specifies how much the camera moves sideways during zoom in the x direction
            int ym = 130; // Specifies how much the camera moves sideways during zoom in the y direction

            xBarValue -= xm*(globalPos.x()-PixPositionMiddleX)/(pixPositionLeftX-PixPositionMiddleX);
            yBarValue -= ym*(globalPos.y()-PixPositionMiddleY)/(pixPositionLeftY-PixPositionMiddleY);

            //xBar check min and max
            (xBarValue < horizontalBar->minimum()) ? xBarValue = horizontalBar->minimum() : xBarValue;
            (xBarValue > horizontalBar->maximum()) ? xBarValue = horizontalBar->maximum() : xBarValue;

            //yBar check min and max
            (yBarValue < verticalBar->minimum()) ? yBarValue = verticalBar->minimum() : yBarValue;
            (yBarValue > verticalBar->maximum()) ? yBarValue = verticalBar->maximum() : yBarValue;

            verticalBar->setValue((yBarValue));
            horizontalBar->setValue(xBarValue);
        }
        //ZOOM SCALE
        scale(1.25,1.25);
        zoomLevel--;
    }
}

void CustomQGraphicsView::zoomOut()
{
    if (zoomLevel < MAX_ZOOM_LEVEL)
    {
        scale(0.8,0.8);
        zoomLevel++;
    }
}

int CustomQGraphicsView::getZoomLevel()
{
    return zoomLevel;
}

void CustomQGraphicsView::setWorldMap(int xSize, int ySize) //need to refract later!
{
    //check max map size -> accept or reduce size to maximum
    (xSize > MAX_MAP_X_SIZE) ? mapSizeX = MAX_MAP_X_SIZE : mapSizeX = xSize;
    (ySize > MAX_MAP_Y_SIZE) ? mapSizeY = MAX_MAP_Y_SIZE : mapSizeY = ySize;

    //set world border and world size
    //set border, border set to coordinate (-) and (+) -> coord. {0,0} in map center
    //int mapXside = mapSizeX/2;
    int mapYside = mapSizeY/2;

    //set start zoom level
    for (int i = 0; i < START_ZOOM; i++) zoomOut();
}

int CustomQGraphicsView::getMapSizeX()
{
    return mapSizeX;
}

int CustomQGraphicsView::getMapSizeY()
{
    return mapSizeY;
}

QPoint CustomQGraphicsView::getRelativeFromCursor()
{
    QPoint globalPos = QCursor::pos();
    QPointF scenePos = mapToScene(mapFromGlobal(globalPos));
    return scenePos.toPoint();
}
