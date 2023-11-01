#ifndef TRAIN_H
#define TRAIN_H

#include "movable.h"

class Train : public Movable
{
public:
    Train();
    addPath();
    movePath(float startPercent);
};

#endif // TRAIN_H
