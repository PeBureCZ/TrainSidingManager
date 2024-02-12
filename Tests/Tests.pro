QT += testlib core gui widgets
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

INCLUDEPATH += ../Src

SOURCES += \
    main.cpp \
    Actors_tests/Signal_test.cpp \
    Actors_tests/rail_test.cpp \
    Actors_tests/train_test.cpp \
    dependencies_tests/trainnavigation_test.cpp \
    dependencies_tests/worldmap_test.cpp \
    Actors_tests/actor_test.cpp \

HEADERS += \
    Actors_tests/actor_test.h \
    Actors_tests/rail_test.h \
    Actors_tests/signal_test.h \
    Actors_tests/train_test.h \
    dependencies_tests/trainnavigation_test.h \
    dependencies_tests/worldmap_test.h \

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lib/release/ -llib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lib/debug/ -llib

INCLUDEPATH += $$PWD/../lib
DEPENDPATH += $$PWD/../lib
