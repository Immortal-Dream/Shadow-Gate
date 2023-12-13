#include "header.h"
#include "BossBullet.h"

BossBullet::BossBullet(BaseEngine* baseEngine, int screenX, int screenY, int width, int height)
    : Bullet(baseEngine, screenX, screenY, width, height, "images/weapons/boss_bullet.png")
{
    strcpy(bulletName, "BossBullet");
    bulletID = 1;
    damage = 2;
    speed = 5;
}

void BossBullet::virtDraw()
{
    if (isVisible()) {
        image.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
    }
}

void BossBullet::virtDoUpdate(int iCurrentTime)
{
    autoMove();
}
