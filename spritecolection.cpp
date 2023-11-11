#include "spritecolection.h"

SpriteColection::SpriteColection()
{
    relativeDirectory = QApplication::applicationDirPath();
    filePath = {""};
}

QPixmap SpriteColection::loco()
{
    //QString pngPath = relativeDirectory + "/loco.png";
    QPixmap pixmap(relativeDirectory + "/images/loco.png");
    return pixmap;
}


/*


       QString pngPath = QApplication::applicationDirPath() + "/loco.png";

       QGraphicsItem* trainItem = new QGraphicsPixmapItem(pixmap);

 */
