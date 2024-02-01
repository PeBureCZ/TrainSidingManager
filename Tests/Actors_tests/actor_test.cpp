#include "actor_test.h"

Actor_test::Actor_test(QObject *parent)
    : QObject{parent}
{
}

void Actor_test::initTestCase()
{

}

void Actor_test::getName_test()
{
    Actor testedActor;
    testedActor.setName("testedName");
    QVERIFY(testedActor.getName() == "testedName");
}

void Actor_test::location_test()
{
    Actor testedActor;
    testedActor.setLocation(QPoint(1,4), false);
    QVERIFY(testedActor.getLocation() == QPoint(1,4));
    testedActor.setLocation(QPoint(-5,-8), false);
    QVERIFY(testedActor.getLocation() == QPoint(-5,-8));
    testedActor.setLocation(QPointF(10,4), false);
    QVERIFY(testedActor.getLocation() == QPoint(10,4));
}

void Actor_test::cleanupTestCase()
{

}


