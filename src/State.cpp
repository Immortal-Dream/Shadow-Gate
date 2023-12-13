#include "header.h"
#include "State.h"



State::State(BaseEngine* engine)
{
	m_Engine = engine;
}

State::~State()
{
}

void State::handleSetupBackgroundBuffer() {

}
void  State::handleMouseDown(int iButton, int iX, int iY)
{

}

int State::handleInitialiseObjects()
{
	return 0;
}

void State::handleDrawStringOnTop()
{
}

bool State::checkClick(int clickX, int clickY, int xMin, int xMax, int yMin, int yMax)
{
	return (clickX >= xMin && clickX <= xMax)
		&& (clickY >= yMin && clickY <= yMax);
	return false;
}




void State::handleKeyUp(int iKeyCode)
{
	
}


void State::handleKeyDown(int iKeyCode)
{
	
}

void State::setDeletMode(int mode)
{
	deleteMode = mode;
}

int State::getDeleteMode()
{
	return deleteMode;
}


void State::handleMainLoopDoBeforeUpdate()
{

	m_Engine->redrawDisplay();

}


void State::handleCopyAllBackgroundBuffer()
{
	m_Engine->getForegroundSurface()->copyRectangleFrom
	(m_Engine->getBackgroundSurface(), 0, 0, m_Engine->getWindowWidth(), m_Engine->getWindowHeight(), 0, 0);

}




void State::handleMouseWheel(int x, int y, int which, int timestamp)
{
	
}
