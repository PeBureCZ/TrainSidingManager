#ifndef SPHERECOLLIDER_H
#define SPHERECOLLIDER_H

#include "collider.h"

class SphereCollider : public Collider
{
protected:
    int radius;
public:
    SphereCollider();
    void setRadius(int newRadius);
    int getRadius();
};

#endif // SPHERECOLLIDER_H
