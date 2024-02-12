#include "spritecolection.h"

SpriteColection::SpriteColection()
{
    relativeDirectory = QApplication::applicationDirPath();
    filePath = {""};
}

QPixmap SpriteColection::getSprite(int indexOfSprite)
{
    QPixmap pixmap;
    if (indexOfSprite == EMPTY_SPRITE) return pixmap;
    pixmap.load(relativeDirectory + relativePaths[indexOfSprite]);
    return pixmap;
}
