QT += testlib
QT += core gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += ../Src

SOURCES +=  tst_test.cpp \




