#include "header.h"
#include "PauseState.h"
#include "Scyjl15Engine.h"
PauseState::PauseState(BaseEngine* engine, RunningState* formerState)
	:State(engine), previousState(formerState)
{
}

PauseState::~PauseState()
{
	if (getDeleteMode() == 0)
	{
		delete previousState;
	}
}

void PauseState::handleSetupBackgroundBuffer()
{
	SimpleImage gameBackground = ImageManager::loadImage("images/backgrounds/Pause.png", true);
	gameBackground.renderImage(m_Engine->getBackgroundSurface(), 0, 0, 0, 0
		, 1300, 800);
}

void PauseState::handleKeyDown(int keyCode)
{
	// down cast BaseEngine to Scyjl15Engine
	Scyjl15Engine* scyjl15Engine = dynamic_cast<Scyjl15Engine*>(m_Engine);

	/*
	* if user press space key, the game will restart
	*/
	if (keyCode == SDLK_SPACE)
	{
		scyjl15Engine->m_Context->restart(previousState, m_Engine);
	}
	/*
	* if player press s key, current game status will be saved to file
	*/
	if (keyCode == SDLK_s)
	{
		SerializationUtil serialization;
		serialization.serialize(previousState, m_Engine);
		printf("State Saved\n");
	}
}

void PauseState::handleMouseDown(int iButton, int iX, int iY)
{
	printf("Pause:( %d , %d )\n", iX, iY);
	if (checkReturnButton(iX,iY))
	{
		// down cast BaseEngine to Scyjl15Engine
		Scyjl15Engine* scyjl15Engine = dynamic_cast<Scyjl15Engine*>(m_Engine);
		State* start = new StartState(m_Engine);
		scyjl15Engine->m_Context->changeState(start, m_Engine);
	}
}

int PauseState::handleInitialiseObjects()
{
	// set all objects to be invisible
	m_Engine->setAllObjectsVisible(false);
	return 0;
}

bool PauseState::checkReturnButton(int x, int y)
{
	return checkClick(x,y,53,215,45,81);
}
