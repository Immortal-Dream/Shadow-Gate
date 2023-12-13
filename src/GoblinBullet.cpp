#include "header.h"
#include "GoblinBullet.h"

GoblinBullet::GoblinBullet(BaseEngine* baseEngine, int screenX, int screenY, int width, int height)
	: Bullet(baseEngine, screenX, screenY, width, height, "images/weapons/goblin_bullet.png")
{
    bulletID = 1;
    damage = 2;
    speed = 4;
	strcpy(bulletName, "GoblinBullet");
}

void GoblinBullet::virtDraw()
{
	if (isVisible()) {
		image.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
	}
}

void GoblinBullet::virtDoUpdate(int iCurrentTime)
{
	autoMove();
}
