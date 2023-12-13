#include "header.h"
#include "LoseState.h"
#include "Scyjl15Engine.h"

LoseState::LoseState(BaseEngine* engine, int score):State(engine)
{
	this->score = score;
	Scyjl15Engine::playMusic("GameOver");
	caveatFont = m_Engine->getFont("resources/Caveat-SemiBold.ttf", 60);
	FileUtils::saveScore(score);
}

LoseState::~LoseState()
{
}

void LoseState::handleSetupBackgroundBuffer()
{
	SimpleImage menuBackground = ImageManager::loadImage("images/backgrounds/Lose.png", true);
	menuBackground.renderImage(m_Engine->getBackgroundSurface(), 0, 0, 0, 0
		, menuBackground.getWidth(), menuBackground.getHeight());
}

void LoseState::handleMouseDown(int iButton, int iX, int iY)
{
	printf("Lose:( %d , %d )\n", iX, iY);

	// down cast BaseEngine to Scyjl15Engine
	Scyjl15Engine* scyjl15Engine = dynamic_cast<Scyjl15Engine*>(m_Engine);
	// click the home button
	if (checkHomeButton(iX,iY))
	{
		State* start = new StartState(m_Engine);
		scyjl15Engine->m_Context->changeState(start, m_Engine);
	}
}

int LoseState::handleInitialiseObjects()
{
	m_Engine->drawableObjectsChanged();
	m_Engine->destroyOldObjects(true);
	return 0;
}

void LoseState::handleDrawStringOnTop()
{
	char scoreString[50];
	sprintf(scoreString, "Your Score: %d", score);
	m_Engine->drawForegroundString(495, 288, scoreString, 0xbababa, caveatFont);
}

bool LoseState::checkHomeButton(int x, int y)
{
	return checkClick(x,y,42,106,29,83);
}

void LoseState::setScore(int value)
{
	score = value;
}
