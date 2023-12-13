#pragma once
#include "Bullet.h"
class FireBullet :
    public Bullet
{
private:
    int imageID;
    SimpleImage fireImages[6];
    long long previousSwitchTime;
    int switchInterval;
public:
    FireBullet(BaseEngine* baseEngine, int screenX, int screenY
        , int width, int height);
    void virtDraw() override;
    void virtDoUpdate(int iCurrentTime) override;
};

