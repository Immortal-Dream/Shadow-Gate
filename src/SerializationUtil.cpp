#include "header.h"
#include "SerializationUtil.h"
#include "FileUtils.h"
#include "FireBullet.h"
#include "BossBullet.h"
#include "GoblinBullet.h"

void SerializationUtil::serialize(RunningState* runningState, BaseEngine* engine)
{

	string filePath = "data/Saved.csv";
	ofstream outfile;
	outfile.open(filePath);
	int episodeID = runningState->getEpisodeID();
	outfile << "episode,"  << episodeID << endl;
	outfile << "offset,"  << runningState->getOffset() << endl;
	outfile << "currentDialog," << runningState->getCurrentDialog() << endl;
	char displayTimeString[80];
	//sprintf(displayTimeString, "previousDisplayTime,%lld", runningState->getPreviousDisplayTime());
	outfile << "previousDisplayTime,"  << runningState->getPreviousDisplayTime() << endl;
	outfile << "score," << runningState->getScore() << endl;
	outfile << "isMoving," << runningState->isMoving << endl;
	outfile << "stages,";
	for (int i = 0; i < 4; i++)
	{
		outfile << runningState->getStages()[i];
		if (i != 3)
		{
			outfile << ",";
		}
	}
	outfile << endl;

	outfile << "itemCounter,";
	for (int i = 0; i < 4; i++)
	{
		outfile << runningState->itemCounter[i];
		if (i == 3)
		{
			outfile << endl;
		}
		else {
			outfile << ",";
		}
	}
	
	outfile << "isPassed," << runningState->getIsPassed() << endl;
	if (runningState->smallMedicine != nullptr && runningState->smallMedicine->isVisible())
	{
		outfile << "smallMedicine," << runningState->smallMedicine->getBaseX()
			<< "," << runningState->smallMedicine->getBaseY() << endl;
	}

	if (runningState->smallEnergy != nullptr && runningState->smallEnergy->isVisible())
	{
		outfile <<"smallEnergy," << runningState->smallEnergy->getBaseX() << ","
			<< runningState->smallEnergy->getBaseY() << endl;
	}
	if (runningState->largeMedicine != nullptr && runningState->largeMedicine->isVisible())
	{
		outfile << "largeMedicine," << runningState->largeMedicine->getBaseX() << ","
			<< runningState->largeMedicine->getBaseY() << endl;
	}
	if (runningState->largeEnergy != nullptr && runningState->largeEnergy->isVisible())
	{
		outfile << "largeEnergy," << runningState->largeEnergy->getBaseX() << ","
			<< runningState->largeEnergy->getBaseY() << endl;
	}

	Hero* hero = runningState->getHero();
	outfile << "hero," << hero->getDrawingRegionLeft() << ","
		<< hero->getDrawingRegionTop() << ","
		<< hero->getHP() << ","
		<< hero->getShield() << ","
		<< hero->getEnerge() << endl;
		
	// traverse all displable objects 
	DisplayableObject* displable;
	engine->bookmarkSetToLast();
	int lastIndex = engine->bookmarkGetCurrentIndex();
    for (int i = 0; i <= lastIndex; i++)
    {
        displable = engine->getDisplayableObject(i);
        // find the object itself or null ptr
        if (displable == nullptr) {
            continue;
        }
        Enemy* enemy = dynamic_cast<Enemy*>(displable);
        // this object is an enemy object
        if (enemy != nullptr)
        {
			outfile << enemy->getType() << ","
				<< enemy->getDrawingRegionLeft() << ","
				<< enemy->getDrawingRegionTop() << ","
				<< enemy->getHP() << endl;
        }

        Bullet* bullet = dynamic_cast<Bullet*>(displable);
        // If the displayable obejects are bullets
        if (bullet != nullptr)
        {
			outfile << bullet->getBulletName() << ","
				<< bullet->getDrawingRegionLeft() << ","
				<< bullet->getDrawingRegionTop() << ","
				<< bullet->getXCos() << ","
				<< bullet->getYSin() << endl;
        }
    }
	// if it is episode2, still need to save poison area's position.
	if (episodeID == 2)
	{
		Episode2State* eposido2 = dynamic_cast<Episode2State*>(runningState);
		if (eposido2->getPoisonTile()->isVisible())
		{
			outfile << "poisonTile," <<
				eposido2->getPoisonTile()->getBaseX() << ","
				<< eposido2->getPoisonTile()->getBaseY() << endl;
		}
	}
	outfile.close();
}

