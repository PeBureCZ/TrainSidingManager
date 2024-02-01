#include "rail_test.h"

Rail_test::Rail_test(QObject *parent)
    : QObject{parent}
{}

void Rail_test::setConnectedRail_test()
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

void Rail_test::connectRails_oneRail_test()
{
    Rail* firstRail = new Rail();
    Rail* connectedRail1 = new Rail();

    firstRail->connectRails(connectedRail1,true);

    QVERIFY(firstRail->getConnectedRail(0) == connectedRail1);
    QVERIFY(firstRail->getConnectedRail(1) == nullptr);
    QVERIFY(firstRail->getConnectedRail(2) == nullptr);
    QVERIFY(firstRail->getConnectedRail(3) == nullptr);

    delete firstRail;
    delete connectedRail1;
}

void Rail_test::connectRails_threeRailsOnStart_test()
{
    Rail* firstRail = new Rail();
    Rail* connectedRail1 = new Rail();
    Rail* connectedRail2 = new Rail();
    Rail* connectedRail3 = new Rail();

    firstRail->connectRails(connectedRail1,true);
    firstRail->connectRails(connectedRail2,true);
    firstRail->connectRails(connectedRail3,true);

    QVERIFY(firstRail->getConnectedRail(0) == connectedRail1);
    QVERIFY(firstRail->getConnectedRail(1) == connectedRail2);
    QVERIFY(firstRail->getConnectedRail(2) == nullptr);
    QVERIFY(firstRail->getConnectedRail(3) == nullptr);

    delete firstRail;
    delete connectedRail1;
    delete connectedRail2;
    delete connectedRail3;
}

void Rail_test::connectRails_fullRails_test()
{
    Rail* firstRail = new Rail();
    Rail* connectedRail1 = new Rail();
    Rail* connectedRail2 = new Rail();
    Rail* connectedRail3 = new Rail();
    Rail* connectedRail4 = new Rail();
    Rail* connectedRail5 = new Rail();

    firstRail->connectRails(connectedRail1,true);
    firstRail->connectRails(connectedRail2,true);
    firstRail->connectRails(connectedRail3,false);
    firstRail->connectRails(connectedRail4,false);
    firstRail->connectRails(connectedRail5,false);

    QVERIFY(firstRail->getConnectedRail(0) == connectedRail1);
    QVERIFY(firstRail->getConnectedRail(1) == connectedRail2);
    QVERIFY(firstRail->getConnectedRail(2) == connectedRail3);
    QVERIFY(firstRail->getConnectedRail(3) == connectedRail4);
    QVERIFY(connectedRail5->getConnectedRail(0) == nullptr);
    QVERIFY(connectedRail5->getConnectedRail(1) == nullptr);
    QVERIFY(connectedRail5->getConnectedRail(2) == nullptr);
    QVERIFY(connectedRail5->getConnectedRail(3) == nullptr);

    delete firstRail;
    delete connectedRail1;
    delete connectedRail2;
    delete connectedRail3;
    delete connectedRail4;
    delete connectedRail5;
}

void Rail_test::connectRails_threeRailsOnEnd_test()
{
    Rail* firstRail = new Rail();
    Rail* connectedRail1 = new Rail();
    Rail* connectedRail2 = new Rail();
    Rail* connectedRail3 = new Rail();

    firstRail->connectRails(connectedRail1,false);
    firstRail->connectRails(connectedRail2,false);
    firstRail->connectRails(connectedRail3,false);

    QVERIFY(firstRail->getConnectedRail(0) == nullptr);
    QVERIFY(firstRail->getConnectedRail(1) == nullptr);
    QVERIFY(firstRail->getConnectedRail(2) == connectedRail1);
    QVERIFY(firstRail->getConnectedRail(3) == connectedRail2);
    QVERIFY(connectedRail3->getConnectedRail(0) == nullptr);
    QVERIFY(connectedRail3->getConnectedRail(1) == nullptr);
    QVERIFY(connectedRail3->getConnectedRail(2) == nullptr);
    QVERIFY(connectedRail3->getConnectedRail(3) == nullptr);

    delete firstRail;
    delete connectedRail1;
    delete connectedRail2;
    delete connectedRail3;
}

