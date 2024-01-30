#ifndef DIESELLOCOMOTIVE_H
#define DIESELLOCOMOTIVE_H

#include "locomotive.h"

class DieselLocomotive : public Locomotive
{
Q_OBJECT
private:
    int fuel;
public:
    DieselLocomotive(QObject *parent = nullptr, QGraphicsItem *newGraphicItem = nullptr);
signals:

public slots:
};

#endif // DIESELLOCOMOTIVE_H
