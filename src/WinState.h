#pragma once
#include "State.h"
class WinState :
    public State
{
public:
    WinState(BaseEngine* engine);
    ~WinState();
    void handleSetupBackgroundBuffer() override;
    void handleMouseDown(int iButton, int iX, int iY) override;
    int handleInitialiseObjects() override;
    bool checkHomeButton(int x, int y);
};

