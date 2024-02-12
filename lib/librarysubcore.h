#ifndef LIBRARYSUBCORE_H
#define LIBRARYSUBCORE_H

#include "librarycore.h"
#include <QObject>
#include <QApplication>
#include <QGraphicsView>

class LIB_EXPORT LibrarySubCore : public LibraryCore
{
    Q_OBJECT
public:
    LibrarySubCore(QObject *parent = nullptr);
};

#endif // LIBRARYSUBCORE_H
