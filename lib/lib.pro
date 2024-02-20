
QT += core gui widgets

TEMPLATE = lib
DEFINES += LIB_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../ui/mwComponents/customqgraphicsview.cpp \
    Actors/Constructors/actorconstructor.cpp \
    Actors/Constructors/portalconstructor.cpp \
    Actors/Constructors/railconstructor.cpp \
    Actors/Constructors/railobjectconstructor.cpp \
    Actors/Constructors/railselector.cpp \
    Actors/Constructors/selectconstructor.cpp \
    Actors/Constructors/signalconstructor.cpp \
    Actors/Vagons/eas.cpp \
    Actors/Vagons/vagon.cpp \
    Actors/Vagons/zaes.cpp \
    Actors/actor.cpp \
    Actors/cd730.cpp \
    Actors/cd753.cpp \
    Actors/diesellocomotive.cpp \
    Actors/electriclocomotive.cpp \
    Actors/locomotive.cpp \
    Actors/movable.cpp \
    Actors/portal.cpp \
    Actors/rail.cpp \
    Actors/railwayobject.cpp \
    Actors/signal.cpp \
    Actors/train.cpp \
    Actors/vehicle.cpp \
    dependencies/WorldMapActorLogic.cpp \
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

HEADERS += \
    ../ui/mwComponents/customqgraphicsview.h \
    Actors/Constructors/actorconstructor.h \
    Actors/Constructors/portalconstructor.h \
    Actors/Constructors/railconstructor.h \
    Actors/Constructors/railobjectconstructor.h \
    Actors/Constructors/railselector.h \
    Actors/Constructors/selectconstructor.h \
    Actors/Constructors/signalconstructor.h \
    Actors/Vagons/eas.h \
    Actors/Vagons/vagon.h \
    Actors/Vagons/zaes.h \
    Actors/actor.h \
    Actors/cd730.h \
    Actors/cd753.h \
    Actors/diesellocomotive.h \
    Actors/electriclocomotive.h \
    Actors/locomotive.h \
    Actors/movable.h \
    Actors/portal.h \
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
    dependencies/Enums/ActorsEnum.h \
    dependencies/Enums/BlockChannels.h \
    dependencies/Enums/ComponentsEnum.h \
    dependencies/Enums/ConsoleEnums.h \
    dependencies/Enums/MainWindowEnum.h \
    dependencies/Enums/SignalEnum.h \
    dependencies/Enums/TrainsEnum.h \
    dependencies/WorldMapActorLogic.h \
    dependencies/interfacewindow.h \
    dependencies/managerconsole.h \
    dependencies/managerconsolelogic.h \
    dependencies/settings.h \
    dependencies/trainnavigation.h \
    dependencies/railnavigation.h \
    dependencies/spritecolection.h \
    dependencies/worldcollide.h \
    dependencies/worldmap.h \
    dependencies/worldviewmap.h \
    lib_global.h \

INCLUDEPATH += ../ui


# Default rules for deployment.
unix
{
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
