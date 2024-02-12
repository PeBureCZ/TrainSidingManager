#ifndef WORLDMAP_TEST_H
#define WORLDMAP_TEST_H

#include <QtTest>
#include <QObject>
#include "dependencies/worldmap.h"
#include "dependencies/worldcollide.h"
#include "mwComponents/customqgraphicsview.h"

#include <QGraphicsItem>


class WorldMap_test : public QObject
{
    Q_OBJECT
public:
    explicit WorldMap_test(QObject *parent = nullptr);
private slots:
    void getRelativeWorldPos_test();

signals:

};

#endif // WORLDMAP_TEST_H
