#pragma once
#include "Bullet.h"
class BossBullet :
    public Bullet
{
public:
    BossBullet(BaseEngine* baseEngine, int screenX, int screenY
        , int width, int height);

    void virtDraw() override;
    void virtDoUpdate(int iCurrentTime) override;
};

