#include "header.h"
#include "Episode3State.h"
#include "Scyjl15Engine.h"
#include "PauseState.h"
#include "WinState.h"

Episode3State::Episode3State(BaseEngine* engine, Hero* hero)
	: RunningState(engine) 
{
	episodeID = 3;
	readDialogFromFile();
	currentDialog = 1;
	this->hero = hero;
	score = 253;
	strncpy(conversationString, dialog[currentDialog].c_str(), 100);
	largeEnergy = make_shared<LargeEnergyTile>();
	largeMedicine = make_shared<LargeMedicineTile>();
	smallMedicine = make_shared<SmallMedicineTile>();
}

Episode3State::~Episode3State()
{
}

void Episode3State::handleSetupBackgroundBuffer()
{
	SimpleImage gameBackground = ImageManager::loadImage("images/backgrounds/Episode3.png", true);
	gameBackground.renderImage(m_Engine->getBackgroundSurface(), offset, 0, 0, 0
		, 1300, 800);
	SimpleImage scoreBoard = ImageManager::loadImage("images/elements/ScoreBoard3.png", true);
	scoreBoard.renderImage(m_Engine->getBackgroundSurface(), 0, 0, 875, 5
		, scoreBoard.getWidth(), scoreBoard.getHeight());
	SimpleImage heroBoard = ImageManager::loadImage("images/elements/HeroBoard3.png", true);
	heroBoard.renderImage(m_Engine->getBackgroundSurface(), 0, 0, 5, 5
		, heroBoard.getWidth(), heroBoard.getHeight());
	drawAllItems();
}



int Episode3State::handleInitialiseObjects()
{
	m_Engine->drawableObjectsChanged();

	m_Engine->destroyOldObjects(true);

	m_Engine->createObjectArray(2);

	m_Engine->setAllObjectsVisible(true);

	m_Engine->storeObjectInArray(0, hero);

	m_Engine->storeObjectInArray(1, hero->getWeapon());
	return 0;
}

void Episode3State::handleDrawStringOnTop()
{
	char shieldString[20];
	char hpString[20];
	char energeString[20];
	char currentScore[25];

	sprintf(shieldString, "Shield: %d / %d", hero->getShield(), hero->getMaximumShield());
	sprintf(hpString, "HP: %d / %d", hero->getHP(), hero->getMaximumHP());
	sprintf(energeString, "Energy: %d / %d", hero->getEnerge(), hero->getMaximumEnerge());
	sprintf(currentScore, "Score: %d", score);

	char episode[27] = "Episode3: By Blood Alone!";

	m_Engine->drawForegroundString(15, 15, shieldString, 0xf3f3f3, NULL);
	m_Engine->drawForegroundString(15, 50, hpString, 0xf3f3f3, NULL);
	m_Engine->drawForegroundString(15, 85, energeString, 0xf3f3f3, NULL);
	m_Engine->drawForegroundString(890, 15, episode, 0xf3f3f3, NULL);
	m_Engine->drawForegroundString(890, 60, currentScore, 0xf3f3f3, NULL);

	m_Engine->drawForegroundString(45, 722, conversationString, 0xf3f3f3, regularFont);

}

void Episode3State::handleKeyDown(int keyCode)
{
	/*
    * if user press space key, the game will pause
    */
	if (keyCode == SDLK_SPACE)
	{
		// down cast BaseEngine to Scyjl15Engine
		Scyjl15Engine* scyjl15Engine = dynamic_cast<Scyjl15Engine*>(m_Engine);
		PauseState* pause = new PauseState(m_Engine, this);
		scyjl15Engine->m_Context->pause(pause, m_Engine);
	}

}

