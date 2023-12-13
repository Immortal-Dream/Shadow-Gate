#pragma once
#include "Enemy.h"
class Wizard :
    public Enemy
{
protected:
    // previous skill time, in milliseconds
    long long previousSkillTime;
    // The colding time interval for wizard to use skills
    int skillColdingTime;
public:
    Wizard(BaseEngine* baseEngine, int screenX, int screenY
        , int width, int height);

    virtual ~Wizard();
    void destroyCharacter();
    void openFire(int targetX, int targetY) override;
    void useSkill(int targetX, int targetY);
    void virtDraw();
    void fireWithColdingTime(long long currentTime, int x, int y) override;
    
};

