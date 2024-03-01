#ifndef SPRITECOLECTION_H
#define SPRITECOLECTION_H

#include <QString>
#include <QApplication>
#include <QVector>
#include <QPixmap>
#include <array>
#include <QGraphicsPixmapItem>

enum spriteEnums
{
    //HAVE TO ADD TO "SpriteColection" STRUCT TOO!!!
    EMPTY_SPRITE = 0,

    //LOCOMOTIVES - ACTIVE
    LOCO_SPRITE,
    CD730_ACTIVE_SPRITE,
    CD753_ACTIVE_SPRITE,

    //LOCOMOTIVES - SELECTED
    CD753_SELECTED_SPRITE,

    //VAGONS - ACTIVE
    EAS_ACTIVE_SPRITE,
    ZAES_ACTIVE_SPRITE,

    //VAGONS - SELECTED
    EAS_SELECTED_SPRITE,
    ZAES_SELECTED_SPRITE,

    //ADDITIONAL
    RAIL_SPRITE,  
    PORTAL_SPRITE,

    //SIGNAL
    STOP_SIGNAL_SPRITE,
    PROCEED_SIGNAL_SPRITE,
    CAUTION_SIGNAL_SPRITE,
    WHITE_SIGNAL_SPRITE,
    FULL_SIGNAL_SPRITE,
    NO_SIGNAL_SPRITE,
    SELECTED_SIGNAL_SPRITE,
};

struct SpriteColection
{
    const QVector<QString>relativePaths =
    {
        //HAVE TO ADD TO "spriteEnums" TOO!!!
        //EMPTY = 0
            "",

        //LOCOMOTIVES - ACTIVE
            "/images/loco.png",
            "/images/CD730.png",
            "/images/CD753.png",

        //LOCOMOTIVES - SELECTED
            "/images/CD753_selected.png",

        //VAGONS - ACTIVE
            "/images/Eas.png",
            "/images/Zaes.png",

        //VAGONS - SELECTED
            "/images/Eas_selected.png",
            "/images/Zaes_selected.png",

        //ADDITIONAL
            "/images/rail.png",
            "/images/portal.png",

        //SIGNAL
        "/images/signal_red.png",
        "/images/signal_green.png",
        "/images/signal_yellow.png",
        "/images/signal_white.png",
        "/images/signal_full.png",
        "/images/signal_full_noPlace.png",
        "/images/selected_signal.png",
    };

    QString relativeDirectory;
    QVector<QString> filePath;
    SpriteColection();
    QPixmap getSprite(int indexOfSprite);

public slots:
};

#endif // SPRITECOLECTION_H
