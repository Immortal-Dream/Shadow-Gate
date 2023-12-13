#include "header.h"
#include "EnemyFactory.h"


Enemy* EnemyFactory::produceEnemy(string name, int screenX, int screenY)
{
	Enemy* enemy = nullptr;
	if (name == "Orc")
	{
		enemy = new Orc(engine, screenX, screenY, 70, 70);
	}
	else if (name == "Skeleton")
	{
		enemy = new Skeleton(engine, screenX, screenY, 75, 75);
	}
	else if (name == "Behemoth")
	{
		enemy = new Behemoth(engine, screenX, screenY, 100, 100);
	}
	else if (name == "Goblin")
	{
		enemy = new Goblin(engine, screenX, screenY, 75, 75);
	}
	else if (name == "Wizard")
	{
		enemy = new Wizard(engine, screenX, screenY, 124, 160);
	}
	return enemy;
}

/*
* produce specific number of enemies according to user's input
*/
void EnemyFactory::produceMultipleEnemies(string name, int number)
{
	for (int i = 0; i < number; i++)
	{
		// generate random x coordinate between 15 and 1200
		int randomX = rand() % (1200 - 15) + 15;
		// generate random y coordinate between 120 and 650
		int randomY = rand() % (600 - 120) + 120;
		Enemy* enemy = produceEnemy(name, randomX, randomY);
		engine->appendObjectToArray(enemy);
	}
}

