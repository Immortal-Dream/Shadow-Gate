#pragma once
#include "Bullet.h"
class GoblinBullet :
    public Bullet
{
public:
    GoblinBullet(BaseEngine* baseEngine, int screenX, int screenY
        , int width, int height);

    void virtDraw() override;
    void virtDoUpdate(int iCurrentTime) override;
};

