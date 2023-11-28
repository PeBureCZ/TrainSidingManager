#include "mainwindow.h"
#include <QApplication>
#include <Qtimer>
#include <QElapsedTimer>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mw;
    QTimer timer;
    QElapsedTimer responseTimer;
    responseTimer.restart();
    QObject::connect(&timer, &QTimer::timeout, [&]()
    {
        mw.actualizeMap();
        mw.actualizeDeltaTime(responseTimer.elapsed());
        responseTimer.restart();
    });
    timer.start(20); //tick "per milsec" - no FPS delta tick support
    mw.show();

    return a.exec();
}
