#pragma once
#include "RunningState.h"
#include "PoisonTile.h"

class Episode2State :
    public RunningState
{
private:
    PoisonTile* poisonTile;
public:
    Episode2State(BaseEngine* engine, Hero* hero);
    ~Episode2State();
    void handleSetupBackgroundBuffer() override;
    void handleMouseDown(int iButton, int iX, int iY);
    int handleInitialiseObjects() override;
    void handleDrawStringOnTop() override;
    void handleKeyDown(int keyCode) override;
    void handleCopyAllBackgroundBuffer() override;
    void handleMainLoopDoBeforeUpdate() override;
    void readDialogFromFile() override;
    void checkPoison();
    PoisonTile* getPoisonTile();
};

