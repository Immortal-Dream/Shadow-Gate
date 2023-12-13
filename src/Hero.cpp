#include "header.h"
#include "Scyjl15Engine.h"
#include "Hero.h"

Hero::Hero(BaseEngine* baseEngine)
	: Character(baseEngine, 200, 300, 80, 80, "images/characters/Warrior.png"), rotator(0)
{
	shield = maximumShield = 6;
	hp = maximumHP = 6;
	lastRecover = 0;
	recoverInterval = 3500;
	energe = maximumEnerge = 300;
	weapon = new MappableMaskImage(&rotator, getXCentre() - 10, getYCentre() - 10, getEngine(), "images/weapons/gun.png", true);
	weapon->setTransparencyColour(weapon->getPixelColour(2, 2));
	
	Scyjl15Engine* scyjl15Engine = dynamic_cast<Scyjl15Engine*>(baseEngine);
	edgePoints = scyjl15Engine->getEdgePointsByName("Warrior");
}

Hero::~Hero()
{
	printf("Hero Deleted!\n");
}

void Hero::setShield(int value)
{
	shield = value;
}

int Hero::getShield()
{
	return shield;
}

void Hero::setEnerge(int value)
{
	energe = value;
}

int Hero::getEnerge()
{
	return energe;
}

int Hero::getMaximumShield()
{
	return maximumShield;
}

int Hero::getMaximumHP()
{
	return maximumHP;
}

int Hero::getMaximumEnerge()
{
	return maximumEnerge;
}

void Hero::virtDraw()
{
	if (isVisible())
	{
		image.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
	}
}

void Hero::virtDoUpdate(int iCurrentTime)
{
	if (isVisible())
	{
		autoRecover(iCurrentTime);

		// Change position by pressing the w a s d keys on keyboard
		// w - go up, a - go left, d -go right, s - go down;
		if (getEngine()->isKeyPressed(SDLK_w) && m_iCurrentScreenY >= 150)
			m_iCurrentScreenY -= 3;
		if (getEngine()->isKeyPressed(SDLK_a) && m_iCurrentScreenX >= 5)
			m_iCurrentScreenX -= 3;
		if (getEngine()->isKeyPressed(SDLK_d) && m_iCurrentScreenX <= 1200)
			m_iCurrentScreenX += 3;
		if (getEngine()->isKeyPressed(SDLK_s) && m_iCurrentScreenY <= 650)
			m_iCurrentScreenY += 3;

		DisplayableObject* displable;
		getEngine()->bookmarkSetToLast();
		int lastIndex = getEngine()->bookmarkGetCurrentIndex();
		for (int i = 0; i <= lastIndex; i++)
		{
			displable = getEngine()->getDisplayableObject(i);
			// find the object itself or null ptr
			if (displable == this || displable == nullptr) {
				continue;
			}
			Bullet* bullet = dynamic_cast<Bullet*>(displable);
			// find the enemy's bullet
			if (bullet != nullptr && bullet->getBulletID() == 1)
			{
				if (CollisionUtil::pixelPerfectDetection(this, bullet))
				{
					beHit(bullet->getDamage());
					bullet->deleteBullet();
					continue;
				}
			}
		}
		getEngine()->redrawDisplay();
	}
}

MappableMaskImage* Hero::getWeapon()
{
	return weapon;
}

void Hero::setWeapon(MappableMaskImage* object)
{
	weapon = object;
}

ImagePixelMappingRotate* Hero::getRotator()
{
	return &rotator;
}

/*
* make the weapon followed the hero
*/
void Hero::setWeaponFollowed()
{
	weapon->setPosition(getXCentre() - 10, getYCentre() - 10);
}


void Hero::openFire(int targetX, int targetY)
{
	// consumption of firing a bullet
	int consumption = 2;
	// hero can only open the fire when energy is positive
	if (energe >= consumption)
	{
		int initialXPosition = weapon->getDrawingRegionRight() - 15;
		int initialYPosition = weapon->getYCentre() - 15;
		HeroBullet* bullet = new HeroBullet
		(getEngine(), initialXPosition, initialYPosition, 19, 19, "images/weapons/hero_bullet.png");
		getEngine()->appendObjectToArray(bullet);

		double opposite = targetY - initialYPosition;
		double adjacent = targetX - initialXPosition;
		double hypotenuse = sqrt(opposite * opposite + adjacent * adjacent);

		bullet->setXCos(adjacent / hypotenuse);
		bullet->setYSin(opposite / hypotenuse);

		energe -= consumption;
		Scyjl15Engine::playMusic("Bullet");
	}
}

void Hero::beHit(int damage)
{
	if (damage <= shield)
	{
		shield -= damage;
	}
	else {
		int deltaValue = damage - shield;
		shield = 0;
		hp -= deltaValue;
	}
}

void Hero::autoRecover(int currentTime)
{
	if (shield < maximumShield && (currentTime - lastRecover) > recoverInterval)
	{
		shield += 1;
		lastRecover = currentTime;
	}
}

Hero* Hero::copyHero()
{
	Hero* heroCopy = new Hero(getEngine());
	heroCopy->setEnerge(energe);
	heroCopy->setHP(hp);
	return heroCopy;
}


