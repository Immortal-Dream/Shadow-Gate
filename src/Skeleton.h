#pragma once
#include "Enemy.h"
#include "OrcBullet.h"
#include "RadianUtil.h"
class Skeleton :
    public Enemy
{
public:
    Skeleton(BaseEngine* baseEngine, int screenX, int screenY
        , int width, int height);

    virtual ~Skeleton();
    void destroyCharacter();
    void openFire(int targetX, int targetY) override;
    void virtDraw();
};

