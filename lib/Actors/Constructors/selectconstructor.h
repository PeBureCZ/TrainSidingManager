#ifndef SELECTCONSTRUCTOR_H
#define SELECTCONSTRUCTOR_H

#include "actorconstructor.h"
#include <QObject>

class LIB_EXPORT SelectConstructor : public ActorConstructor
{
    Q_OBJECT
protected:
    bool underSelectMode;
    bool underEditMode;
public:
    explicit SelectConstructor(QObject* parent = nullptr, QGraphicsItem* newGraphicItem = nullptr, Actor *actorToConstructing = nullptr);
    bool getUnderSelect();
    bool getUnderEdit();
    void setUnderEdit(bool newUnderEdit);
    void actualizeConstructor(QPoint newPoint, int zoomLevel) override;
    virtual void setUnderSelect(bool newUnderSelect);

    virtual void callSelectEvent(QPoint point);
    virtual Actor* getSelectedActor();
};

#endif // SELECTCONSTRUCTOR_H
