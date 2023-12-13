#pragma once
#include "Enemy.h"
#include "Orc.h"
#include "OrcBullet.h"
#include "RadianUtil.h"
/*
* junior monster
*/
class Orc :
    public Enemy
{
public:
    Orc(BaseEngine* baseEngine, int screenX, int screenY
        , int width, int height);

    virtual ~Orc();

    void destroyCharacter();
    void openFire(int targetX, int targetY) override;
    void virtDraw();
};

