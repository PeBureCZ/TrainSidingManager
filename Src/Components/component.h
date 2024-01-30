#ifndef COMPONENT_H
#define COMPONENT_H

#include <QPoint>

class Component
{
protected:
    QPoint relativeLocation;
    float relativeRotation;
public:
    Component();
    void setRelativeLocation(QPoint newPosition);
    void setRelativeRotation(float newRotation);
    QPoint getRelativeLocation();
    virtual ~Component();
};

#endif // COMPONENT_H
