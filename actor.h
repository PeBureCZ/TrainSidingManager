#ifndef ACTOR_H
#define ACTOR_H

#include <QString>
#include <QPoint>
#include <QGraphicsScene>

class Actor
{
public:
    Actor();
    QString name;
    QPoint location;
    QGraphicsScene *worldScene;

    void setName(QString newName);
    QString getName();

    //~Actor();
};

#endif // ACTOR_H
