#include "train_test.h"

Train_test::Train_test(QObject *parent)
    : QObject{parent}
{

}

void Train_test::addVehicle_zeroVehicle_test()
{
    Train* testedTrain = new Train;
    QVERIFY(testedTrain->getMaxSpeed() == 0);
    QVERIFY(testedTrain->getVehicles().size() == 0);

    //vehicles deleted in train destructor!
    delete testedTrain;
}

void Train_test::addMultipleVehicles_oneVehicle_test()
{
    Vehicle* testedVehicle1 = new Vehicle;
    QList<Vehicle*> testedVehicles = {testedVehicle1};
    testedVehicle1->setMaxSpeed(8001.0f);

    Train* testedTrain = new Train;
    testedTrain->addMultipleVehicleToTrain(testedVehicles);
    QVERIFY(testedTrain->getMaxSpeed() == 8001.0f);
    QVERIFY(testedTrain->getVehicles().size() == 1);

    //vehicles deleted in train destructor!
    delete testedTrain;
}

void Train_test::addVehicle_twoVehicle_test()
{
    Vehicle* testedVehicle1 = new Vehicle;
    testedVehicle1->setMaxSpeed(8001.0f);
    Vehicle* testedVehicle2 = new Vehicle;
    testedVehicle2->setMaxSpeed(505.0f);

    QList<Vehicle*> testedVehicles = {testedVehicle1, testedVehicle2};

    Train* testedTrain = new Train;
    testedTrain->addMultipleVehicleToTrain(testedVehicles);
    QVERIFY(testedTrain->getMaxSpeed() == 505.0f);
    QVERIFY(testedTrain->getVehicles().size() == 2);

    //vehicles deleted in train destructor!
    delete testedTrain;
}
