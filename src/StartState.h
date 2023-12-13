#pragma once
#include "State.h"
#include "FileUtils.h"
#include "TimeUtil.h"
class StartState : 
	public State
{
public:
	StartState(BaseEngine* engine);
	~StartState();
	void handleSetupBackgroundBuffer() override;
	void handleMouseDown(int iButton, int iX, int iY) override;
	int handleInitialiseObjects() override;
	void handleDrawStringOnTop() override;
	void handleMainLoopDoBeforeUpdate() override;
	bool checkBeginButton(int x, int y);
	bool checkExitButton(int x, int y);
	bool checkSettingButton(int x, int y);
	bool checkMapButton(int x, int y);
private:
	long long lastDisplayTime;
	int animationInterval = 100;
	map<string, string>  gameSettings;
	vector<DrawingSurface*> surfaceVector;
	int backgroundIndex;
	Font* caveatFont;
	DrawingSurface* previousSurface;
};