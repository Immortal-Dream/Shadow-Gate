#include "header.h"
#include "HeroBullet.h"


HeroBullet::HeroBullet(BaseEngine* baseEngine, int screenX, int screenY, int width, int height, std::string url)
	: Bullet(baseEngine, screenX, screenY, width, height, url)
{
	bulletID = 0;
	damage = 2;
	speed = 4;
	strcpy(bulletName, "HeroBullet");
}

void HeroBullet::virtDraw()
{

	if (isVisible()) {
		image.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
	}
}

void HeroBullet::virtDoUpdate(int iCurrentTime)
{
	if (isVisible())
	{
		destoryBullet();
		if (m_iCurrentScreenX >= 0 && m_iCurrentScreenX <= 1300) {
			m_iCurrentScreenX += (int)round(speed * xCos);
		}
		if (m_iCurrentScreenY >= 0 && m_iCurrentScreenY <= 800) {
			m_iCurrentScreenY += (int)round(speed * ySin);
		}
	}
}
/*
* the function used to delete bullet, either goes out of bound or
* hit the enemies. 
*/
void HeroBullet::destoryBullet()
{
	if (isOutOfScreen())
	{
		// when the drawable objects array is changed, this methode is called to notify 
		// the framework avoid using the array after it has changed. 
		getEngine()->drawableObjectsChanged();
		// remove this object from the displayable objects array
		getEngine()->removeDisplayableObject(this);
		// delete this object
		delete this;
	}
}
