#pragma once
#include "Hero.h"
#include "LoseState.h"
#include "RadianUtil.h"
#include "EnemyFactory.h"
#include "SmallMedicineTile.h"
#include "LargeMedicineTile.h"
#include "SmallEnergyTile.h"
#include "LargeEnergyTile.h"

// SerializationUtil is a friend class of this class
class SerializationUtil;
class RunningState :
    public State
{
private:
	friend class SerializationUtil;
protected:
	// member variables that do not need to be serialized
	map<int, string>  dialog;
	EnemyFactory* enemyFactory;
	int DISPLAY_SECONDS = 6;
	Font* regularFont;
	const int SMALL_MEDICINE = 0;
	const int LARGE_MEDICINE = 1;
	const int SMALL_ENERGY = 2;
	const int LARGE_ENERGY = 3;
	// member variables that need to be serialized
	int episodeID;
	int offset;
	int currentDialog;
	char conversationString[100];
	long long previousDisplayTime;
	Hero* hero;
	int score;
	bool stages[4] = { false, false, false, false };
	bool isPassed;
	shared_ptr<SmallMedicineTile> smallMedicine;
	shared_ptr<SmallEnergyTile> smallEnergy;
	shared_ptr<LargeMedicineTile> largeMedicine;
	shared_ptr<LargeEnergyTile> largeEnergy;
	// count the emerge times of each item
	int itemCounter[4] = {0,0,0,0};
	// control whether the background can be scrolled
	bool isMoving;
	bool dialogControl[3] = { true, true, true };
public:
	RunningState(BaseEngine* engine);
	virtual ~RunningState();
	virtual void handleSetupBackgroundBuffer() override;
	virtual void handleMouseDown(int iButton, int iX, int iY);
	virtual int handleInitialiseObjects() override;
	virtual void handleDrawStringOnTop() override;
	virtual void handleKeyDown(int keyCode) override;
	virtual void handleCopyAllBackgroundBuffer() override;
	virtual void handleMainLoopDoBeforeUpdate() override;
	virtual void readDialogFromFile();
	bool checkGameOver();
	void checkMarks();
	void checkItems();
	void displayDialog(int seconds, int endIndex);

	// getter and setter functions
	int getEpisodeID();
	int getOffset();
	void setOffset(int offset);

	int getCurrentDialog();
	void setCurrentDialog(int dialog);

	char* getConversationString();
	void setConversationString(char conversation[]);

	long long getPreviousDisplayTime();
	void setPreviousDisplayTime(long long  time);

	int getScore();
	void setScore(int value);

	bool* getStages();
	void setStages(bool stageArray[4]);

	bool getIsPassed();
	void setIsPassed(bool passed);

	int* getItemCounter();
	void setItemCounter(bool itemCounter[4]);

	bool* getDialogControl();
	void setDialogControl(bool control[3]);

	Hero* getHero();

	void drawAllItems();
};

