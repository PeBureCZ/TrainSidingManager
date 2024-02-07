#include "trainnavigation_test.h"
#include "Actors/rail.h"
#include "dependencies/trainnavigation.h"
#include "QtTest"
#include <QPoint>

TrainNavigation_test::TrainNavigation_test(QObject *parent)
    : QObject{parent}
{

}

void TrainNavigation_test::checkNewDirection_test()
{
    Rail testedActualTrainRail;
    Rail newRail;
    bool actualDirection; //value from Train = direction of train

    //test1: connected P3->P0 (train direction to P3)
    actualDirection = true;
    testedActualTrainRail.setLocation(QPoint(0,0),false); //world location
    testedActualTrainRail.setP3RelativeLocation(QPoint(0,10)); //relative to P0 location (= actor loc.)!
    newRail.setLocation(QPoint(0,10),false); //world location
    newRail.setP3RelativeLocation(QPoint(0,10)); //relative to P0 location (= actor loc.)!
    QVERIFY(TrainNavigation::checkNewDirection(actualDirection,&testedActualTrainRail, &newRail) == true);

    //test2: connected P0->P3 (train direction to P3)
    actualDirection = true;
    testedActualTrainRail.setLocation(QPoint(0,0),false); //world location
    testedActualTrainRail.setP3RelativeLocation(QPoint(0,10)); //relative to P0 location (= actor loc.)!
    newRail.setLocation(QPoint(0,20),false); //world location
    newRail.setP3RelativeLocation(QPoint(0,-10)); //relative to P0 location (= actor loc.)!
    QVERIFY(TrainNavigation::checkNewDirection(actualDirection,&testedActualTrainRail, &newRail) == false);

    //test3: connected P0->P0 (train direction to P0)
    actualDirection = false;
    testedActualTrainRail.setLocation(QPoint(0,0),false); //world location
    testedActualTrainRail.setP3RelativeLocation(QPoint(0,10)); //relative to P0 location (= actor loc.)!
    newRail.setLocation(QPoint(0,0),false); //world location
    newRail.setP3RelativeLocation(QPoint(0,-10)); //relative to P0 location (= actor loc.)!
    QVERIFY(TrainNavigation::checkNewDirection(actualDirection,&testedActualTrainRail, &newRail) == true);

    //test4: connected P0->P3 (train direction to P0)
    actualDirection = false;
    testedActualTrainRail.setLocation(QPoint(0,0),false); //world location
    testedActualTrainRail.setP3RelativeLocation(QPoint(0,10)); //relative to P0 location (= actor loc.)!
    newRail.setLocation(QPoint(0,-10),false); //world location
    newRail.setP3RelativeLocation(QPoint(0,10)); //relative to P0 location (= actor loc.)!
    QVERIFY(TrainNavigation::checkNewDirection(actualDirection,&testedActualTrainRail, &newRail) == false);
}
