#include "header.h"
#include "Scyjl15Engine.h"
#include "Behemoth.h"
#include "GoblinBullet.h"

Behemoth::Behemoth(BaseEngine* baseEngine, int screenX, int screenY
    , int width, int height) : Enemy(baseEngine, screenX, screenY, width, height, "images/characters/Behemoth.png")
{
	previousFireTime = rand() % 2000;
	strcpy(type, "Behemoth");
	hp = 15;
	speed = 1;
	// colding time is 0.8s
	coldingTime = 800;
	// load the edge points of Behemoth
	Scyjl15Engine* scyjl15Engine = dynamic_cast<Scyjl15Engine*>(baseEngine);
	edgePoints = scyjl15Engine->getEdgePointsByName("Behemoth");
	reward = 15;
}

Behemoth::~Behemoth()
{
	delete selection;
	selection = nullptr;
}

void Behemoth::destroyCharacter()
{
	getEngine()->drawableObjectsChanged();
	getEngine()->removeDisplayableObject(this);

	delete this;
}

void Behemoth::openFire(int targetX, int targetY)
{
	int sourceX = getXCentre();
	int sourceY = getYCentre();

	GoblinBullet* bullet = new GoblinBullet
	(getEngine(), sourceX, sourceY, 22, 22);
	getEngine()->appendObjectToArray(bullet);
	double radian = -RadianUtil::getRelativeRadian(sourceX, sourceY, targetX, targetY);
	bullet->setXCos(cos(radian));
	bullet->setYSin(sin(radian));
	

}

void Behemoth::virtDraw()
{
	if (isVisible())
	{
		image.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
	}
}
