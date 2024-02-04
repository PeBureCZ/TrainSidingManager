#ifndef TRAIN_TEST_H
#define TRAIN_TEST_H

#include <QObject>
#include "Actors/train.h"
#include <QtTest>

class Train_test : public QObject
{
    Q_OBJECT
public:
    explicit Train_test(QObject *parent = nullptr);


private slots:
    void addVehicle_zeroVehicle_test();
    void addVehicle_oneVehicle_test();
    void addVehicle_twoVehicle_test();

signals:

};

#endif // TRAIN_TEST_H
