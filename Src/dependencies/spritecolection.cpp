#include "spritecolection.h"

SpriteColection::SpriteColection()
{
    relativeDirectory = QApplication::applicationDirPath();
    filePath = {""};
}

QPixmap SpriteColection::getSprite(int indexOfSprite)
{
    QPixmap pixmap(relativeDirectory + relativePaths[indexOfSprite]);
    return pixmap;
}
