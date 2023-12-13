#pragma once
#include "RunningState.h"
/*
ontext class defines and handle the current state for client in  
	State Design Pattern
*/
class Context
{
private:
	State* m_State;
public:
	Context();
	Context(BaseEngine* engine);
	Context(State* state);
	void requestSetupBackgroundBuffer();
	void requestMouseDown(int iButton, int iX, int iY);
	void requestInitialiseObjects();
	void requestDrawStringOnTop();
	void continueState(State* newState, BaseEngine* engine);
	void changeState(State* newState, BaseEngine* engine);
	void requestKeyUp(int iKeyCode);
	void requestKeyDown(int iKeyCode);
	void deleteState();
	void requestMainLoopDoBeforeUpdate();
	void requestCopyAllBackgroundBuffer();
	void pause(State* pauseState, BaseEngine* engine);
	void restart(RunningState* previousState, BaseEngine* engine);
	void requestMouseWheel(int x, int y, int which, int timestamp);
};

