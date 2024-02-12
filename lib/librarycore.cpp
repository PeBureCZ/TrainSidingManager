#include "librarycore.h"

LibraryCore::LibraryCore(QObject* parent) : QObject(parent)
{

}

int LibraryCore::testCustomLib(int a, int b)
{
    return a * b;
}
