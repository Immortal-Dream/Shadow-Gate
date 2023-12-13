#include "header.h"
#include "Character.h"

/*
* set the hp value
*/
Character::Character(BaseEngine* baseEngine, int screenX, int screenY, int width, int height, std::string url)
	: DisplayableObject(baseEngine)
	, image(baseEngine->loadImage(url, false))
{
	previousFireTime = 0;
	coldingTime = 500;
	previousTime = 0;
	hp = 2;
	speed = 3;
	m_iCurrentScreenX = screenX;
	m_iCurrentScreenY = screenY;
	m_iDrawWidth = width;
	m_iDrawHeight = height;
}
void Character::setHP(int value)
{
	hp = value;
}
/*
* get hp value
*/
int Character::getHP()
{
	return hp;
}

void Character::setSpeed(int speedValue)
{
	speed = speedValue;
}

int Character::getSpeed()
{
	return speed;
}

void Character::virtDraw()
{
}

void Character::virtDoUpdate(int iCurrentTime)
{
}
/*
* character's attack function
*/
void Character::openFire(int x, int y)
{
}
/*
* delete the character
*/
void Character::destroyCharacter()
{

}
/*
* be hit by the bullet
*/
void Character::beHit(int damage)
{
	hp -= damage;
}

long long Character::getPreviousFireTime()
{
	return previousFireTime;
}

void Character::setPreviousFireTime(long long time)
{
	previousFireTime = time;
}

/*
* - operator is used to calculate the distance between this 
* Character's centre and the object's centre.
*/
double Character::operator-(DisplayableObject& object)
{
	return sqrt(pow(getXCentre()-object.getXCentre(), 2) + pow(getYCentre()-object.getYCentre(),2));
}

vector<DataPair<int, int>*> Character::getEdgePoints()
{
	return edgePoints;
}
/*
* reduce the fire rate with a limit of colding time
*/
void Character::fireWithColdingTime(long long currentTime, int x, int y)
{
	if ((currentTime - previousFireTime) > coldingTime)
	{
		openFire(x, y);
		previousFireTime = currentTime;
	}
}
