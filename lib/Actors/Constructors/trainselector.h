#ifndef TRAINSELECTOR_H
#define TRAINSELECTOR_H

#include "selectconstructor.h"
#include <QObject>

class TrainSelector : public SelectConstructor
{
    Q_OBJECT
public:
    explicit TrainSelector(QObject* parent = nullptr, QGraphicsItem* newGraphicItem = nullptr, Actor *actorToConstructing = nullptr);
};

#endif // TRAINSELECTOR_H
