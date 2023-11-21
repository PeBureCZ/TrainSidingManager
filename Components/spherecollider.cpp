#include "spherecollider.h"

SphereCollider::SphereCollider()
{
    radius = 0;
}

void SphereCollider::setRadius(int newRadius)
{
    radius = newRadius;
}

int SphereCollider::getRadius()
{
    return radius;
}
