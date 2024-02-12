#ifndef LIBRARYCORE_H
#define LIBRARYCORE_H

#include "lib_global.h"
#include <QObject>


class LIB_EXPORT LibraryCore : public QObject
{
public:
    LibraryCore(QObject* parent = nullptr);
    int testCustomLib(int a, int b);
};

#endif // LIBRARYCORE_H
