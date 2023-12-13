#pragma once
#include "Character.h"
#include "BaseEngine.h"
#include "ImageManager.h"
#include "RouletteWheelSelection.h"
#include "RadianUtil.h"
#include "HeroBullet.h"
#include "Hero.h"
#include <memory>
#include "CollisionUtil.h"

/*
* Parent classes of all enemy units
*/
class Enemy :
    public Character
{
protected:
    /*
    * Enemy's type
    */
    char type[30];
    RouletteWheelSelection* selection;
    /*
    * direction of moving
    */
    double direction = 0;
    // reward of killing this enemy
    int reward;
public:

    Enemy(BaseEngine* baseEngine, int screenX, int screenY
        , int width, int height, std::string url)
        : Character(baseEngine, screenX, screenY, width, height, url)
    {

        m_iCurrentScreenX = screenX;
        m_iCurrentScreenY = screenY;
        m_iDrawWidth = width;
        m_iDrawHeight = height;
        strcpy(type, "Enemy");
        speed = 5;
        reward = 5;
        // use smart pointer to manage selection object inside Enemy
        selection = new RouletteWheelSelection();
    }
    string getType();
    virtual void virtDraw();
    virtual void virtDoUpdate(int iCurrentTime) override;
    virtual void openFire(int x, int y);
    virtual void move(double radian);
    virtual void escape(double radian);
    virtual void destroyCharacter();
    virtual void openFire();
    void setReward(int value);
    int getReward();
};

