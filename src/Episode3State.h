#pragma once
#include "RunningState.h"
class Episode3State :
    public RunningState
{
public:
    Episode3State(BaseEngine* engine, Hero* hero);
    ~Episode3State();
    void handleSetupBackgroundBuffer() override;
    void handleMouseDown(int iButton, int iX, int iY);
    int handleInitialiseObjects() override;
    void handleDrawStringOnTop() override;
    void handleKeyDown(int keyCode) override;
    void handleCopyAllBackgroundBuffer() override;
    void handleMainLoopDoBeforeUpdate() override;
    void readDialogFromFile() override;
};

