#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "collider.h"
#include <QDebug>
#include <QTransform>

class BoxCollider : public Collider
{
protected:
    QPoint leftUpCorner;
    QPoint rightDownCorner;
public:
    BoxCollider();
    void setBoxCollider(QPoint newLeftUpCorner, QPoint newRightDownCorner, float newRotation); //pivot = middle relative P0/P3
    bool isInCollision(QPoint relativeLocation);
};

#endif // BOXCOLLIDER_H
