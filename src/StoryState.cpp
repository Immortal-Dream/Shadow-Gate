#include "header.h"
#include "StoryState.h"
#include "Scyjl15Engine.h"
#include "StartState.h"
#include "Episode1State.h"
#include "SerializationUtil.h"

StoryState::StoryState(BaseEngine* engine) : State(engine) 
{
	offset = 0;
	isScrolling = true;
	scrollingSpeed = 2;

}
StoryState::~StoryState() 
{

}
void StoryState::handleSetupBackgroundBuffer()
{
	

	if (offset <800)
	{
		SimpleImage menuBackground = ImageManager::loadImage("images/backgrounds/Menu.png", true);
		menuBackground.renderImage(m_Engine->getBackgroundSurface(), 0, offset, 0, 0
			, 1300, 800-offset);
		SimpleImage storyBackground = ImageManager::loadImage("images/backgrounds/StoryPage.png", true);
		storyBackground.renderImage(m_Engine->getBackgroundSurface(), 0, 0, 0, 800-offset
			, 1300, offset);
		m_Engine->getBackgroundSurface()->setOpaque();
	}
	else
	{
		SimpleImage storyBackground = ImageManager::loadImage("images/backgrounds/StoryPage.png", true);
		storyBackground.renderImage(m_Engine->getBackgroundSurface(), 0, offset - 800, 0, 0
			, 1300, 3500);
		m_Engine->getBackgroundSurface()->setOpaque();
	}
	// draw the buttons
	SimpleImage newGame = ImageManager::loadImage("images/elements/NewGame.png", true);
	newGame.renderImageWithMask(m_Engine->getBackgroundSurface(), 0, 0, 1154, 700
		, 150, 80);

	SimpleImage continueImage = ImageManager::loadImage("images/elements/Continue.png", true);
	continueImage.renderImageWithMask(m_Engine->getBackgroundSurface(), 0, 0, 1154, 600
		, 150, 80);
	// draw the key pressed hints
	SimpleImage hints = ImageManager::loadImage("images/elements/StoryKeys.png", true);
	hints.renderImageWithMask(m_Engine->getBackgroundSurface(), 0, 0, 1154, 120
		, hints.getWidth(), hints.getHeight());


}

void StoryState::handleMainLoopDoBeforeUpdate()
{
	// if user pressed up button, the page will go up
	if (m_Engine->isKeyPressed(SDLK_UP) && offset > 0)
	{
		offset -= 10;
	}
	// if user pressed down button, the page will go down
	if (m_Engine->isKeyPressed(SDLK_DOWN) && offset < 3500)
	{
		offset += 10;
	}
	if (offset < 3500 && isScrolling)
	{
		offset = offset + scrollingSpeed;
	}
	m_Engine->lockBackgroundForDrawing();
	handleSetupBackgroundBuffer();
	m_Engine->unlockBackgroundForDrawing();
	m_Engine->redrawDisplay();
}

void StoryState::handleCopyAllBackgroundBuffer()
{
	m_Engine->getForegroundSurface()->copyEntireSurface(m_Engine->getBackgroundSurface());
}

void StoryState::handleMouseDown(int iButton, int iX, int iY)
{
	printf("Story:( %d , %d )\n", iX, iY);
	// start a new game
	if (checkNewGameButton(iX,iY))
	{
		Scyjl15Engine* scyjl15Engine = dynamic_cast<Scyjl15Engine*>(m_Engine);
		State* episode1 = new Episode1State(m_Engine);
		scyjl15Engine->m_Context->changeState(episode1, m_Engine);
	}
	// continue last saved game
	if (checkContinueButton(iX, iY))
	{
		Scyjl15Engine* scyjl15Engine = dynamic_cast<Scyjl15Engine*>(m_Engine);
		SerializationUtil serialization;
		State* runningState = serialization.deserialize(m_Engine);
		if (runningState == nullptr)
		{
			runningState = new Episode1State(m_Engine);
			scyjl15Engine->m_Context->changeState(runningState, m_Engine);
		}
		else
		{
			scyjl15Engine->m_Context->continueState(runningState, m_Engine);
		}
		
	}
}


bool StoryState::checkNewGameButton(int x, int y)
{
	return checkClick(x,y,1161,1293,720,772);
}

bool StoryState::checkContinueButton(int x, int y)
{
	return checkClick(x, y, 1161, 1293, 620, 672);
}

void StoryState::handleKeyDown(int keyCode)
{
	// if players pressed space key, then switch the scroing 
	// status: scoring
	if (keyCode == SDLK_SPACE)
	{
		isScrolling = !isScrolling;
	}
	// speed up the scrolling
	if (keyCode == SDLK_RIGHT)
	{
		if (scrollingSpeed < 6)
		{
			scrollingSpeed += 1;
		}
	}
	// slow down the scrolling speed
	if (keyCode == SDLK_LEFT)
	{
		if (scrollingSpeed > 1)
		{
			scrollingSpeed -= 1;
		}
	}
	// return to start menu
	if (keyCode == SDLK_ESCAPE)
	{
		// back to start menu state
		Scyjl15Engine* scyjl15Engine = dynamic_cast<Scyjl15Engine*>(m_Engine);
		State* start = new StartState(m_Engine);
		scyjl15Engine->m_Context->changeState(start, m_Engine);
	}

}
