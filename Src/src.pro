QT       += core gui widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


DISTFILES += \
    README.md \
    images/CD730.png \
    images/loco.png \
    images/signal_green.png \
    images/signal_red.png \
    images/signal_white.png \
    images/signal_yellow.png

SOURCES += \
    main.cpp \
    mainWindow/mainwindow.cpp \
    mwComponents/buttonfunctions.cpp \
    mwComponents/interfacewindow.cpp \
    mwComponents/customqgraphicsview.cpp \
    mwComponents/mwlogic.cpp


HEADERS += \
    mainWindow/mainwindow.h \
    mwComponents/buttonfunctions.h \
    mwComponents/interfacewindow.h \
    mwComponents/customqgraphicsview.h \
    mwComponents/mwlogic.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lib/release/ -llib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lib/debug/ -llib

INCLUDEPATH += $$PWD/../lib
DEPENDPATH += $$PWD/../lib
