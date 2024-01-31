#include "actor_test.h"

Actor_test::Actor_test(QObject *parent)
    : QObject{parent}
{
    full_test();
}

void Actor_test::getName_test()
{
    qDebug() << "test name";
    Actor testedActor;
    testedActor.setName("testedName");
    QVERIFY(testedActor.getName() == "testedName");
}

void Actor_test::location_test()
{
    qDebug() << "test location";
    Actor testedActor;
    testedActor.setLocation(QPoint(1,4), false);
    QVERIFY(testedActor.getLocation() == QPoint(1,4));
    testedActor.setLocation(QPoint(-5,-8), false);
    QVERIFY(testedActor.getLocation() == QPoint(-5,-8));
    testedActor.setLocation(QPointF(10,4), false);
    QVERIFY(testedActor.getLocation() == QPoint(10,4));
}

void Actor_test::full_test()
{
    getName_test();
    location_test();
}
