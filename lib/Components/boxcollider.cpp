#include "boxcollider.h"

BoxCollider::BoxCollider(Collider *parent)
{
    leftUpCorner = {0,0};
    rightDownCorner = {0,0};
}

void BoxCollider::setBoxCollider(QPoint newLeftUpCorner, QPoint newRightDownCorner, float newRotation)
{
    leftUpCorner = newLeftUpCorner;
    rightDownCorner = newRightDownCorner;
    setRelativeRotation(newRotation);

}

bool BoxCollider::isInCollision(QPoint relativeLocation)
{
    if (relativeLocation.x() >= leftUpCorner.x()
        && relativeLocation.x() <= rightDownCorner.x()
        && relativeLocation.y() >= leftUpCorner.y()
        && relativeLocation.y() <= rightDownCorner.y())
        return true;
    return false;
}
