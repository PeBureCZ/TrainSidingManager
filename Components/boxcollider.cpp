#include "boxcollider.h"

BoxCollider::BoxCollider()
{
    leftUpCorner = {0,0};
    rightDownCorner = {0,0};
}

BoxCollider::setBoxCollider(QPoint newLeftUpCorner, QPoint newRightDownCorner, float newRotation)
{
    leftUpCorner = newLeftUpCorner;
    rightDownCorner = newRightDownCorner;
    setRelativeRotation(newRotation);
}
