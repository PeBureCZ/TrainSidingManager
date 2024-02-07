QT += testlib core gui widgets
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += ../Src



SOURCES += \
    ../Src/Actors/Constructors/actorconstructor.cpp \
    ../Src/Actors/Constructors/portalconstructor.cpp \
    ../Src/Actors/Constructors/railconstructor.cpp \
    ../Src/Actors/Constructors/railobjectconstructor.cpp \
    ../Src/Actors/Constructors/railselector.cpp \
    ../Src/Actors/Constructors/selectconstructor.cpp \
    ../Src/Actors/Constructors/signalconstructor.cpp \
    ../Src/Actors/Vagons/eas.cpp \
    ../Src/Actors/Vagons/vagon.cpp \
    ../Src/Actors/cd730.cpp \
    ../Src/Actors/diesellocomotive.cpp \
    ../Src/Actors/electriclocomotive.cpp \
    ../Src/Actors/locomotive.cpp \
    ../Src/Actors/movable.cpp \
    ../Src/Actors/signal.cpp \
    ../Src/Actors/train.cpp \
    ../Src/Actors/vehicle.cpp \
    ../Src/dependencies/managerconsole.cpp \
    ../Src/dependencies/managerconsolelogic.cpp \
    ../Src/dependencies/railnavigation.cpp \
    ../Src/dependencies/spritecolection.cpp \
    ../Src/dependencies/trainnavigation.cpp \
    ../Src/dependencies/worker.cpp \
    ../Src/dependencies/worldcollide.cpp \
    ../Src/dependencies/worldmap.cpp \
    ../Src/dependencies/worldviewmap.cpp \
    ../Src/mainWindow/customqgraphicsview.cpp \
    Actors_tests/Signal_test.cpp \
    Actors_tests/rail_test.cpp \
    Actors_tests/train_test.cpp \
    dependencies_tests/trainnavigation_test.cpp \
    dependencies_tests/worldmap_test.cpp \
    main.cpp \
    ../Src/Actors/actor.cpp \
    ../Src/Actors/rail.cpp \
    ../Src/Actors/railwayobject.cpp \
    ../Src/Components/boxcollider.cpp \
    ../Src/Components/collider.cpp \
    ../Src/Components/component.cpp \
    ../Src/Components/spherecollider.cpp \
    ../Src/Components/spheretrigger.cpp \
    ../Src/Components/trigger.cpp \
    Actors_tests/actor_test.cpp \


HEADERS += \
    ../Src/Actors/Constructors/actorconstructor.h \
    ../Src/Actors/Constructors/portalconstructor.h \
    ../Src/Actors/Constructors/railconstructor.h \
    ../Src/Actors/Constructors/railobjectconstructor.h \
    ../Src/Actors/Constructors/railselector.h \
    ../Src/Actors/Constructors/selectconstructor.h \
    ../Src/Actors/Constructors/signalconstructor.h \
    ../Src/Actors/Vagons/eas.h \
    ../Src/Actors/Vagons/vagon.h \
    ../Src/Actors/actor.h \
    ../Src/Actors/cd730.h \
    ../Src/Actors/locomotive.h \
    ../Src/Actors/diesellocomotive.h \
    ../Src/Actors/electriclocomotive.h \
    ../Src/Actors/movable.h \
    ../Src/Actors/rail.h \
    ../Src/Actors/railwayobject.h \
    ../Src/Actors/signal.h \
    ../Src/Actors/train.h \
    ../Src/Actors/vehicle.h \
    ../Src/Components/boxcollider.h \
    ../Src/Components/collider.h \
    ../Src/Components/component.h \
    ../Src/Components/spherecollider.h \
    ../Src/Components/spheretrigger.h \
    ../Src/Components/trigger.h \
    ../Src/dependencies/Enums/SignalEnum.h \
    ../Src/dependencies/managerconsole.h \
    ../Src/dependencies/managerconsolelogic.h \
    ../Src/dependencies/railnavigation.h \
    ../Src/dependencies/spritecolection.h \
    ../Src/dependencies/trainnavigation.h \
    ../Src/dependencies/worker.h \
    ../Src/dependencies/worldcollide.h \
    ../Src/dependencies/worldmap.h \
    ../Src/dependencies/worldviewmap.h \
    ../Src/mainWindow/customqgraphicsview.h \
    Actors_tests/actor_test.h \
    Actors_tests/rail_test.h \
    Actors_tests/signal_test.h \
    Actors_tests/train_test.h \
    dependencies_tests/trainnavigation_test.h \
    dependencies_tests/worldmap_test.h
