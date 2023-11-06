#ifndef ACTOR_H
#define ACTOR_H

#include <QString>
#include <QPoint>

class Actor
{
protected:
    QString name;
    QPoint location;
    float rotation;
private:

public:
    Actor();
    virtual void setName(QString newName); //virtual need for polymorph
    QString getName();
    void setRotation(float newRotation);
    float getRotation();
    void setLocation(QPoint newLocation);
    QPoint getLocation();
    ~Actor();
};

#endif // ACTOR_H
