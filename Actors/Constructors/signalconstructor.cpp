#include "signalconstructor.h"

SignalConstructor::SignalConstructor(QObject* parent, QGraphicsItem* newGraphicItem, Actor *actorToConstructing)
    : RailobjectConstructor(parent, newGraphicItem, actorToConstructing)
{

}

SignalConstructor::~SignalConstructor()
{
    qDebug() <<"Signal constructor deleted";
}
