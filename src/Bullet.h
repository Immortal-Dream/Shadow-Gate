#pragma once
#include "DisplayableObject.h"
#include "BaseEngine.h"
#include "ImageManager.h"
class Bullet :
    public DisplayableObject
{
protected:
    SimpleImage image;
    /*
    * damage of this bullet
    */
    int damage;
    /*
    * bullet id
    * 0 means hero's bullet; 1 means monster's bullet
    */
    int bulletID;
    /*
    * speed of the bullet
    */
    int speed;
    /*
    * value between 0 and 1
    * cos value of the bullet moving in x coordinate
    */
    double xCos;
    /*
    * value between 0 and 1
    * sin value of the bullet moving in x coordinate
    */
    double ySin;
    /*
    * Bullet's name
    */
    char bulletName[30];
public:
    Bullet(BaseEngine* baseEngine, int screenX, int screenY
        , int width, int height, std::string url);
        
    virtual void setDamage(int power);
    virtual void setBulletID(int id);
    virtual void setSpeed(int value);
    virtual void setXCos(double cosValue);
    virtual void setYSin(double sinValue);

    virtual int getDamage();
    virtual int getBulletID();
    virtual int getSpeed();
    virtual double getXCos();
    virtual double getYSin();

    virtual void virtDraw();
    virtual void virtDoUpdate(int iCurrentTime) override;
    virtual void destoryBullet();
    virtual bool isOutOfScreen();
    virtual void deleteBullet();
    void autoMove();
    char* getBulletName();
};

