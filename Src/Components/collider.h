#ifndef COLLIDER_H
#define COLLIDER_H

#include "trigger.h"

class Collider : public Trigger
{
Q_OBJECT
public:
    Collider(Trigger *parent = nullptr);
};

#endif // COLLIDER_H
