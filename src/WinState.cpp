#include "header.h"
#include "State.h"
#include "WinState.h"
#include "Scyjl15Engine.h"

WinState::WinState(BaseEngine* engine)
	:State(engine)
{
	Scyjl15Engine::playMusic("Victory");
	FileUtils::saveScore(500);
}


WinState::~WinState()
{
}

void WinState::handleSetupBackgroundBuffer()
{
	SimpleImage menuBackground = ImageManager::loadImage("images/backgrounds/Win.png", true);
	menuBackground.renderImage(m_Engine->getBackgroundSurface(), 0, 0, 0, 0
		, menuBackground.getWidth(), menuBackground.getHeight());

	SimpleImage homeButton = ImageManager::loadImage("images/elements/Home.png", true);
	homeButton.renderImageWithMask(m_Engine->getBackgroundSurface(), 0, 0, 12, 12
		, homeButton.getWidth(), homeButton.getHeight());
}

void WinState::handleMouseDown(int iButton, int iX, int iY)
{
	// down cast BaseEngine to Scyjl15Engine
	Scyjl15Engine* scyjl15Engine = dynamic_cast<Scyjl15Engine*>(m_Engine);
	// click the home button
	if (checkHomeButton(iX, iY))
	{
		State* start = new StartState(m_Engine);
		scyjl15Engine->m_Context->changeState(start, m_Engine);
	}
}

int WinState::handleInitialiseObjects()
{
	m_Engine->drawableObjectsChanged();
	m_Engine->destroyOldObjects(true);
	return 0;
}

bool WinState::checkHomeButton(int x, int y)
{
	return checkClick(x, y, 12, 102, 12, 102);
}
