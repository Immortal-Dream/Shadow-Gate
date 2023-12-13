#pragma once
#include "Bullet.h"
#include "BaseEngine.h"
#include "ImageManager.h"
class HeroBullet :
    public Bullet
{
public:
    HeroBullet(BaseEngine* baseEngine, int screenX, int screenY
        , int width, int height, std::string url);
        
    void virtDraw() override;
    void virtDoUpdate(int iCurrentTime) override;
    void destoryBullet() override;
};

