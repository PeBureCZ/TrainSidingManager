#ifndef MOVABLE_H
#define MOVABLE_H

#include "actor.h"
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QDir>

class Movable : public Actor
{
public:
    Movable();
    QPixmap pixmap;
    QGraphicsPixmapItem *pixmapItem;
    void setPixMap(QGraphicsScene *scene);
    //~Movable();
};

#endif // MOVABLE_H