void Episode3State::handleCopyAllBackgroundBuffer()
{
	if (isMoving && offset <= 800 && offset >= 0)
	{
		if (hero->getDrawingRegionRight() >= 1250) {
			hero->setPosition(hero->getDrawingRegionLeft() - 3, hero->getDrawingRegionTop());
			offset = min(offset + 3, 1400);
			m_Engine->lockBackgroundForDrawing();
			handleSetupBackgroundBuffer();
			m_Engine->unlockBackgroundForDrawing();
			m_Engine->redrawDisplay();
		}
		if (hero->getDrawingRegionLeft() <= 20) {
			hero->setPosition(hero->getDrawingRegionLeft() + 3, hero->getDrawingRegionTop());
			offset = max(offset - 3, 0);
			m_Engine->lockBackgroundForDrawing();
			handleSetupBackgroundBuffer();
			m_Engine->unlockBackgroundForDrawing();
			m_Engine->redrawDisplay();
		}
	}
}

void Episode3State::handleMouseDown(int iButton, int iX, int iY)
{
	printf("Episode3:( %d , %d ,offset: %d)\n", iX, iY,offset);
	double radian = RadianUtil::getRelativeRadian
	(hero->getXCentre(), hero->getYCentre(), iX, iY);
	hero->getRotator()->setRotation(radian);


	// get current time int milliseconds
	long long now_ms = TimeUtil::getCurrentTime();
	hero->fireWithColdingTime(now_ms, iX, iY);
}

void Episode3State::handleMainLoopDoBeforeUpdate()
{
	checkMarks();
	checkItems();
	hero->setWeaponFollowed();
	m_Engine->getForegroundSurface()->copyEntireSurface(m_Engine->getBackgroundSurface());
	if (checkGameOver())
	{
		return;
	}
	
	// open stage1 and generate new monsters
	if (!stages[0])
	{
		enemyFactory->produceMultipleEnemies("Orc", 2);
		enemyFactory->produceMultipleEnemies("Goblin", 2);
		enemyFactory->produceMultipleEnemies("Behemoth", 1);
		stages[0] = true;
		previousDisplayTime = TimeUtil::getCurrentTime();
	}
	if (stages[0])
	{
		displayDialog(DISPLAY_SECONDS, 1);
	}
	
	if (score == 298 && itemCounter[SMALL_MEDICINE]==0)
	{
		itemCounter[SMALL_MEDICINE] ++;
		smallMedicine->enableItem(m_Engine);
	}
	if (score == 298 && !isMoving && !stages[1])
	{
		isMoving = true;
	}
	// open stage2 and generate new monsters
	if (score == 298 && offset >= 400 && !stages[1])
	{
		// stage 2 of episode 3
		enemyFactory->produceMultipleEnemies("Skeleton", 2);
		enemyFactory->produceMultipleEnemies("Goblin", 2);
		enemyFactory->produceMultipleEnemies("Behemoth", 2);
		stages[1] = true;
		isMoving = false;
	}
	if (score == 364 && itemCounter[LARGE_MEDICINE] == 0)
	{
		itemCounter[LARGE_MEDICINE]++;
		largeMedicine->enableItem(m_Engine);

		itemCounter[LARGE_ENERGY]++;
		largeEnergy->enableItem(m_Engine);
	}
	if (score == 364 && !isMoving && !stages[2])
	{
		isMoving = true;
	}
	// open final stage and generate new monsters
	if (score == 364 && offset >= 800 && !stages[2])
	{
		// stage 3
		enemyFactory->produceMultipleEnemies("Orc", 3);
		enemyFactory->produceMultipleEnemies("Goblin", 3);
		enemyFactory->produceMultipleEnemies("Wizard", 1);
		stages[2] = true;
		isMoving = false;
		previousDisplayTime = TimeUtil::getCurrentTime();
	}
	if (stages[2] && score < 500)
	{
		displayDialog(DISPLAY_SECONDS, 6);
	}
	if (score == 500 && !isPassed)
	{
		if (!isMoving)
		{
			isMoving = true;
		}
		isPassed = true;
		Scyjl15Engine* scyjl15Engine = dynamic_cast<Scyjl15Engine*>(m_Engine);
		State* win = new WinState(m_Engine);
		scyjl15Engine->m_Context->changeState(win, m_Engine);
		return;
	}
}

void Episode3State::readDialogFromFile()
{
	dialog = FileUtils::readPairFromFile("data/episode3_dialog.txt");
}
