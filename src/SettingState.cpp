#include "header.h"
#include "SettingState.h"
#include "StartState.h"
#include "Scyjl15Engine.h"
SettingState::SettingState(BaseEngine* engine): State(engine) 
{
	inputPointer = 1;
	playerName[0] = ' ';
	playerName[1] = '\0';
	gameSettings = FileUtils::readFromFile("data/game_setting.txt");
	regularFont = m_Engine->getFont("resources/AlibabaPuHui.ttf", 25);
	caveatFont = m_Engine->getFont("resources/Caveat-SemiBold.ttf", 38);
	scoreList = FileUtils::loadScores();
}
SettingState::~SettingState()
{
	FileUtils::clearPairsInVector(scoreList);
}
void SettingState::handleSetupBackgroundBuffer()
{
	SimpleImage menuBackground = ImageManager::loadImage("images/backgrounds/SettingPage.png", true);
	menuBackground.renderImage(m_Engine->getBackgroundSurface(), 0, 0, 0, 0
		, menuBackground.getWidth(), menuBackground.getHeight());
	
	SimpleImage playButton = ImageManager::loadImage("images/elements/PlayMusic.png", true);
	playButton.renderImageWithMask(m_Engine->getBackgroundSurface(), 0, 0, 466, 330
		, playButton.getWidth(), playButton.getHeight());
	
	SimpleImage muteButton = ImageManager::loadImage("images/elements/Mute.png", true);
	muteButton.renderImageWithMask(m_Engine->getBackgroundSurface(), 0, 0, 730, 330
		, muteButton.getWidth(), muteButton.getHeight());
}

void SettingState::handleMouseDown(int iButton, int iX, int iY)
{
	printf("Setting: ( %d , %d )\n", iX, iY);
	// down cast BaseEngine to Scyjl15Engine
	Scyjl15Engine* scyjl15Engine = dynamic_cast<Scyjl15Engine*>(m_Engine);
	if (checkReturnButton(iX,iY))
	{
		State* start = new StartState(m_Engine);
		scyjl15Engine->m_Context->changeState(start, m_Engine);
	}
	if (checkSaveButton(iX, iY))
	{

		gameSettings["player name"] = playerName;
		// update the name settings
		FileUtils::saveMapToFile(gameSettings,"data/game_setting.txt");
		State* start = new StartState(m_Engine);
		scyjl15Engine->m_Context->changeState(start, m_Engine);
	}
	if (checkPlayButton(iX,iY) && !scyjl15Engine->getIsPlaying())
	{
		scyjl15Engine->playMusicLoop(scyjl15Engine->mainMusicPath,"mainMusic");
		scyjl15Engine->setIsPlaying(true);
	}
	if (checkMuteButton(iX, iY) && scyjl15Engine->getIsPlaying())
	{
		scyjl15Engine->stopAndCloseMusic("mainMusic");
		scyjl15Engine->setIsPlaying(false);
	}
}

int SettingState::handleInitialiseObjects()
{
	m_Engine->drawableObjectsChanged();

	m_Engine->destroyOldObjects(true);

	m_Engine->createObjectArray(1);

	m_Engine->setAllObjectsVisible(true);

	return 0;
}


bool SettingState::checkReturnButton(int x, int y)
{
	return checkClick(x, y, 41, 99, 53, 112);
}

void SettingState::handleDrawStringOnTop()
{
	Scyjl15Engine* scyjl15Engine = dynamic_cast<Scyjl15Engine*>(m_Engine);

	m_Engine->drawForegroundString(457,247,playerName,0xc2c7cc,regularFont);

	char top1[100];
	sprintf(top1, "1st: %s    %d", scoreList[0]->getFirst().c_str(), scoreList[0]->getSecond());
	char top2[100];
	sprintf(top2, "2st: %s    %d", scoreList[1]->getFirst().c_str(), scoreList[1]->getSecond());
	char top3[100];
	sprintf(top3, "3st: %s    %d", scoreList[2]->getFirst().c_str(), scoreList[2]->getSecond());
	m_Engine->drawForegroundString(140, 527, top1, 0xc2c7cc, caveatFont);
	m_Engine->drawForegroundString(140, 577, top2, 0xc2c7cc, caveatFont);
	m_Engine->drawForegroundString(140, 627, top3, 0xc2c7cc, caveatFont);

}

void SettingState::handleKeyDown(int iKeyCode)
{
	if (iKeyCode >= 97 && iKeyCode <=122)
	{
		// if the user pressed left shift, transfer to upper case
		if (m_Engine->isKeyPressed(SDLK_LSHIFT))
		{
			playerName[inputPointer] = iKeyCode - 32;
		}
		else {
			playerName[inputPointer] = iKeyCode;
		}
		
		inputPointer++;
		playerName[inputPointer] = '\0';
		m_Engine->redrawDisplay();
	}
	// support input with space, numbers and math operators
	if (iKeyCode >= 32 && iKeyCode <= 64 && iKeyCode != 44)
	{
		playerName[inputPointer] = iKeyCode;
		inputPointer++;
		playerName[inputPointer] = '\0';
		m_Engine->redrawDisplay();
	}
	// delete button
	if (iKeyCode == SDLK_BACKSPACE)
	{
		if (inputPointer > 1)
		{
			inputPointer--;
			playerName[inputPointer] = '\0';
			m_Engine->redrawDisplay();
		}

	}
}

bool SettingState::checkSaveButton(int x, int y)
{
	return checkClick(x, y, 561, 765, 683, 743);
}

bool SettingState::checkPlayButton(int x, int y)
{
	return checkClick(x,y,466, 586, 330, 500);
}

bool SettingState::checkMuteButton(int x, int y)
{
	return checkClick(x, y,730, 850, 330, 500);;
}
