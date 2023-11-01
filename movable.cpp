#include "movable.h"

Movable::Movable()
{
    pixmap = QPixmap (QDir::currentPath() + "/debug/loco.png");
    pixmapItem = new QGraphicsPixmapItem(pixmap);

}

void Movable::setPixMap(QGraphicsScene *scene)
{

    worldScene = scene;
    worldScene->addItem(pixmapItem);
}

//Movable::~Movable()
//{
//    pixmapItem->setPos(-500,-500);
//}
