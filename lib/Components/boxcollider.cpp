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
    QTransform rotationTransform;
    rotationTransform.rotate(relativeRotation);
    QPoint rotatedPoint = rotationTransform.map(relativeLocation);
    if (rotatedPoint.x() >= leftUpCorner.x()
        && rotatedPoint.x() <= rightDownCorner.x()
        && rotatedPoint.y() >= leftUpCorner.y()
        && rotatedPoint.y() <= rightDownCorner.y())
        return true;
    return false;
}
