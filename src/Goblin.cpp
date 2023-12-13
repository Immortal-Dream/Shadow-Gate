#include "header.h"
#include "Goblin.h"
#include "Scyjl15Engine.h"
#include "GoblinBullet.h"

Goblin::Goblin(BaseEngine* baseEngine, int screenX, int screenY, int width, int height)
	: Enemy(baseEngine, screenX, screenY, width, height, "images/characters/Goblin.png")
{
	previousFireTime = rand() % 2000;
	strcpy(type, "Goblin");
	hp = 8;
	speed = 4;
	// colding time is 4s
	coldingTime = 4000;
	// load the edge points of Goblin
	Scyjl15Engine* scyjl15Engine = dynamic_cast<Scyjl15Engine*>(baseEngine);
	edgePoints = scyjl15Engine->getEdgePointsByName("Goblin");
	reward = 10;
}

Goblin::~Goblin()
{
	delete selection;
	selection = nullptr;
}

void Goblin::destroyCharacter()
{
	getEngine()->drawableObjectsChanged();
	getEngine()->removeDisplayableObject(this);
	delete this;
}

void Goblin::openFire(int targetX, int targetY)
{
	int sourceX = getXCentre();
	int sourceY = getYCentre();
	GoblinBullet* bullet = new GoblinBullet
	(getEngine(), sourceX, sourceY, 21, 21);
	getEngine()->appendObjectToArray(bullet);
	double radian = -RadianUtil::getRelativeRadian(sourceX, sourceY, targetX, targetY);
	bullet->setXCos(cos(radian));
	bullet->setYSin(sin(radian));
}

void Goblin::virtDraw()
{
	if (isVisible())
	{
		image.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
	}
}
