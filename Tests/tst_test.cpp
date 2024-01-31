#include <QtTest>
#include <QCoreApplication>

#include "Actors_tests/actor_test.h"
#include "Actors_tests/rail_test.h"




class TEST : public QObject
{
    Q_OBJECT

public:
    TEST();
    ~TEST();

private slots:
    void fullActor_test();
    void fullRail_test();

};

TEST::TEST()
{

}

TEST::~TEST()
{

}

void TEST::fullActor_test()
{
    Actor_test test;
}

void TEST::fullRail_test()
{
    Rail_test test;
}

QTEST_MAIN(TEST)

#include "tst_test.moc"
