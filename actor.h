#ifndef ACTOR_H
#define ACTOR_H

#include <QString>
#include <QPoint>
#include <QGraphicsScene>

class Actor
{
protected:
    QString name;
    QPoint location;
    float rotation;
    QGraphicsScene *worldScene;
private:

public:
    Actor();
    void setName(QString newName);
    QString getName();
    void setRotation(float newRotation);
    float getRotation();
    void destroyActor();
};

#endif // ACTOR_H
