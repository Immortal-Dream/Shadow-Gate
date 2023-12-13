#include "header.h"
#include "FireBullet.h"
#include "TimeUtil.h"

FireBullet::FireBullet(BaseEngine* baseEngine, int screenX, int screenY, int width, int height)
    : Bullet(baseEngine, screenX, screenY, width, height, "images/weapons/goblin_bullet.png")
{
    imageID = 0;
    // switch time for dynamic fire ball
    previousSwitchTime = 0;
    // switch interval for dynamic fire ball, in milliseconds
    switchInterval = 80;
    bulletID = 1;
    damage = 3;
    strcpy(bulletName, "FireBullet");
    speed = 2;
    for (int i = 0; i < 6; i++)
    {
        char path[35];
        sprintf(path, "images/weapons/Fire%d.png",i+1);
        fireImages[i] = ImageManager::loadImage(path, true);
    }
}

void FireBullet::virtDraw()
{
    if (isVisible())
    {
        
        fireImages[imageID].renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, 
            m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
        if (TimeUtil::getTimeInterval(TimeUtil::getCurrentTime(), previousSwitchTime) > switchInterval)
        {
            previousSwitchTime = TimeUtil::getCurrentTime();
            imageID++;
            imageID %= 6;      
        }
    }
}

void FireBullet::virtDoUpdate(int iCurrentTime)
{
    autoMove();
}
