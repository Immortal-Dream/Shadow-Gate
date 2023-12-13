#pragma once
#include "Enemy.h"
class Behemoth :
    public Enemy
{
public:
    Behemoth(BaseEngine* baseEngine, int screenX, int screenY
        , int width, int height);

    virtual ~Behemoth();

    void destroyCharacter();
    void openFire(int targetX, int targetY) override;
    void virtDraw();
};

