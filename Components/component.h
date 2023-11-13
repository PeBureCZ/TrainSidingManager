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
    virtual ~Component();
};

#endif // COMPONENT_H
