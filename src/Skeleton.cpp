#include "header.h"
#include "Scyjl15Engine.h"
#include "Skeleton.h"

Skeleton::Skeleton(BaseEngine* baseEngine, int screenX, int screenY, int width, int height)
	: Enemy(baseEngine, screenX, screenY, width, height, "images/characters/Skeleton.png")
{
	previousFireTime = rand() % 2000;
	strcpy(type, "Orc");
	hp = 5;
	speed = 3;
	// colding time is 2s
	coldingTime = 2000;
	// load the edge points of Orc
	Scyjl15Engine* scyjl15Engine = dynamic_cast<Scyjl15Engine*>(baseEngine);
	edgePoints = scyjl15Engine->getEdgePointsByName("Skeleton");
	reward = 8;
}

Skeleton::~Skeleton()
{
	delete selection;
}

void Skeleton::destroyCharacter()
{
	getEngine()->drawableObjectsChanged();
	getEngine()->removeDisplayableObject(this);
	delete this;
}

void Skeleton::openFire(int targetX, int targetY)
{
	int sourceX = getXCentre();
	int sourceY = getYCentre();
	OrcBullet* bullet = new OrcBullet
	(getEngine(), sourceX, sourceY, 21, 21);
	// set the damage to 2
	bullet->setDamage(2);
	getEngine()->appendObjectToArray(bullet);
	double radian = -RadianUtil::getRelativeRadian(sourceX, sourceY, targetX, targetY);
	bullet->setXCos(cos(radian));
	bullet->setYSin(sin(radian));
}

void Skeleton::virtDraw()
{
	if (isVisible())
	{
		image.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
	}
}
