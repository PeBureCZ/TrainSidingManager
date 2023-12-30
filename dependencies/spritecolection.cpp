#include "spritecolection.h"

SpriteColection::SpriteColection()
{
    relativeDirectory = QApplication::applicationDirPath();
    filePath = {""};
}

QPixmap SpriteColection::empty()
{
    QPixmap pixmap;
    return pixmap;
}

QPixmap SpriteColection::loco()
{
    QPixmap pixmap(relativeDirectory + "/images/loco.png");
    return pixmap;
}

QPixmap SpriteColection::cd730()
{
    QPixmap pixmap(relativeDirectory + "/images/CD730.png");
    return pixmap;
}

QPixmap SpriteColection::redSignal()
{
    QPixmap pixmap(relativeDirectory + "/images/signal_red.png");
    return pixmap;
}

QPixmap SpriteColection::greenSignal()
{
    QPixmap pixmap(relativeDirectory + "/images/signal_green.png");
    return pixmap;
}

QPixmap SpriteColection::yellowSignal()
{
    QPixmap pixmap(relativeDirectory + "/images/signal_yellow.png");
    return pixmap;
}

QPixmap SpriteColection::whiteSignal()
{
    QPixmap pixmap(relativeDirectory + "/images/signal_white.png");
    return pixmap;
}

QPixmap SpriteColection::rail()
{
    QPixmap pixmap(relativeDirectory + "/images/rail.png");
    return pixmap;
}

QPixmap SpriteColection::fullSignal()
{
    QPixmap pixmap(relativeDirectory + "/images/signal_full.png");
    return pixmap;
}

QPixmap SpriteColection::noPlaceSignal()
{
    QPixmap pixmap(relativeDirectory + "/images/signal_full_noPlace.png");
    return pixmap;
}
