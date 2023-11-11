#ifndef SPRITECOLECTION_H
#define SPRITECOLECTION_H

#include <QString>
#include <QApplication>
#include <QVector>
#include <QPixmap>
#include <QGraphicsPixmapItem>

struct SpriteColection
{
    QString relativeDirectory;
    QVector<QString> filePath;
    SpriteColection();
    QPixmap loco();

};

#endif // SPRITECOLECTION_H
