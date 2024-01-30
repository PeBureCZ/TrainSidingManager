QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Actors/Constructors/actorconstructor.cpp \
    Actors/Constructors/railconstructor.cpp \
    Actors/Constructors/railobjectconstructor.cpp \
    Actors/Constructors/railselector.cpp \
    Actors/Constructors/selectconstructor.cpp \
    Actors/Constructors/signalconstructor.cpp \
    Actors/actor.cpp \
    Actors/cd730.cpp \
    Actors/diesellocomotive.cpp \
    Actors/electriclocomotive.cpp \
    Actors/locomotive.cpp \
    Actors/movable.cpp \
    Actors/rail.cpp \
    Actors/railwayobject.cpp \
    Actors/signal.cpp \
    Actors/train.cpp \
    Actors/vehicle.cpp \
    main.cpp \
    Components/boxcollider.cpp \
    Components/collider.cpp \
    Components/component.cpp \
    Components/spherecollider.cpp \
    Components/spheretrigger.cpp \
    Components/trigger.cpp \
    dependencies/managerconsole.cpp \
    dependencies/managerconsolelogic.cpp \
    dependencies/trainnavigation.cpp \
    dependencies/railnavigation.cpp \
    dependencies/spritecolection.cpp \
    dependencies/worldcollide.cpp \
    dependencies/worldmap.cpp \
    dependencies/worldviewmap.cpp \
    mainWindow/interfacewindow.cpp \
    mainWindow/customqgraphicsview.cpp \
    mainWindow/mwlogic.cpp \
    mainWindow/mainwindow.cpp

HEADERS += \
    Actors/Constructors/actorconstructor.h \
    Actors/Constructors/railconstructor.h \
    Actors/Constructors/railobjectconstructor.h \
    Actors/Constructors/railselector.h \
    Actors/Constructors/selectconstructor.h \
    Actors/Constructors/signalconstructor.h \
    Actors/actor.h \
    Actors/cd730.h \
    Actors/diesellocomotive.h \
    Actors/electriclocomotive.h \
    Actors/locomotive.h \
    Actors/movable.h \
    Actors/rail.h \
    Actors/railwayobject.h \
    Actors/signal.h \
    Actors/train.h \
    Actors/vehicle.h \
    Components/boxcollider.h \
    Components/collider.h \
    Components/component.h \
    Components/spherecollider.h \
    Components/spheretrigger.h \
    Components/trigger.h \
    dependencies/interfacewindow.h \
    dependencies/managerconsole.h \
    dependencies/managerconsolelogic.h \
    dependencies/trainnavigation.h \
    dependencies/railnavigation.h \
    dependencies/spritecolection.h \
    dependencies/worldcollide.h \
    dependencies/worldmap.h \
    dependencies/worldviewmap.h \
    mainWindow/interfacewindow.h \
    mainWindow/customqgraphicsview.h \
    mainWindow/mwlogic.h \
    mainWindow/mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md \
    images/CD730.png \
    images/loco.png \
    images/signal_green.png \
    images/signal_red.png \
    images/signal_white.png \
    images/signal_yellow.png
