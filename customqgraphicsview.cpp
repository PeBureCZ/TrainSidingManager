#include "customqgraphicsview.h"

CustomQGraphicsView::CustomQGraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    zoomLevel = 0;
    mapSizeX = 0;
    mapSizeY = 0;
}

QString CustomQGraphicsView::testX()
{
    QPoint globalPos = QCursor::pos();

    QRectF mySceneRect = sceneRect(); //resolution of scene
    qreal sceneWidth = mySceneRect.width(); // equal mapSizeX * 2
    qreal sceneHeight = mySceneRect.height(); //equal mapSizeY * 2
    return QString::number(sceneWidth) + " / " + QString::number(sceneHeight) + " / " + QString::number(mapSizeX) + " / " + QString::number(mapSizeY);
}

void CustomQGraphicsView::wheelEvent(QWheelEvent *event)
{
    int delta = event->angleDelta().y();

    if (delta > 0)
    {
        zoomIn();
    }
    else if (delta < 0)
    {
        zoomOut();
    }
    else
    {
    }
}

void CustomQGraphicsView::zoomIn()
{
    //ZOOM IN MOUSE DIRECTION
    QPoint globalPos = QCursor::pos();

    QScrollBar* horizontalBar = horizontalScrollBar();
    QScrollBar* verticalBar = verticalScrollBar();

    int xBarValue = horizontalBar->value();
    int yBarValue = verticalBar->value();

    //CALCULATE RELATIVE MOUSE POSITION TO THE MAINWINDOW (in range from -1 to 1)
    //It must be changed, it does not care about the window size, currently set with fixed values for the scene view location.
    xBarValue -= 150*(globalPos.x()-830)/(385-830); //-150 = efectivity, 830 = midle pix, 385 = pix on main window (left) - WILL BE CHANGED
    yBarValue -= 140*(globalPos.y()-400)/(85-400); //-140 = efectivity, 400 = midle pix, 85 = pix on main window (top) - WILL BE CHANGED

    //xBar check min and max
    (xBarValue < horizontalBar->minimum()) ? xBarValue = horizontalBar->minimum() : xBarValue;
    (xBarValue > horizontalBar->maximum()) ? xBarValue = horizontalBar->maximum() : xBarValue;

    //yBar check min and max
    (yBarValue < verticalBar->minimum()) ? yBarValue = verticalBar->minimum() : yBarValue;
    (yBarValue > verticalBar->maximum()) ? yBarValue = verticalBar->maximum() : yBarValue;

    verticalBar->setValue((yBarValue));
    horizontalBar->setValue(xBarValue);

    //ZOOM SCALE
    if (zoomLevel > MIN_ZOOM_LEVEL)
    {
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
    int mapXside = mapSizeX/2;
    int mapYside = mapSizeY/2;

    //set start zoom level
    for (int i = 0; i < 17; i++) zoomOut();

    /*
    IMAGES - NEED ADD THIS OPTION! (image instances?!)
    QPixmap pixmap1("C:/Users/Bureš/Desktop/Dočasné dokumenty/C++/Screenshots/1.jpg");
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap1);
    worldScene->addItem(item);
    */
}

int CustomQGraphicsView::getMapSizeX()
{
    return mapSizeX;
}

int CustomQGraphicsView::getMapSizeY()
{
    return mapSizeY;
}
