#ifndef DIESELLOCOMOTIVE_H
#define DIESELLOCOMOTIVE_H

#include "locomotive.h"

class DieselLocomotive : public Locomotive
{
public:
    DieselLocomotive();

    int fuel;
};

#endif // DIESELLOCOMOTIVE_H
