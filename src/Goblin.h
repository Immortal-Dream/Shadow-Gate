#pragma once
#include "Enemy.h"
class Goblin :
    public Enemy
{
public:
    Goblin(BaseEngine* baseEngine, int screenX, int screenY
        , int width, int height);

    virtual ~Goblin();

    void destroyCharacter();
    void openFire(int targetX, int targetY) override;
    void virtDraw();
};

