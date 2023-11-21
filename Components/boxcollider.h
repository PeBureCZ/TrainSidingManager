#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "collider.h"

class BoxCollider : public Collider
{
protected:
    QPoint leftUpCorner;
    QPoint rightDownCorner;
public:
    BoxCollider();
    setBoxCollider(QPoint newLeftUpCorner, QPoint newRightDownCorner, float newRotation); //pivot = middle relative P0/P3
};

#endif // BOXCOLLIDER_H
