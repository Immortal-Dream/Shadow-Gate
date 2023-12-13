#pragma once
#include "BaseEngine.h"
#include "Enemy.h"
#include "Orc.h"
#include "Skeleton.h"
#include "Behemoth.h"
#include "Goblin.h"
#include "Wizard.h"
#include <string>
using namespace std;
class EnemyFactory
{
private:
	BaseEngine* engine;
public:
	EnemyFactory(BaseEngine* baseEngine):engine(baseEngine){}
	Enemy* produceEnemy(string name, int screenX, int screenY);
	void produceMultipleEnemies(string name, int number);
};

