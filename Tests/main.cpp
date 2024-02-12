#include <QTest>
#include <Actors_tests/actor_test.h>
#include <Actors_tests/rail_test.h>
#include "dependencies_tests/worldmap_test.h"
#include "Actors_tests/signal_test.h"
#include "Actors_tests/train_test.h"
#include "dependencies_tests/trainnavigation_test.h"

#include "librarysubcore.h"

int main(int argc, char *argv[])
{
    int status = 0;

    //this line fix QT ("auto run test" sometimes disable Tools/Tests menu -> QT bug?)
    QTest::qExec(new WorldMap_test, argc, argv);

    auto runTest = [&status, argc, argv](QObject* obj)
    {
        status |= QTest::qExec(obj, argc, argv);
    };

    runTest(new Actor_test);
    runTest(new Rail_test);
    runTest(new Signal_test);
    runTest(new Train_test);
    runTest(new TrainNavigation_test);
    return status;
}
