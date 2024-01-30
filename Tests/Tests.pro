QT += testlib
QT += core gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += ../Src

SOURCES +=  tst_test.cpp \
    ../Src/Actors/actor.cpp \
    ../Src/Components/boxcollider.cpp \
    ../Src/Components/collider.cpp \
    ../Src/Components/component.cpp \
    ../Src/Components/spherecollider.cpp \
    ../Src/Components/spheretrigger.cpp \
    ../Src/Components/trigger.cpp

HEADERS += \
    ../Src/Actors/actor.h \
    ../Src/Components/boxcollider.h \
    ../Src/Components/collider.h \
    ../Src/Components/component.h \
    ../Src/Components/spherecollider.h \
    ../Src/Components/spheretrigger.h \
    ../Src/Components/trigger.h




