#pragma once
#include "Bullet.h"
#include "BaseEngine.h"
#include "ImageManager.h"
class OrcBullet :
    public Bullet
{
public:
    OrcBullet(BaseEngine* baseEngine, int screenX, int screenY
        , int width, int height);
    void virtDraw() override;
    void virtDoUpdate(int iCurrentTime) override;

};

