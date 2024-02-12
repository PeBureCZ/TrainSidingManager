#ifndef COLLIDER_H
#define COLLIDER_H

#include "lib_global.h"
#include "trigger.h"

class LIB_EXPORT Collider : public Trigger
{
Q_OBJECT
public:
    Collider(Trigger *parent = nullptr);
};

#endif // COLLIDER_H
