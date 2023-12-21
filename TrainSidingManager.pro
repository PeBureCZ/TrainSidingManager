QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Actors/actor.cpp \
    Actors/actorconstructor.cpp \
    Actors/cd730.cpp \
    Actors/diesellocomotive.cpp \
    Actors/electriclocomotive.cpp \
    Actors/locomotive.cpp \
    Actors/movable.cpp \
    Actors/rail.cpp \
    Actors/railconstructor.cpp \
    Actors/railwayobject.cpp \
    Actors/train.cpp \
    Actors/vehicle.cpp \
    Components/boxcollider.cpp \
    Components/collider.cpp \
    Components/component.cpp \
    Components/spherecollider.cpp \
    Components/spheretrigger.cpp \
    Components/trigger.cpp \
    customqgraphicsview.cpp \
    dependencies/interfacewindow.cpp \
    dependencies/mwlogic.cpp \
    dependencies/trainnavigation.cpp \
    main.cpp \
    mainwindow.cpp \
    railnavigation.cpp \
    spritecolection.cpp \
    worldcollide.cpp \
    worldmap.cpp \
    worldviewmap.cpp


HEADERS += \
    Actors/actor.h \
    Actors/actorconstructor.h \
    Actors/cd730.h \
    Actors/diesellocomotive.h \
    Actors/electriclocomotive.h \
    Actors/locomotive.h \
    Actors/movable.h \
    Actors/rail.h \
    Actors/railconstructor.h \
    Actors/railwayobject.h \
    Actors/train.h \
    Actors/vehicle.h \
    Components/boxcollider.h \
    Components/collider.h \
    Components/component.h \
    Components/spherecollider.h \
    Components/spheretrigger.h \
    Components/trigger.h \
    customqgraphicsview.h \
    dependencies/interfacewindow.h \
    dependencies/mwlogic.h \
    dependencies/trainnavigation.h \
    mainwindow.h \
    railnavigation.h \
    spritecolection.h \
    worldcollide.h \
    worldmap.h \
    worldviewmap.h


FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/loco.png
