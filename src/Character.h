#pragma once
#include "DisplayableObject.h"
#include "BaseEngine.h"
#include "ImageManager.h"
#include "DataPair.h"
#include "FileUtils.h"
#include <vector>


using namespace std;
/*
    this class is the intermediate class of all game characters
    such as hero, monsters and wizard.
*/
class Character :
    public DisplayableObject
{
protected:
    // previous time is used to control the time interval
    int previousTime;
    // every character has hp value, if hp reaches 0, the character will dead.
    int hp;
    SimpleImage image;
    // move speed of the character
    int speed;
    // The coordinates of the character's edge points are determined relative to the top-left corner.
    vector<DataPair<int, int>*> edgePoints;
    // previous fire time, in milliseconds
    long long previousFireTime;
    // coldingTime between two consecutive fire, in milliseconds
    int coldingTime;
public:
    Character(BaseEngine* baseEngine, int screenX, int screenY
        , int width, int height, std::string url);
        
    void setHP(int value);
    int getHP();

    void setSpeed(int speedValue);
    int getSpeed();
    virtual void virtDraw();
    virtual void virtDoUpdate(int iCurrentTime) override;
    virtual void openFire(int x, int y);
    virtual void destroyCharacter();
    virtual void beHit(int damage);
    long long getPreviousFireTime();
    void setPreviousFireTime(long long time);
    double operator-(DisplayableObject& object);
    vector<DataPair<int, int>*> getEdgePoints();
    virtual void fireWithColdingTime(long long currentTime, int x, int y);
};