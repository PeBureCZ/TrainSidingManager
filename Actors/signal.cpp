#include "signal.h"

Signal::Signal(QObject *parent, QGraphicsItem *newGraphicItem)
    : RailwayObject(parent, newGraphicItem)
{

}

Signal::~Signal()
{
    qDebug() << "signal destroyed on loc: " << location << " > " << graphicLocation;
}
