#pragma once
#include "header.h"
#include "RunningState.h"
#include "memory"
#include "PauseState.h"
#include "Scyjl15Engine.h"


/*
    State of episode 1 of the game
*/
class Episode1State :
    public RunningState
{
public:
    Episode1State(BaseEngine* engine);
    
    void handleSetupBackgroundBuffer() override;
    void handleMouseDown(int iButton, int iX, int iY);
    int handleInitialiseObjects() override;
    void handleDrawStringOnTop() override;
    void handleKeyDown(int keyCode) override;
    void handleCopyAllBackgroundBuffer() override;
    void handleMainLoopDoBeforeUpdate() override;
    void readDialogFromFile() override;
    
};

