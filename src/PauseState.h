#pragma once
#include "RunningState.h"
#include "StartState.h"
#include "SerializationUtil.h"
/*
* pause state during the game
*/
class PauseState :
    public State
{
private:
    RunningState* previousState;
public:
    PauseState(BaseEngine* engine, RunningState* formerState);
    ~PauseState();
    void handleSetupBackgroundBuffer() override;
    void handleKeyDown(int keyCode) override;
    void handleMouseDown(int iButton, int iX, int iY);
    int handleInitialiseObjects() override;
    bool checkReturnButton(int x, int y);
};

