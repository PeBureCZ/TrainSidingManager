#ifndef PORTAL_H
#define PORTAL_H

#include "actor.h"
#include <QObject>

class LIB_EXPORT Portal : public Actor
{
    Q_OBJECT
public:
    explicit Portal(QObject *parent = nullptr);
};

#endif // PORTAL_H
