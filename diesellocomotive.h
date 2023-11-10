#ifndef DIESELLOCOMOTIVE_H
#define DIESELLOCOMOTIVE_H

#include "locomotive.h"

class DieselLocomotive : public Locomotive
{
private:
    int fuel;
public:
    DieselLocomotive();
};

#endif // DIESELLOCOMOTIVE_H
