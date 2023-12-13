#include "header.h"
#include "Episode1State.h"
#include "Episode2State.h"
#include "Episode3State.h"
#include "WinState.h"
#include "LoseState.h"

Episode1State::Episode1State(BaseEngine* engine) : RunningState(engine) {
	episodeID = 1;
	readDialogFromFile();
	currentDialog = 1;
	previousDisplayTime = TimeUtil::getCurrentTime();
	hero = new Hero(m_Engine);
	strncpy(conversationString, dialog[currentDialog].c_str(), 100);
	smallMedicine = make_shared<SmallMedicineTile>();
	smallEnergy = make_shared<SmallEnergyTile>();

}

void Episode1State::handleSetupBackgroundBuffer()
{

	SimpleImage gameBackground = ImageManager::loadImage("images/backgrounds/Episode1.png", true);
	gameBackground.renderImage(m_Engine->getBackgroundSurface(), offset, 0, 0, 0
		, 1300, 800);
	SimpleImage scoreBoard = ImageManager::loadImage("images/elements/ScoreBoard1.png", true);
	scoreBoard.renderImage(m_Engine->getBackgroundSurface(), 0, 0, 875, 5
		, scoreBoard.getWidth(), scoreBoard.getHeight());
	SimpleImage heroBoard = ImageManager::loadImage("images/elements/HeroBoard1.png", true);
	heroBoard.renderImage(m_Engine->getBackgroundSurface(), 0, 0, 5, 5
		, heroBoard.getWidth(), heroBoard.getHeight());
	drawAllItems();
}



int Episode1State::handleInitialiseObjects()
{
	m_Engine->drawableObjectsChanged();

	m_Engine->destroyOldObjects(true);

	m_Engine->createObjectArray(4);

	m_Engine->setAllObjectsVisible(true);

	m_Engine->storeObjectInArray(0, hero);

	m_Engine->storeObjectInArray(1, hero->getWeapon());
	return 0;
}

void Episode1State::handleDrawStringOnTop()
{
	char shieldString[20];
	char hpString[20];
	char energeString[20];
	char currentScore[25];

	sprintf(shieldString, "Shield: %d / %d", hero->getShield(),hero->getMaximumShield());
	sprintf(hpString, "HP: %d / %d", hero->getHP(),hero->getMaximumHP());
	sprintf(energeString, "Energy: %d / %d", hero->getEnerge(),hero->getMaximumEnerge());
	sprintf(currentScore, "Score: %d", score);
	
	char episode[27] = "Episode1: Break The Gate!";

	m_Engine->drawForegroundString(15,15, shieldString, 0xf3f3f3, NULL);
	m_Engine->drawForegroundString(15,50, hpString, 0xf3f3f3, NULL);
	m_Engine->drawForegroundString(15,85, energeString, 0xf3f3f3, NULL);
	m_Engine->drawForegroundString(890,15, episode, 0xf3f3f3, NULL);
	m_Engine->drawForegroundString(890,60, currentScore, 0xf3f3f3, NULL);

	m_Engine->drawForegroundString(45, 722, conversationString, 0xf3f3f3, regularFont);

}

void Episode1State::handleKeyDown(int keyCode)
{

	/*
	* if user press space key, the game will pause
	*/
	if (keyCode == SDLK_SPACE)
	{
		// down cast BaseEngine to Scyjl15Engine
		Scyjl15Engine* scyjl15Engine = dynamic_cast<Scyjl15Engine*>(m_Engine);
		PauseState* pause = new PauseState(m_Engine,this);
		scyjl15Engine->m_Context->pause(pause, m_Engine);
	}
	// if player has cleared all enemies, press 'E' to enter next episode
	if (keyCode == SDLK_e && isPassed)
	{
		Hero* heroCopy = hero->copyHero();
		Scyjl15Engine* scyjl15Engine = dynamic_cast<Scyjl15Engine*>(m_Engine);
		Episode2State* episode2 = new Episode2State(m_Engine, heroCopy);
		scyjl15Engine->m_Context->changeState(episode2, m_Engine);
		return;
	}

}

