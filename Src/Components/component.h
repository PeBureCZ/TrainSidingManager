#ifndef COMPONENT_H
#define COMPONENT_H

#include <QPoint>
#include <QObject>

class Component : public QObject
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
    virtual ~Component();
};

#endif // COMPONENT_H
