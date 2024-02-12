#ifndef SPHERECOLLIDER_H
#define SPHERECOLLIDER_H

#include "collider.h"
#include <QObject>

class LIB_EXPORT SphereCollider : public Collider
{
Q_OBJECT
protected:
    int radius;
public:
    SphereCollider(Collider *parent = nullptr);
    void setRadius(int newRadius);
    int getRadius();
};

#endif // SPHERECOLLIDER_H
