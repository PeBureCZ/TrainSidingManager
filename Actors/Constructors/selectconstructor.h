#ifndef SELECTCONSTRUCTOR_H
#define SELECTCONSTRUCTOR_H

#include "actorconstructor.h"
#include <QObject>

class SelectConstructor : public ActorConstructor
{
    Q_OBJECT
protected:
    bool underSelectEvent;
public:
    explicit SelectConstructor(QObject* parent = nullptr, QGraphicsItem* newGraphicItem = nullptr, Actor *actorToConstructing = nullptr);
    bool getUnderSelect();
    void setUnderSelect(bool newUnderSelect);
    virtual void callSelectEvent(QPoint point);
    void actualizeConstructor(QPoint newPoint) override;
};

#endif // SELECTCONSTRUCTOR_H
