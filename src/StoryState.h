#pragma once
#include "State.h"
class StoryState : public State
{
private:
	bool isScrolling;
	int scrollingSpeed;
protected:
	int offset;
public:
	StoryState(BaseEngine* engine);
	~StoryState();
	void handleSetupBackgroundBuffer() override;
	void handleMainLoopDoBeforeUpdate() override;
	void handleCopyAllBackgroundBuffer();
	// method to handle the mouse down listen;er in Engine class
	void handleMouseDown(int iButton, int iX, int iY);

	bool checkNewGameButton(int x, int y);
	bool checkContinueButton(int x, int y);
	void handleKeyDown(int keyCode) override;
};

