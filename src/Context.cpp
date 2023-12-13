#include "header.h"
#include "Context.h"
void Context::requestSetupBackgroundBuffer() {
	m_State->handleSetupBackgroundBuffer();
}

void Context::requestMouseDown(int iButton, int iX, int iY) {
	m_State->handleMouseDown(iButton, iX, iY);
}

void Context::requestInitialiseObjects() {
	m_State->handleInitialiseObjects();
}
void Context::requestDrawStringOnTop()
{
	m_State->handleDrawStringOnTop();
}
// continue last state
void Context::continueState(State* newState, BaseEngine* engine)
{
	deleteState();
	m_State = newState;
	engine->lockBackgroundForDrawing();
	requestSetupBackgroundBuffer();
	engine->unlockBackgroundForDrawing();
}
// change the current state
void Context::changeState(State* newState, BaseEngine* engine)
{
	deleteState();
	m_State = newState;
	engine->lockBackgroundForDrawing();
	requestSetupBackgroundBuffer();
	engine->unlockBackgroundForDrawing();
	requestInitialiseObjects();
	engine->redrawDisplay();
}

void Context::requestKeyUp(int iKeyCode)
{
	m_State->handleKeyUp(iKeyCode);

}


void Context::requestKeyDown(int iKeyCode)
{
	m_State->handleKeyDown(iKeyCode);
}

void Context::deleteState()
{
	if (m_State != nullptr)
	{
		delete m_State;
		m_State = nullptr;
	}
}

void Context::requestMainLoopDoBeforeUpdate()
{
	m_State->handleMainLoopDoBeforeUpdate();
}


void Context::requestCopyAllBackgroundBuffer()
{
	m_State->handleCopyAllBackgroundBuffer();
	
}
/*
* switch to pause state
*/
void Context::pause(State* newState, BaseEngine* engine)
{
	m_State = newState;
	engine->lockBackgroundForDrawing();
	requestSetupBackgroundBuffer();
	engine->unlockBackgroundForDrawing();
	requestInitialiseObjects();
	engine->redrawDisplay();

}
void Context::restart(RunningState* previousState, BaseEngine* engine)
{
	m_State->setDeletMode(1);
	delete m_State;
	m_State = previousState;
	engine->lockBackgroundForDrawing();
	requestSetupBackgroundBuffer();
	engine->unlockBackgroundForDrawing();
	engine->setAllObjectsVisible(true);
	engine->redrawDisplay();
}
Context::Context() 
{
	m_State = NULL;
}
Context::Context(BaseEngine* engine) 
{
	m_State = new State(engine);
}
Context::Context(State* state)
{
	m_State = state;
}




void Context::requestMouseWheel(int x, int y, int which, int timestamp)
{
	m_State->handleMouseWheel(x, y, which,timestamp);
}