void Rail_test::connectRails_connectA0ToP0()
{
    Rail* firstRail = new Rail();
    Rail* connectedRail1 = new Rail();

    firstRail->setLocation(QPointF(0,0),false);
    firstRail->setP3RelativeLocation(QPoint(10,0));

    connectedRail1->setLocation(QPointF(10,0),false);
    connectedRail1->setP3RelativeLocation(QPoint(20,0));

    firstRail->connectRails(connectedRail1,true);

    QVERIFY(firstRail->getConnectedRail(0) == connectedRail1);
    QVERIFY(firstRail->getConnectedRail(1) == nullptr);
    QVERIFY(firstRail->getConnectedRail(2) == nullptr);
    QVERIFY(firstRail->getConnectedRail(3) == nullptr);

    QVERIFY(connectedRail1->getConnectedRail(0) == firstRail);
    QVERIFY(connectedRail1->getConnectedRail(1) == nullptr);
    QVERIFY(connectedRail1->getConnectedRail(2) == nullptr);
    QVERIFY(connectedRail1->getConnectedRail(3) == nullptr);

    delete firstRail;
    delete connectedRail1;
}

void Rail_test::connectRails_connectA0ToP3()
{
    Rail* firstRail = new Rail();
    Rail* connectedRail1 = new Rail();

    firstRail->setLocation(QPointF(0,0),false);
    firstRail->setP3RelativeLocation(QPoint(10,0));

    connectedRail1->setLocation(QPointF(20,0),false);
    connectedRail1->setP3RelativeLocation(QPoint(-10,0));

    firstRail->connectRails(connectedRail1,true);

    QVERIFY(firstRail->getConnectedRail(0) == connectedRail1);
    QVERIFY(firstRail->getConnectedRail(1) == nullptr);
    QVERIFY(firstRail->getConnectedRail(2) == nullptr);
    QVERIFY(firstRail->getConnectedRail(3) == nullptr);

    QVERIFY(connectedRail1->getConnectedRail(0) == nullptr);
    QVERIFY(connectedRail1->getConnectedRail(1) == nullptr);
    QVERIFY(connectedRail1->getConnectedRail(2) == firstRail);
    QVERIFY(connectedRail1->getConnectedRail(3) == nullptr);

    delete firstRail;
    delete connectedRail1;
}

void Rail_test::connectRails_connecC1ToP0()
{
    Rail* firstRail = new Rail();
    Rail* connectedRail1 = new Rail();

    firstRail->setLocation(QPointF(0,0),false);
    firstRail->setP3RelativeLocation(QPoint(10,0));

    connectedRail1->setLocation(QPointF(10,0),false);
    connectedRail1->setP3RelativeLocation(QPoint(-10,0));

    firstRail->connectRails(connectedRail1,false);

    QVERIFY(firstRail->getConnectedRail(0) == nullptr);
    QVERIFY(firstRail->getConnectedRail(1) == nullptr);
    QVERIFY(firstRail->getConnectedRail(2) == connectedRail1);
    QVERIFY(firstRail->getConnectedRail(3) == nullptr);

    QVERIFY(connectedRail1->getConnectedRail(0) == firstRail);
    QVERIFY(connectedRail1->getConnectedRail(1) == nullptr);
    QVERIFY(connectedRail1->getConnectedRail(2) == nullptr);
    QVERIFY(connectedRail1->getConnectedRail(3) == nullptr);

    delete firstRail;
    delete connectedRail1;
}

void Rail_test::connectRails_connectC1ToP3()
{
    Rail* firstRail = new Rail();
    Rail* connectedRail1 = new Rail();

    firstRail->setLocation(QPointF(0,0),false);
    firstRail->setP3RelativeLocation(QPoint(10,0));

    connectedRail1->setLocation(QPointF(20,0),false);
    connectedRail1->setP3RelativeLocation(QPoint(-10,0));

    firstRail->connectRails(connectedRail1,false);

    QVERIFY(firstRail->getConnectedRail(0) == nullptr);
    QVERIFY(firstRail->getConnectedRail(1) == nullptr);
    QVERIFY(firstRail->getConnectedRail(2) == connectedRail1);
    QVERIFY(firstRail->getConnectedRail(3) == nullptr);

    QVERIFY(connectedRail1->getConnectedRail(0) == nullptr);
    QVERIFY(connectedRail1->getConnectedRail(1) == nullptr);
    QVERIFY(connectedRail1->getConnectedRail(2) == firstRail);
    QVERIFY(connectedRail1->getConnectedRail(3) == nullptr);

    delete firstRail;
    delete connectedRail1;
}


Rail_test::~Rail_test()
{
}
