#include "header.h"
#include "Bullet.h"



Bullet::Bullet(BaseEngine* baseEngine, int screenX, int screenY, int width, int height, std::string url)
	: DisplayableObject(baseEngine)
	, image(baseEngine->loadImage(url, false))
{
	m_iCurrentScreenX = screenX;
	m_iCurrentScreenY = screenY;
	m_iDrawWidth = width;
	m_iDrawHeight = height;
	damage = 0;
	strcpy(bulletName, "Bullet");
	bulletID = 0;
	speed = 0;
	xCos = 1.0;
	ySin = 0.0;
}

void Bullet::setDamage(int power)
{
	damage = power;
}

void Bullet::setBulletID(int id)
{ 
	bulletID = id;
}

void Bullet::setSpeed(int value)
{
	speed = value;
}

void Bullet::setXCos(double cosValue)
{
	xCos = cosValue;
}

void Bullet::setYSin(double sinValue)
{
	ySin = sinValue;
}

int Bullet::getDamage()
{
	return damage;
}

int Bullet::getBulletID()
{
	return bulletID;
}

int Bullet::getSpeed()
{
	return speed;
}

double Bullet::getXCos()
{
	return xCos;
}

double Bullet::getYSin()
{
	return ySin;
}

void Bullet::virtDraw()
{
}

void Bullet::virtDoUpdate(int iCurrentTime)
{
}

void Bullet::destoryBullet()
{
	if (isOutOfScreen())
	{
		getEngine()->drawableObjectsChanged();
		getEngine()->removeDisplayableObject(this);
		delete this;
	}
}
/*
* judge whether the bullet is out of bound
*/
bool Bullet::isOutOfScreen()
{
	int isOutside = false;
	if (getDrawingRegionLeft() <= 0 || getDrawingRegionTop() <=0 ||
		getDrawingRegionRight() >= getEngine()->getWindowWidth() ||
		getDrawingRegionBottom() >= getEngine()->getWindowHeight())
	{
		isOutside = true;
	}
	return isOutside;
}

// manually delete the bullet
void Bullet::deleteBullet()
{
	getEngine()->drawableObjectsChanged();
	getEngine()->removeDisplayableObject(this);
	delete this;
}

/*
* control the moving logic of the bullet
*/
void Bullet::autoMove()
{
	if (isVisible())
	{
		if (isOutOfScreen())
		{
			getEngine()->drawableObjectsChanged();
			getEngine()->removeDisplayableObject(this);
			delete this;
			return;
		}
		if (m_iCurrentScreenX >= 0 && m_iCurrentScreenX <= 1300) {
			m_iCurrentScreenX += (int)round(speed * xCos);
		}
		if (m_iCurrentScreenY >= 0 && m_iCurrentScreenY <= 800) {
			m_iCurrentScreenY += (int)round(speed * ySin);
		}
	}
}

char* Bullet::getBulletName()
{
	return bulletName;
}
