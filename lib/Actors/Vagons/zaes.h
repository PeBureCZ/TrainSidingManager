#ifndef ZAES_H
#define ZAES_H

#include "vagon.h"
#include <QObject>

class LIB_EXPORT Zaes : public Vagon
{
    Q_OBJECT
public:
    explicit Zaes(QObject* parent = nullptr, QGraphicsItem* newGraphicItem = nullptr);
};

#endif // ZAES_H
