#include "header.h"
#include "Scyjl15Engine.h"
#include "Orc.h"

Orc::Orc(BaseEngine* baseEngine, int screenX, int screenY, int width, int height)
	: Enemy(baseEngine, screenX, screenY, width, height, "images/characters/Orc.png")
{
	previousFireTime = rand() % 2000;
	strcpy(type, "Orc");
	hp = 4;
	speed = 2;
	// colding time is 2.5s
	coldingTime = 2500;
	// load the edge points of Orc
	Scyjl15Engine* scyjl15Engine = dynamic_cast<Scyjl15Engine*>(baseEngine);
	edgePoints = scyjl15Engine->getEdgePointsByName("Orc");
	reward = 5;
}

Orc::~Orc()
{
	delete selection;
	selection = nullptr;
}

void Orc::destroyCharacter()
{
	getEngine()->drawableObjectsChanged();
	getEngine()->removeDisplayableObject(this);
	delete this;
}

void Orc::openFire(int targetX, int targetY)
{
	int sourceX = getXCentre();
	int sourceY = getYCentre();
	OrcBullet* bullet = new OrcBullet
	(getEngine(), sourceX, sourceY, 21, 21);
	getEngine()->appendObjectToArray(bullet);
	double radian = -RadianUtil::getRelativeRadian(sourceX, sourceY, targetX, targetY);
	bullet->setXCos(cos(radian));
	bullet->setYSin(sin(radian));
}

void Orc::virtDraw()
{
	if (isVisible())
	{
		image.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
	}
}
