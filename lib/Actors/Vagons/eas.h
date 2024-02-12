#ifndef EAS_H
#define EAS_H

#include "vagon.h"
#include <QObject>

class Eas : public Vagon
{
    Q_OBJECT
public:
    explicit Eas(QObject* parent = nullptr, QGraphicsItem* newGraphicItem = nullptr);
};

#endif // EAS_H
