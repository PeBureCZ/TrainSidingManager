#include "mainWindow/interfacewindow.h"
#include <QApplication>
#include <Qtimer>
#include <QElapsedTimer>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InterfaceWindow mw;
    mw.show();
    QTimer timer;
    QElapsedTimer responseTimer;
    responseTimer.restart();

    QObject::connect(&timer, &QTimer::timeout, [&]()
    {
        mw.actualizeMap();
        mw.actualizeDeltaTime(responseTimer.elapsed());
        responseTimer.restart();
    });
    timer.start(30); //tick "per milsec" - no FPS delta tick support
    return a.exec();
}
