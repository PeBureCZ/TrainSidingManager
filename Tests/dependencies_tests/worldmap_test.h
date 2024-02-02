#ifndef WORLDMAP_TEST_H
#define WORLDMAP_TEST_H

#include <QObject>
#include "dependencies/worldmap.h"
#include <QtTest>

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
