#include "rail_test.h"

Rail_test::Rail_test(QObject *parent)
    : QObject{parent}
{
    full_test();
}

void Rail_test::conection_test()
{
    Rail* firstRail = new Rail();
    Rail* secondRail = new Rail();
    firstRail->setConnectedRail(secondRail,0);
    secondRail->setConnectedRail(firstRail, 0);
    QVERIFY(secondRail->getConnectedRail(0) == firstRail);
    QVERIFY(firstRail->getConnectedRail(0) == secondRail);
    delete firstRail;
    delete secondRail;
}

void Rail_test::full_test()
{
    conection_test();
}

Rail_test::~Rail_test()
{
}
