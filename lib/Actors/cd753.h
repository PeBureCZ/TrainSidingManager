#ifndef CD753_H
#define CD753_H

#include "diesellocomotive.h"

class LIB_EXPORT CD753 : public DieselLocomotive
{
Q_OBJECT
public:
    CD753(QObject *parent = nullptr, QGraphicsItem* newGraphicItem = nullptr);
signals:

public slots:
};

#endif // CD753_H
