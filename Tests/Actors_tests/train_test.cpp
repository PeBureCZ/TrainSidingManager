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

void Train_test::addVehicle_oneVehicle_test()
{
    Vehicle* testedVehicle1 = new Vehicle;
    testedVehicle1->setMaxSpeed(8001);

    Train* testedTrain = new Train;
    testedTrain->addVehicle(testedVehicle1, nullptr);
    QVERIFY(testedTrain->getMaxSpeed() == 8001);
    QVERIFY(testedTrain->getVehicles().size() == 1);

    //vehicles deleted in train destructor!
    delete testedTrain;
}

void Train_test::addVehicle_twoVehicle_test()
{
    Vehicle* testedVehicle1 = new Vehicle;
    testedVehicle1->setMaxSpeed(8001);
    Vehicle* testedVehicle2 = new Vehicle;
    testedVehicle2->setMaxSpeed(505);

    Train* testedTrain = new Train;
    testedTrain->addVehicle(testedVehicle1, nullptr);
    testedTrain->addVehicle(testedVehicle2, nullptr);
    QVERIFY(testedTrain->getMaxSpeed() == 505);
    QVERIFY(testedTrain->getVehicles().size() == 2);

    //vehicles deleted in train destructor!
    delete testedTrain;
}
