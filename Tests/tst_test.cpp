#include <QtTest>
#include <QCoreApplication>
#include "Actors_tests/actor_test.h"

#include "Actors/actor.h"

class TEST : public QObject
{
    Q_OBJECT

public:
    TEST();
    ~TEST();

private slots:
    void fullActor_test();

};

TEST::TEST()
{

}

TEST::~TEST()
{

}

void TEST::fullActor_test()
{
    Actor_test actor;
}

QTEST_MAIN(TEST)

#include "tst_test.moc"
