#ifndef RAILWAYOBJECT_H
#define RAILWAYOBJECT_H

#include "actor.h"

class RailwayObject : public Actor
{
Q_OBJECT
protected:
    bool visibleName;
public:
    RailwayObject(QObject *parent = nullptr, QGraphicsItem* newGraphicItem = nullptr);
signals:

public slots:
};

#endif // RAILWAYOBJECT_H
