#pragma once
#include "BaseEngine.h"
using namespace std;
class State
{
private:
	int deleteMode = 0;
protected:
	BaseEngine* m_Engine;
public:
	State(BaseEngine* engine);
	virtual ~State();
	// method to handle the background buffer in engine
	virtual void handleSetupBackgroundBuffer();
	// method to handle the mouse down listen;er in Engine class
	virtual void handleMouseDown(int iButton, int iX, int iY);
	// method to handle initialising objects in Engine class
	virtual int handleInitialiseObjects();
	// method to handle wrting dynamic string on top of object
	virtual void handleDrawStringOnTop();
	virtual void handleKeyUp(int iKeyCode);
	virtual void handleKeyDown(int iKeyCode);
	void setDeletMode(int mode);
	int getDeleteMode();

	bool checkClick(int clickX, int clickY, int xMin, int xMax, int yMin, int yMax);

	virtual void handleMainLoopDoBeforeUpdate();
	virtual void handleCopyAllBackgroundBuffer();

	virtual void handleMouseWheel(int x, int y, int which, int timestamp);
};

