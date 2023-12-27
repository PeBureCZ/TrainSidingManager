#ifndef SIGNAL_H
#define SIGNAL_H

#include "railwayobject.h"
#include <QObject>

class Signal : public RailwayObject
{
    Q_OBJECT
public:
    explicit Signal(QObject *parent = nullptr, QGraphicsItem* newGraphicItem = nullptr);
};

#endif // SIGNAL_H
