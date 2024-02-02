#ifndef VAGON_H
#define VAGON_H

#include "Actors/vehicle.h"
#include <QObject>

class Vagon : public Vehicle
{
    Q_OBJECT
public:
    explicit Vagon(QObject *parent = nullptr, QGraphicsItem* newGraphicItem = nullptr);
};

#endif // VAGON_H
