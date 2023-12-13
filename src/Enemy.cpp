#include "header.h"
#include "Enemy.h"


string Enemy::getType()
{
    return type;
}

void Enemy::virtDraw()
{
}

void Enemy::virtDoUpdate(int iCurrentTime)
{

    if (isVisible())
    {
        // traverse all displable objects 
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
            Enemy* enemy = dynamic_cast<Enemy*>(displable);
            // this object is an enemy object too
            if (enemy != nullptr)
            {
                // To prevent enemies from becoming crowded, we decrease score of that area and
                // reduce the probability of moving to that area.
                int area = RadianUtil::getArea
                (this->getXCentre(), this->getYCentre(), displable->getXCentre(), displable->getYCentre());
                selection->decreaseScore(area);
            }

            HeroBullet* heroBullet = dynamic_cast<HeroBullet*>(displable);
            // If the bullets belong to the hero, the score of that area is decreased to prevent the 
            // AI from approaching the bullets.
            if (heroBullet != nullptr)
            {

                double relativeRadian = RadianUtil::getRelativeRadian
                (this->getXCentre(), this->getYCentre(), displable->getXCentre(), displable->getYCentre());
                int area = RadianUtil::getArea(relativeRadian);
                double distance = this->operator-(*displable);
                // if the distance between monster is smaller than 150
                // monster will escape the bullets in another direction
                if (distance < 150)
                {
                    if (CollisionUtil::pixelPerfectDetection((Character*)this, heroBullet))
                    {
                        this->beHit(heroBullet->getDamage());
                        heroBullet->deleteBullet();
                        continue;
                    }
                    escape(relativeRadian);
                }
                selection->decreaseScore(area);
            }
            // get close to the hero
            Hero* hero = dynamic_cast<Hero*>(displable);
            if (hero != nullptr) {
                // fire at hero's position
                fireWithColdingTime(iCurrentTime, hero->getXCentre(), hero->getYCentre());
                int area = RadianUtil::getArea
                (this->getXCentre(), this->getYCentre(), displable->getXCentre(), displable->getYCentre());
                selection->increaseScore(area);
            }
        }

        if ((iCurrentTime - previousTime) > 350)
        {
            // select the direction according to reinforcement learning
            direction = RadianUtil::convertDegreeToRadian(selection->selectDirection());
            previousTime = iCurrentTime;
            selection->resetScore();
        }
        // make movement
        move(direction);
    }
}

void Enemy::openFire(int x, int y)
{
}
/*
* move according to radian and speed
*/
void Enemy::move(double radian)
{
    double cosValue = cos(radian);
    double sinValue = sin(radian);
    // move positively
    if (cosValue > 0&& getDrawingRegionRight() <= 1200)
    {
        m_iCurrentScreenX += (int)(cosValue * speed);
    }
    else if (cosValue < 0 && getDrawingRegionLeft() >= 10)
    {
        m_iCurrentScreenX += (int)(cosValue * speed);
    }

    if (sinValue < 0 && getDrawingRegionTop() >= 120)
    {
        m_iCurrentScreenY += (int)(sinValue * speed);
    }
    else if (sinValue > 0 && getDrawingRegionBottom() <= 700)
    {
        m_iCurrentScreenY += (int)(sinValue * speed);
    }
    
}

/*
* escape algorithm to make monster hide from hero's bullet
* @parm radian the direction of the bullet
*/
void Enemy::escape(double radian)
{
    double newDirection = radian - (M_PI / 2);
    for (int i = 0; i < 2; i++)
    {
        move(newDirection);
    } 
}

void Enemy::destroyCharacter()
{
}

void Enemy::openFire()
{
}

void Enemy::setReward(int value)
{
    reward = value;
}

int Enemy::getReward()
{
    return reward;
}
