#pragma once
#include "State.h"
#include "ScalingUtils.h"
//#include "ExampleFilterPointClasses.h" 

class MapState :
    public State
{
private:
    ZoomingFilter m_filterScaling;
    ZoomTranslator m_filterTranslation;
public:
    MapState(BaseEngine* engine);
    ~MapState();
    void handleSetupBackgroundBuffer() override;
    void handleMainLoopDoBeforeUpdate() override;
    void handleCopyAllBackgroundBuffer();
    int handleInitialiseObjects() override;
    void handleKeyDown(int keyCode) override;
    void handleMouseDown(int iButton, int iX, int iY);
    void handleMouseWheel(int x, int y, int which, int timestamp) override;
};
