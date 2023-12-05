#ifndef ELECTRICLOCOMOTIVE_H
#define ELECTRICLOCOMOTIVE_H

#include "locomotive.h"

class ElectricLocomotive : public Locomotive
{
Q_OBJECT
public:
    ElectricLocomotive(QObject *parent = nullptr, QGraphicsItem* newGraphicItem = nullptr);
signals:

public slots:
};

#endif // ELECTRICLOCOMOTIVE_H
