#include <QtTest>
#include <QCoreApplication>

#include "Actors/actor.h"

class TEST : public QObject
{
    Q_OBJECT

public:
    TEST();
    ~TEST();

private slots:
    void test_getActorName();

};

TEST::TEST()
{

}

TEST::~TEST()
{

}

void TEST::test_getActorName()
{
    Actor testedActor;
    testedActor.setName("testedName");
    QVERIFY(testedActor.getName() == "testedName");
}

QTEST_MAIN(TEST)

#include "tst_test.moc"
