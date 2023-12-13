#include "header.h"
#include "OrcBullet.h"

OrcBullet::OrcBullet(BaseEngine* baseEngine, int screenX, int screenY, int width, int height)
    : Bullet(baseEngine, screenX, screenY, width, height, "images/weapons/orc_bullet.png")
{
    bulletID = 1;
    damage = 1;
    speed = 3;
	strcpy(bulletName, "OrcBullet");
}

void OrcBullet::virtDraw()
{
	if (isVisible()) {
		image.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
	}
}

void OrcBullet::virtDoUpdate(int iCurrentTime)
{
	autoMove();
}