// read state data from csv file
RunningState* SerializationUtil::deserialize(BaseEngine* engine)
{
	RunningState* runningState = nullptr;
	string filePath = "data/Saved.csv";
	ifstream inputFile;
	inputFile.open(filePath);
	int episodeID = 0;
	string line;

	engine->drawableObjectsChanged();
	engine->destroyOldObjects(true);
	engine->createObjectArray(2);
	while (getline(inputFile, line))
	{

		vector<string> data = FileUtils::split(line, ",");
		// if there is noting in the file, start a new game
		if (data[0] == "")
		{
			break;
		}
		// the first line of the file will be episode's type
		if (data[0] == "episode")
		{
			if (data[1] == "1")
			{
				runningState = new Episode1State(engine);
				int episodeID = 1;
			}
			else if (data[1] == "2")
			{
				runningState = new Episode2State(engine, new Hero(engine));
				int episodeID = 2;
			}
			else if (data[1] == "3")
			{
				runningState = new Episode3State(engine, new Hero(engine));
				int episodeID = 3;
			}
		}
		if (data[0] == "offset")
		{
			runningState->setOffset(atoi(data[1].c_str()));
		}
		if (data[0] == "currentDialog")
		{
			runningState->setCurrentDialog(atoi(data[1].c_str()));
		}
		if (data[0] == "previousDisplayTime")
		{
			runningState->setPreviousDisplayTime(atoll(data[1].c_str()));
		}
		if (data[0] == "score")
		{
			runningState->setScore(atoi(data[1].c_str()));
		}
		if (data[0] == "isMoving")
		{
			runningState->isMoving = stoi(data[1]);
		}
		if (data[0] == "stages")
		{
			bool stageArray[4];
			for (int i = 0; i < 4; i++)
			{
				stageArray[i] = atoi(data[i+1].c_str());
			}
			runningState->setStages(stageArray);
		}
		if (data[0] == "isPassed")
		{
			runningState->setIsPassed(atoi(data[1].c_str()));
		}
		// game item tiles
		if (data[0] == "smallMedicine")
		{
			runningState->smallMedicine->
				setTopLeftPositionOnScreen(stoi(data[1]), stoi(data[2]));
		}
		if (data[0] == "smallEnergy")
		{
			runningState->smallEnergy->
				setTopLeftPositionOnScreen(stoi(data[1]), stoi(data[2]));
		}
		if (data[0] == "largeMedicine")
		{
			runningState->largeMedicine->
				setTopLeftPositionOnScreen(stoi(data[1]), stoi(data[2]));
		}
		if (data[0] == "largeEnergy")
		{
			runningState->largeEnergy->
				setTopLeftPositionOnScreen(stoi(data[1]), stoi(data[2]));
		}
		// hero
		if (data[0] == "hero")
		{
			Hero* hero = runningState->getHero();
			hero->setPosition
			(atoi(data[1].c_str()), atoi(data[2].c_str()));
			hero->setHP(atoi(data[3].c_str()));
			hero->setShield(atoi(data[4].c_str()));
			hero->setEnerge(atoi(data[5].c_str()));
			engine->storeObjectInArray(0, hero);
			engine->storeObjectInArray(1, hero->getWeapon());
		}
		if (data[0] == "itemCounter")
		{
			for (int i = 0; i < 4; i++)
			{
				runningState->itemCounter[i] = stoi(data[i + 1]);
			}
		}
		// monsters
		if (data[0] == "Orc")
		{
			Orc *orc = new Orc(engine, atoi(data[1].c_str()), 
				atoi(data[2].c_str()),70,70);
			orc->setHP(atoi(data[3].c_str()));
			engine->appendObjectToArray(orc);
		}
		if (data[0] == "Skeleton")
		{
			Skeleton* enemy = new Skeleton(engine, atoi(data[1].c_str()),
				atoi(data[2].c_str()), 75, 75);
			enemy->setHP(atoi(data[3].c_str()));
			engine->appendObjectToArray(enemy);
		}
		if (data[0] == "Goblin")
		{
			Goblin* enemy = new Goblin(engine, atoi(data[1].c_str()),
				atoi(data[2].c_str()), 75, 75);
			enemy->setHP(atoi(data[3].c_str()));
			engine->appendObjectToArray(enemy);
		}
		if (data[0] == "Behemoth")
		{
			Behemoth* enemy = new Behemoth(engine, atoi(data[1].c_str()),
				atoi(data[2].c_str()), 100, 100);
			enemy->setHP(atoi(data[3].c_str()));
			engine->appendObjectToArray(enemy);
		}
		if (data[0] == "Wizard")
		{
			Wizard* enemy = new Wizard(engine, atoi(data[1].c_str()),
				atoi(data[2].c_str()), 124, 160);
			enemy->setHP(atoi(data[3].c_str()));
			engine->appendObjectToArray(enemy);

		}
		// bullets
		if (data[0] == "HeroBullet")
		{
			HeroBullet* bullet = new HeroBullet
			(engine, atoi(data[1].c_str()), stoi(data[2]), 19, 19, "images/weapons/hero_bullet.png");
			engine->appendObjectToArray(bullet);
			bullet->setXCos(stod(data[3]));
			bullet->setYSin(stod(data[4]));
		}
		if (data[0] == "OrcBullet")
		{
			OrcBullet* bullet = new OrcBullet
			(engine, atoi(data[1].c_str()), stoi(data[2]), 21, 21);
			engine->appendObjectToArray(bullet);
			bullet->setXCos(stod(data[3]));
			bullet->setYSin(stod(data[4]));
		}
		if (data[0] == "FireBullet")
		{
			FireBullet* bullet = new FireBullet
			(engine, atoi(data[1].c_str()), stoi(data[2]), 45, 50);
			engine->appendObjectToArray(bullet);
			bullet->setXCos(stod(data[3]));
			bullet->setYSin(stod(data[4]));
		}
		if (data[0] == "BossBullet")
		{
			BossBullet* bullet = new BossBullet
			(engine, atoi(data[1].c_str()), stoi(data[2]), 22, 22);
			engine->appendObjectToArray(bullet);
			bullet->setXCos(stod(data[3]));
			bullet->setYSin(stod(data[4]));
		}
		if (data[0] == "GoblinBullet")
		{
			GoblinBullet* bullet = new GoblinBullet
			(engine, atoi(data[1].c_str()), stoi(data[2]), 22, 22);
			engine->appendObjectToArray(bullet);
			bullet->setXCos(stod(data[3]));
			bullet->setYSin(stod(data[4]));
		}
		if (data[0] == "poisonTile")
		{
			Episode2State* eposido2 = dynamic_cast<Episode2State*>(runningState);
			eposido2->getPoisonTile()->setTopLeftPositionOnScreen(stoi(data[1]), stoi(data[2]));
			eposido2->getPoisonTile()->displayPoison(engine);
		}



	}
	return runningState;
}
