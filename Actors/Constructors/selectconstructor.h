#ifndef SELECTCONSTRUCTOR_H
#define SELECTCONSTRUCTOR_H

#include "actorconstructor.h"
#include <QObject>

class SelectConstructor : public ActorConstructor
{
    Q_OBJECT
protected:
    bool underSelectMode;
    bool underEditMode;
public:
    explicit SelectConstructor(QObject* parent = nullptr, QGraphicsItem* newGraphicItem = nullptr, Actor *actorToConstructing = nullptr);
    bool getUnderSelect();
    bool getUnderEdit();
    virtual void setUnderSelect(bool newUnderSelect);
    void setUnderEdit(bool newUnderEdit);
    virtual void callSelectEvent(QPoint point);
    void actualizeConstructor(QPoint newPoint) override;
};

#endif // SELECTCONSTRUCTOR_H