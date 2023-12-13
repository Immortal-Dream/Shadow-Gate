#pragma once
#include "Character.h"
#include "BaseEngine.h"
#include "ImageManager.h"
#include "MappableMaskImage.h"
#include "ImagePixelMapping.h"
#include "HeroBullet.h" 
#include "CollisionUtil.h"
class Hero :
    public Character
{
private:
    /*
    * hero has shild value, shield is similar to hp value but it can be recovered
    * automatically with time going by. HP cannot grows automatically. Player have to 
    * eat medicine to increase the hp value.
    * 
    */ 
    int shield;
    /*
    * hero need to consume the energe to use the weapon to fire the bullets
    */
    int energe;
    /*
    * maximum number of hp value
    */
    int maximumHP;
    /*
    * maximum number of shield value
    */
    int maximumShield;
    /*
    * maximum number of energe value
    */
    int maximumEnerge;
    /*
    * ImageObject pointer points to hero's weapon
    */
    MappableMaskImage* weapon;
    /*
    * rotator of the weapon
    */
    ImagePixelMappingRotate rotator;

    /*
    * last time of getting recover, in miliseconds
    * shield will recover automatically every interval 
    */
    int lastRecover;

    /*
    * recover colding time, in miliseconds
    */
    int recoverInterval;
public:
    Hero(BaseEngine* baseEngine);

    ~Hero();
    void setShield(int value);
    int getShield();
    void setEnerge(int value);
    int getEnerge();

    int getMaximumShield();
    int getMaximumHP();
    int getMaximumEnerge();
    void virtDraw() override;
    void virtDoUpdate(int iCurrentTime) override;
    MappableMaskImage* getWeapon();
    void setWeapon(MappableMaskImage* object);
    ImagePixelMappingRotate* getRotator();
    void setWeaponFollowed();
    void openFire(int targetX, int targetY) override;
    void beHit(int damage) override;
    void autoRecover(int currentTime);
    Hero* copyHero();
};

