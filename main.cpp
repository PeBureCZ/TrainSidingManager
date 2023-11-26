#include "mainwindow.h"
#include <QApplication>
#include <Qtimer>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mw;
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]()
    {
        mw.actualizeMap();
        //w.testFce();
        //timer.stop();
    });
    timer.start(30); //tick "per milsec" - no FPS delta tick support
    mw.show();

    return a.exec();
}
