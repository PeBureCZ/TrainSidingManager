
#ifndef PORTALCONSTRUCTOR_H
#define PORTALCONSTRUCTOR_H

#include "actorconstructor.h"
#include <QObject>

class PortalConstructor : public ActorConstructor
{
    Q_OBJECT
public:
    explicit PortalConstructor(QObject *parent = nullptr);
};

#endif // PORTALCONSTRUCTOR_H