void Episode1State::handleCopyAllBackgroundBuffer()
{
	if (isMoving && offset <= 1400 && offset >= 0)
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
void Episode1State::handleMouseDown(int iButton, int iX, int iY)
{
	printf("Episode1:( %d , %d )\n", iX, iY);
	double radian = RadianUtil::getRelativeRadian
			(hero->getXCentre(),hero->getYCentre(), iX,iY);
	hero->getRotator()->setRotation(radian);


	// get current time int milliseconds
	long long now_ms = TimeUtil::getCurrentTime();
	hero->fireWithColdingTime(now_ms,iX, iY);

}

/*
* main logic of episode1
*/
void Episode1State::handleMainLoopDoBeforeUpdate()
{
	checkMarks();
	checkItems();


	if (checkGameOver())
	{
		return;
	}

	// display first three pieces of dialog
	displayDialog(DISPLAY_SECONDS,2);

	
	// open stage1 and generate 3 new monsters
	if (!stages[0] && currentDialog == 3)
	{
		displayDialog(DISPLAY_SECONDS, 3);
		enemyFactory->produceMultipleEnemies("Orc", 3);
		stages[0] = true;
	}
	// clear first wave of enemies
	if (score == 15)
	{
		displayDialog(DISPLAY_SECONDS, 5);
	}
	// set the background can be scrolled by player
	if (score == 15 && !isMoving && !stages[1])
	{
		isMoving = true;
	}
	// open stage2 and generate new monsters
	if (score == 15 && offset >= 400 && !stages[1])
	{
		// stage 2 of episode 1, generate 2 new orcs and 1 skeleton
		enemyFactory->produceMultipleEnemies("Orc", 2);
		enemyFactory->produceMultipleEnemies("Skeleton", 1);
		stages[1] = true;
		// player cannot move the background when fighting
		isMoving = false;
	}
	if (stages[1] == true)
	{
		displayDialog(DISPLAY_SECONDS, 8);
	}


	// stage 2 end, reward one small medicine to recover hp
	if (score == 33)
	{
		if (currentDialog == 9 && dialogControl[0])
		{
			previousDisplayTime = TimeUtil::getCurrentTime();
			dialogControl[0] = false;
		}
		displayDialog(DISPLAY_SECONDS, 9);

		if (itemCounter[SMALL_ENERGY] == 0)
		{
			itemCounter[SMALL_ENERGY]++;
			smallEnergy->enableItem(m_Engine);
		}
	}
	if (score == 33 && !isMoving && !stages[2])
	{
		isMoving = true;
	}
	// stage 3 begin
	if (score == 33 && offset >= 800 && !stages[2])
	{
		// stage 3 of episode 1, generate 3 new orcs, 2 new skeletons
		enemyFactory->produceMultipleEnemies("Orc", 3);
		enemyFactory->produceMultipleEnemies("Skeleton", 2);
		stages[2] = true;
		// lock the background
		isMoving = false;
	}
	if (score == 64 && !isMoving && !stages[3])
	{
		isMoving = true;
	}
	if (score == 64)
	{
		if (dialogControl[1])
		{
			currentDialog = 10;
			previousDisplayTime = TimeUtil::getCurrentTime();
			dialogControl[1] = false;
		}
		displayDialog(DISPLAY_SECONDS, 10);	
	}

	if (score == 64 && offset >= 1250 && !stages[3])
	{
		// stage 4 of episode 1, generate 5 new orcs, 2 new skeletons
		enemyFactory->produceMultipleEnemies("Orc", 5);
		enemyFactory->produceMultipleEnemies("Skeleton", 2);
		stages[3] = true;
		isMoving = false;
	}
	// if the player reached 105 scores, which means he or she has
	// passed this episode
	if (score == 105)
	{
		if (itemCounter[SMALL_MEDICINE] == 0)
		{
			itemCounter[SMALL_MEDICINE]++;
			smallMedicine->enableItem(m_Engine);
		}
		if (!isMoving)
		{
			isMoving = true;
		}
		isPassed = true;
	}
	if (isPassed)
	{
		if (dialogControl[2])
		{
			currentDialog = 11;
			previousDisplayTime = TimeUtil::getCurrentTime();
			dialogControl[2] = false;
			displayDialog(DISPLAY_SECONDS, 11);
		}
		
	}
	
	hero->setWeaponFollowed();
	m_Engine->getForegroundSurface()->copyEntireSurface(m_Engine->getBackgroundSurface());
}
/*
* read dialog data from txt file
*/
void Episode1State::readDialogFromFile()
{
	dialog = FileUtils::readPairFromFile("data/episode1_dialog.txt");
}




