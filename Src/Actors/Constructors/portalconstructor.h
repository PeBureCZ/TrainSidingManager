
#ifndef PORTALCONSTRUCTOR_H
#define PORTALCONSTRUCTOR_H

#include "actorconstructor.h"
#include <QObject>

class PortalConstructor : public ActorConstructor
{
    Q_OBJECT
public:
    PortalConstructor
    (QObject *parent = nullptr,
    QGraphicsItem *newGraphicItem = nullptr,
    Actor *actorToConstructing = nullptr);

    void actualizeConstructor(QPoint newPoint) override;
    ~PortalConstructor();
};

#endif // PORTALCONSTRUCTOR_H
