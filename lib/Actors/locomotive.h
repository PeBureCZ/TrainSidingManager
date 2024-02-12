#ifndef LOCOMOTIVE_H
#define LOCOMOTIVE_H

#include "vehicle.h"

class LIB_EXPORT Locomotive : public Vehicle
{
Q_OBJECT
protected:
    int power;
public:
    Locomotive(QObject *parent = nullptr, QGraphicsItem* newGraphicItem = nullptr);
signals:

public slots:
};

#endif // LOCOMOTIVE_H
