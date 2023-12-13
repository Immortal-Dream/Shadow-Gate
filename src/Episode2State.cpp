#include "header.h"
#include "Episode2State.h"
#include "Episode3State.h"
#include "PauseState.h"
#include "Scyjl15Engine.h"


Episode2State::Episode2State(BaseEngine* engine, Hero* hero)
	: RunningState(engine)
{
	episodeID = 2;
	poisonTile = new PoisonTile();
	readDialogFromFile();
	currentDialog = 1;
	score = 105;
	previousDisplayTime = TimeUtil::getCurrentTime();
	this->hero = hero;
	strncpy(conversationString, dialog[currentDialog].c_str(), 100);
	largeEnergy = make_shared<LargeEnergyTile>();
	largeMedicine = make_shared<LargeMedicineTile>();
}

Episode2State::~Episode2State()
{
	delete poisonTile;
}

void Episode2State::handleSetupBackgroundBuffer()
{
	SimpleImage gameBackground = ImageManager::loadImage("images/backgrounds/Episode2.png", true);
	gameBackground.renderImage(m_Engine->getBackgroundSurface(), offset, 0, 0, 0
		, 1300, 800);
	SimpleImage scoreBoard = ImageManager::loadImage("images/elements/ScoreBoard2.png", true);
	scoreBoard.renderImage(m_Engine->getBackgroundSurface(), 0, 0, 875, 5
		, scoreBoard.getWidth(), scoreBoard.getHeight());
	SimpleImage heroBoard = ImageManager::loadImage("images/elements/HeroBoard2.png", true);
	heroBoard.renderImage(m_Engine->getBackgroundSurface(), 0, 0, 5, 5
		, heroBoard.getWidth(), heroBoard.getHeight());
	drawAllItems();
	if (poisonTile->isVisible())
	{
		poisonTile->drawAllTiles(m_Engine, m_Engine->getBackgroundSurface());
	}
}

void Episode2State::handleMouseDown(int iButton, int iX, int iY)
{
	printf("Episode2:( %d , %d ,offset: %d)\n", iX, iY, offset);
	double radian = RadianUtil::getRelativeRadian
	(hero->getXCentre(), hero->getYCentre(), iX, iY);
	hero->getRotator()->setRotation(radian);


	// get current time int milliseconds
	long long now_ms = TimeUtil::getCurrentTime();
	hero->fireWithColdingTime(now_ms, iX, iY);
}

int Episode2State::handleInitialiseObjects()
{
	m_Engine->drawableObjectsChanged();

	m_Engine->destroyOldObjects(true);

	m_Engine->createObjectArray(2);

	m_Engine->setAllObjectsVisible(true);

	m_Engine->storeObjectInArray(0, hero);

	m_Engine->storeObjectInArray(1, hero->getWeapon());
	return 0;
}

void Episode2State::handleDrawStringOnTop()
{
	char shieldString[20];
	char hpString[20];
	char energeString[20];
	char currentScore[25];

	sprintf(shieldString, "Shield: %d / %d", hero->getShield(), hero->getMaximumShield());
	sprintf(hpString, "HP: %d / %d", hero->getHP(), hero->getMaximumHP());
	sprintf(energeString, "Energy: %d / %d", hero->getEnerge(), hero->getMaximumEnerge());
	sprintf(currentScore, "Score: %d", score);

	char episode[27] = "Episode2: No Step Back!";

	m_Engine->drawForegroundString(15, 15, shieldString, 0xf3f3f3, NULL);
	m_Engine->drawForegroundString(15, 50, hpString, 0xf3f3f3, NULL);
	m_Engine->drawForegroundString(15, 85, energeString, 0xf3f3f3, NULL);
	m_Engine->drawForegroundString(890, 15, episode, 0xf3f3f3, NULL);
	m_Engine->drawForegroundString(890, 60, currentScore, 0xf3f3f3, NULL);

	m_Engine->drawForegroundString(45, 722, conversationString, 0xf3f3f3, regularFont);

}

