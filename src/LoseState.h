#pragma once

#include "State.h"
#include "StartState.h"
class LoseState :
    public State
{
private:
    Font* caveatFont;
    int score;
public:
    LoseState(BaseEngine* engine, int score);
    ~LoseState();
    void handleSetupBackgroundBuffer() override;
    void handleMouseDown(int iButton, int iX, int iY) override;
    int handleInitialiseObjects() override;
    void handleDrawStringOnTop() override;
    bool checkHomeButton(int x, int y);
    void setScore(int value);
};

