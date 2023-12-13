#include "header.h"
#include "Wizard.h"
#include "Scyjl15Engine.h"
#include "FireBullet.h"
#include "BossBullet.h"
Wizard::Wizard(BaseEngine* baseEngine, int screenX, int screenY, int width, int height)
	: Enemy(baseEngine, screenX, screenY, width, height, "images/characters/Wizard.png")
{
	previousFireTime = rand() % 2000;
	strcpy(type, "Wizard");
	hp = 45;
	speed = 2;
	// colding time is 2.5s
	coldingTime = 2500;
	// load the edge points of Behemoth
	Scyjl15Engine* scyjl15Engine = dynamic_cast<Scyjl15Engine*>(baseEngine);
	edgePoints = scyjl15Engine->getEdgePointsByName("Wizard");
	reward = 91;

	// previous skill time is set to be 5s
	previousSkillTime = 5000;
	// skill cooling time is 10s
	skillColdingTime = 10000;
}

Wizard::~Wizard()
{
	delete selection;
	selection = nullptr;
}


void Wizard::destroyCharacter()
{
	getEngine()->drawableObjectsChanged();
	getEngine()->removeDisplayableObject(this);
	delete this;
}

void Wizard::openFire(int targetX, int targetY)
{
	int sourceX = getXCentre();
	int sourceY = getYCentre();
    // create 3 bullets at the same time in three directions
	BossBullet* bulletMiddle = new BossBullet
	(getEngine(), sourceX, sourceY, 22, 22);
	getEngine()->appendObjectToArray(bulletMiddle);
	double radian = -RadianUtil::getRelativeRadian(sourceX, sourceY, targetX, targetY);
    bulletMiddle->setXCos(cos(radian));
    bulletMiddle->setYSin(sin(radian));

    BossBullet* bulletUp = new BossBullet
    (getEngine(), sourceX, sourceY, 22, 22);
    getEngine()->appendObjectToArray(bulletUp);
    radian += M_PI / 6;
    bulletUp->setXCos(cos(radian));
    bulletUp->setYSin(sin(radian));

    BossBullet* bulletDown = new BossBullet
    (getEngine(), sourceX, sourceY, 22, 22);
    radian -= M_PI / 3;
    getEngine()->appendObjectToArray(bulletDown);
    bulletDown->setXCos(cos(radian));
    bulletDown->setYSin(sin(radian));
}

/*
* Wizard uses the skill
*/
void Wizard::useSkill(int targetX, int targetY)
{
	int sourceX = getXCentre();
	int sourceY = getYCentre();
	// create a fire ball
	FireBullet* fireBall = new FireBullet
	(getEngine(), sourceX, sourceY, 45, 50);
	getEngine()->appendObjectToArray(fireBall);
	double radian = -RadianUtil::getRelativeRadian(sourceX, sourceY, targetX, targetY);
	fireBall->setXCos(cos(radian));
	fireBall->setYSin(sin(radian));
}

void Wizard::virtDraw()
{
	if (isVisible())
	{
		image.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
	}
}

void Wizard::fireWithColdingTime(long long currentTime, int x, int y)
{
	if ((currentTime - previousFireTime) > coldingTime)
	{
		openFire(x, y);
		previousFireTime = currentTime;
	}
	if ((currentTime - previousSkillTime) > skillColdingTime)
	{
		useSkill(x, y);
		previousSkillTime = currentTime;
	}
}