void Episode2State::handleKeyDown(int keyCode)
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
	// if player has cleared all enemies, press 'E' to enter next episode
	if (keyCode == SDLK_e && isPassed)
	{
		Hero* heroCopy = hero->copyHero();
		Scyjl15Engine* scyjl15Engine = dynamic_cast<Scyjl15Engine*>(m_Engine);
		Episode3State* episode3 = new Episode3State(m_Engine, heroCopy);
		scyjl15Engine->m_Context->changeState(episode3, m_Engine);
		return;
	}
}

void Episode2State::handleCopyAllBackgroundBuffer()
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

void Episode2State::handleMainLoopDoBeforeUpdate()
{
	checkMarks();
	checkItems();
	checkPoison();
	hero->setWeaponFollowed();
	m_Engine->getForegroundSurface()->copyEntireSurface(m_Engine->getBackgroundSurface());

	if (checkGameOver())
	{
		return;
	}

	displayDialog(DISPLAY_SECONDS, 1);
	if (!stages[0] && currentDialog == 2)
	{
		enemyFactory->produceMultipleEnemies("Orc", 3);
		enemyFactory->produceMultipleEnemies("Goblin", 2);
		poisonTile->displayPoison(m_Engine);
		stages[0] = true;
	}
	if (score == 140)
	{
		if (dialogControl[0])
		{
			previousDisplayTime = TimeUtil::getCurrentTime();
			dialogControl[0] = false;
			poisonTile->hideAllTiles(m_Engine);
		}
		displayDialog(DISPLAY_SECONDS, 2);
	}
	if (score == 140 && !isMoving && !stages[1])
	{
		isMoving = true;
	}
	// open stage2 and generate new monsters
	if (score == 140 && offset >= 400 && !stages[1])
	{
		// stage 2 of episode 2
		enemyFactory->produceMultipleEnemies("Skeleton", 3);
		enemyFactory->produceMultipleEnemies("Goblin", 2);
		stages[1] = true;
		poisonTile->displayPoison(m_Engine);
		isMoving = false;
	}
	if (score == 184 && itemCounter[LARGE_MEDICINE] == 0)
	{
		poisonTile->hideAllTiles(m_Engine);
		itemCounter[LARGE_MEDICINE]++;
		largeMedicine->enableItem(m_Engine);
	}
	if (score == 184 && !isMoving && !stages[2])
	{
		isMoving = true;
	}
	// stage 3 begin
	if (score == 184 && offset >= 800 && !stages[2])
	{
		poisonTile->displayPoison(m_Engine);
		// stage 2 of episode 2
		enemyFactory->produceMultipleEnemies("Skeleton", 3);
		enemyFactory->produceMultipleEnemies("Goblin", 3);
		enemyFactory->produceMultipleEnemies("Behemoth", 1);
		stages[2] = true;
		isMoving = false;
	}

	if (score >= 184 && score < 253)
	{
		if (dialogControl[1])
		{
			previousDisplayTime = TimeUtil::getCurrentTime();
			dialogControl[1] = false;
		}
		displayDialog(DISPLAY_SECONDS, 4);
	}

	// episode 2 ends
	if (score == 253)
	{
		if (!isMoving)
		{
			isMoving = true;
		}
		isPassed = true;
		if (dialogControl[2])
		{
			poisonTile->hideAllTiles(m_Engine);
			previousDisplayTime = TimeUtil::getCurrentTime();
			dialogControl[2] = false;
			displayDialog(DISPLAY_SECONDS, 5);
		}
		if (itemCounter[LARGE_ENERGY] == 0)
		{
			itemCounter[LARGE_ENERGY]++;
			largeEnergy->enableItem(m_Engine);
		}
	}
}

void Episode2State::readDialogFromFile()
{
	dialog = FileUtils::readPairFromFile("data/episode2_dialog.txt");
}

/*
* check whether the hero is in poisoned area
*/
void Episode2State::checkPoison()
{
	if (poisonTile->isVisible() && CollisionUtil::pixelPerfectDetection(hero, poisonTile))
	{
		if ((TimeUtil::getTimeInterval(TimeUtil::getCurrentTime(),
			poisonTile->getLastPoisonedTime()) > poisonTile->getPoisonInterval()))
		{

			hero->beHit(poisonTile->getDamage());
			poisonTile->setLastPoisonedTime(TimeUtil::getCurrentTime());
		}
	}

}

PoisonTile* Episode2State::getPoisonTile()
{
	return poisonTile;
}
