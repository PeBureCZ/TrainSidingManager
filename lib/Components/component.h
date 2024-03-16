#ifndef COMPONENT_H
#define COMPONENT_H

#include <QPoint>
#include <QObject>
#include "lib_global.h"

class LIB_EXPORT Component : public QObject
{
Q_OBJECT
protected:
    QPoint relativeLocation;
    float relativeRotation;
public:
    Component(QObject *parent = nullptr);
    void setRelativeLocation(QPoint newPosition);
    void setRelativeRotation(float newRotation);
    QPoint getRelativeLocation();
    float getRelativeRotation();
    virtual ~Component();
};

#endif // COMPONENT_H
