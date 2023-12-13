#include "header.h"
#include "RunningState.h"
#include "Scyjl15Engine.h"
#include "StartState.h"

RunningState::RunningState(BaseEngine* engine) : State(engine)
{
	Scyjl15Engine* scyjl15Engine = dynamic_cast<Scyjl15Engine*>(m_Engine);
	offset = 0;
	isPassed = false;
	hero = nullptr;
	enemyFactory = new EnemyFactory(m_Engine);
	score = 0;
	previousDisplayTime = 0;
	strcpy(conversationString, " ");
	currentDialog = 0;
	episodeID = 0;
	regularFont = m_Engine->getFont("resources/AlibabaPuHui.ttf", 30);
	smallMedicine = nullptr;
	smallEnergy = nullptr;
	largeMedicine = nullptr;
	largeEnergy = nullptr;
	isMoving = false;
}

RunningState::~RunningState() 
{
	if (enemyFactory != nullptr)
	{
		delete enemyFactory;
		enemyFactory = nullptr;
	}
}
void RunningState::handleSetupBackgroundBuffer()
{
	m_Engine->fillBackground(0x87c5e4);
}

void RunningState::handleMouseDown(int iButton, int iX, int iY)
{

}

int RunningState::handleInitialiseObjects()
{
	return 0;
}

void RunningState::handleDrawStringOnTop()
{
}

void RunningState::handleKeyDown(int keyCode)
{
}

void RunningState::handleCopyAllBackgroundBuffer()
{
}

void RunningState::handleMainLoopDoBeforeUpdate()
{
}
void RunningState::readDialogFromFile()
{
}
/*
* This function is used to check whether the player has died
*/
bool RunningState::checkGameOver()
{
	bool isOver = false;
	if (hero->getHP() <= 0)
	{
		// down cast BaseEngine to Scyjl15Engine
		Scyjl15Engine* scyjl15Engine = dynamic_cast<Scyjl15Engine*>(m_Engine);
		LoseState* lose = new LoseState(m_Engine,score);
		scyjl15Engine->m_Context->changeState(lose, m_Engine);
		isOver = true;
	}
	return isOver;
}
/*
* check the destroyed enemies and add corresponding marks
*/
void RunningState::checkMarks()
{
	DisplayableObject* displable;
	m_Engine->bookmarkSetToLast();
	int lastIndex = m_Engine->bookmarkGetCurrentIndex();
	for (int i = 0; i <= lastIndex; i++)
	{
		displable = m_Engine->getDisplayableObject(i);
		if (displable == nullptr) {
			continue;
		}
		Enemy* enemy = dynamic_cast<Enemy*>(displable);
		if (enemy != nullptr)
		{
			if (enemy->getHP() < 0)
			{
				Scyjl15Engine::playMusic("Score");
				score += enemy->getReward();
				m_Engine->drawableObjectsChanged();
				m_Engine->removeDisplayableObject(enemy);
				delete enemy;

			}
		}
	}
}

void RunningState::checkItems()
{
	if (smallMedicine != nullptr && smallMedicine->isVisible() &&
		CollisionUtil::pixelPerfectDetection(hero, smallMedicine))
	{
		Scyjl15Engine::playMusic("Item");
		smallMedicine->castEffect(hero);
	}
	if (smallEnergy != nullptr && smallEnergy->isVisible() &&
		CollisionUtil::pixelPerfectDetection(hero, smallEnergy))
	{
		Scyjl15Engine::playMusic("Item");
		smallEnergy->castEffect(hero);
	}
	if (largeMedicine != nullptr && largeMedicine->isVisible() &&
		CollisionUtil::pixelPerfectDetection(hero, largeMedicine))
	{
		Scyjl15Engine::playMusic("Item");
		largeMedicine->castEffect(hero);
	}
	if (largeEnergy != nullptr && largeEnergy->isVisible() &&
		CollisionUtil::pixelPerfectDetection(hero, largeEnergy))
	{
		Scyjl15Engine::playMusic("Item");
		largeEnergy->castEffect(hero);
	}
	
}


/*
* display several conversations in sequence
*/
void RunningState::displayDialog(int seconds, int endIndex)
{
	if (currentDialog > endIndex)
	{
		return;
	}
	if (TimeUtil::getTimeInterval(TimeUtil::getCurrentTime(), previousDisplayTime) >= seconds * 1000)
	{
		previousDisplayTime = TimeUtil::getCurrentTime();
		currentDialog++;
		if (currentDialog > endIndex)
		{
			strcpy(conversationString, " ");
			return;
		}
	}
	strncpy(conversationString, dialog[currentDialog].c_str(), 100);
}



int RunningState::getEpisodeID()
{
	return episodeID;
}

int RunningState::getOffset()
{
	return offset;
}

void RunningState::setOffset(int offset)
{
	this->offset = offset;
}

int RunningState::getCurrentDialog()
{
	return currentDialog;
}

void RunningState::setCurrentDialog(int dialog)
{
	currentDialog = dialog;
}

char* RunningState::getConversationString()
{
	return conversationString;
}

void RunningState::setConversationString(char conversation[])
{
	strcpy(conversationString, conversation);
}

long long RunningState::getPreviousDisplayTime()
{
	return previousDisplayTime;
}

void RunningState::setPreviousDisplayTime(long long  time)
{
	previousDisplayTime = time;
}

int RunningState::getScore()
{
	return score;
}

void RunningState::setScore(int value)
{
	score = value;
}

bool* RunningState::getStages()
{
	return stages;
}

void RunningState::setStages(bool stageArray[4])
{
	for (int i = 0; i < 4; i++)
	{
		stages[i] = stageArray[i];
	}
}



bool RunningState::getIsPassed()
{
	return isPassed;
}

void RunningState::setIsPassed(bool passed)
{
	isPassed = passed;
}


int* RunningState::getItemCounter()
{
	return itemCounter;
}

void RunningState::setItemCounter(bool counter[4])
{
	for (int i = 0; i < 4; i++)
	{
		itemCounter[i] = counter[i];
	}
}

bool* RunningState::getDialogControl()
{
	return dialogControl;
}

void RunningState::setDialogControl(bool control[3])
{
	for (int i = 0; i < 3; i++)
	{
		dialogControl[i] = control[i];
	}
}



Hero* RunningState::getHero()
{
	return hero;
}

void RunningState::drawAllItems()
{

	if (smallMedicine != nullptr && smallMedicine->isVisible())
	{
		smallMedicine->drawAllTiles(m_Engine,m_Engine->getBackgroundSurface());
	}
	if (smallEnergy != nullptr && smallEnergy->isVisible())
	{
		smallEnergy->drawAllTiles(m_Engine, m_Engine->getBackgroundSurface());
	}
	if (largeEnergy != nullptr && largeEnergy->isVisible())
	{
		largeEnergy->drawAllTiles(m_Engine, m_Engine->getBackgroundSurface());
	}
	if (largeMedicine != nullptr && largeMedicine->isVisible())
	{
		largeMedicine->drawAllTiles(m_Engine, m_Engine->getBackgroundSurface());
	}
}
