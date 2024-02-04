#ifndef SIGNAL_H
#define SIGNAL_H

#include "railwayobject.h"
#include <QObject>
#include <QList>
#include "dependencies/Enums/SignalEnum.h"


class Signal : public RailwayObject
{
    Q_OBJECT
protected:
    QList<int> allowedSignalState;
    int signalState;
public:
    explicit Signal(QObject *parent = nullptr, QGraphicsItem* newGraphicItem = nullptr);
    void setState(int newSignState);
    int getState();
    QList<int> getAllowedSignalState() const;
    ~Signal();

};

#endif // SIGNAL_H
