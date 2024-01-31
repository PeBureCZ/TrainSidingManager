#ifndef RAIL_TEST_H
#define RAIL_TEST_H

#include <QObject>
#include "Actors/rail.h"
#include <QTest>

class Rail_test : public QObject
{
    Q_OBJECT
public:
    explicit Rail_test(QObject *parent = nullptr);
    ~Rail_test();
private slots:
    void conection_test();
public slots:
    void full_test();

signals:

};

#endif // RAIL_TEST_H
