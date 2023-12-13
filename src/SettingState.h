#pragma once
#include "State.h"
#include "FileUtils.h"
#include "DataPair.h"
class SettingState :
    public State
{
private:
	char playerName[100];
	int inputPointer;
	map<string, string>  gameSettings;
	vector<DataPair<string, int>*> scoreList;
	Font* regularFont;
	Font* caveatFont;
public:
    SettingState(BaseEngine* engine);
	~SettingState();
	void handleSetupBackgroundBuffer() override;
	void handleMouseDown(int iButton, int iX, int iY) override;
	int handleInitialiseObjects() override;
	bool checkReturnButton(int x, int y);
	void handleDrawStringOnTop();
	void handleKeyDown(int iKeyCode) override;
	bool checkSaveButton(int x, int y);
	bool checkPlayButton(int x, int y);
	bool checkMuteButton(int x, int y);
};

