#include <QTest>
#include <Actors_tests/actor_test.h>
#include <Actors_tests/rail_test.h>

int main(int argc, char *argv[])
{
    int status = 0;

    auto runTest = [&status, argc, argv](QObject* obj)
    {
        status |= QTest::qExec(obj, argc, argv);
    };

    runTest(new Actor_test);
    runTest(new Rail_test);
    return status;



    //return QTest::qExec(new Actor_test, argc, argv);
}
