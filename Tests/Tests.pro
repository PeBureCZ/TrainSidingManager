QT += testlib core gui widgets
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += ../Src



SOURCES += \
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
    Actors_tests/rail_test.cpp \
    Actors_tests/actor_test.cpp \


HEADERS += \
    ../Src/Actors/actor.h \
    ../Src/Actors/rail.h \
    ../Src/Actors/railwayobject.h \
    ../Src/Components/boxcollider.h \
    ../Src/Components/collider.h \
    ../Src/Components/component.h \
    ../Src/Components/spherecollider.h \
    ../Src/Components/spheretrigger.h \
    ../Src/Components/trigger.h \
    Actors_tests/rail_test.h \
    Actors_tests/actor_test.h \




