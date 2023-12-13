#include "header.h"
#include "PoisonTile.h"

PoisonTile::PoisonTile() : TileManager(5, 5, 35, 35)
{
	damage = 1;
	this->visible = false;
	setTopLeftPositionOnScreen(0, 0);
	for (int x = 0; x < COLUMNS; x++)
	{
		for (int y = 0; y < ROWS; y++)
		{
			setMapValue(x, y, 0);
		}
	}
	lastPoisonedTime = 0;
	poisonInterval = 2000;

}
void PoisonTile::virtDrawTileAt(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY, int iStartPositionScreenX, int iStartPositionScreenY) const
{
	int greenColorArray[3] = {0x07c954, 0x20ce65, 0x06b54c};
	int mapValue = getMapValue(iMapX, iMapY);
	// draw the tile only when map value is 1
	if (mapValue == 1)
	{
		int randomNumber = rand() % 3;
		pSurface->drawRectangle(
			iStartPositionScreenX,
			iStartPositionScreenY,
			iStartPositionScreenX + getTileWidth() - 1,
			iStartPositionScreenY + getTileHeight() - 1,
			greenColorArray[randomNumber]);
	} 
}

bool PoisonTile::isVisible()
{
	return visible;
}

void PoisonTile::setVisible(bool visible)
{
	this->visible = visible;
}

void PoisonTile::setLastPoisonedTime(long long time)
{
	lastPoisonedTime = time;
}

long long PoisonTile::getLastPoisonedTime()
{
	return lastPoisonedTime;
}

int PoisonTile::getPoisonInterval()
{
	return poisonInterval;
}

/*
* hide all tiles by setting all tiles to 0
*/
void PoisonTile::hideAllTiles(BaseEngine* engine)
{
	this->visible = false;
	for (int x = 0; x < COLUMNS; x++)
	{
		for (int y = 0; y < ROWS; y++)
		{
			setMapValue(x, y, 0);
		}
	}
	// hide tiles
	engine->lockBackgroundForDrawing();
	drawAllTiles(engine, engine->getBackgroundSurface());
	engine->virtSetupBackgroundBuffer();
	engine->unlockBackgroundForDrawing();
}

int PoisonTile::getDamage()
{
	return damage;
}

void PoisonTile::displayPoison(BaseEngine* engine)
{
	this->visible = true;
	int x = rand() % (1200 - 50) + 50;
	int y = rand() % (630 - 200) + 200;

	setTopLeftPositionOnScreen(x, y);

	for (int x = 0; x < COLUMNS; x++)
	{
		for (int y = 0; y < ROWS; y++)
		{
			if ((x <= 15 && x >= 5) && (y <= 15 && y >= 5))
			{
				setMapValue(x, y, 1);
			}
			else {
				double randomDouble = rand() / double(RAND_MAX);
				if (randomDouble < 0.7)
				{
					setMapValue(x, y, 1);
				}
				else {
					setMapValue(x, y, 0);
				}
			}
		}
	}


	// display tiles
	engine->lockBackgroundForDrawing();
	drawAllTiles(engine, engine->getBackgroundSurface());
	engine->virtSetupBackgroundBuffer();
	engine->unlockBackgroundForDrawing();
}

int PoisonTile::getBaseX()
{
	return m_iBaseScreenX;
}

int PoisonTile::getBaseY()
{
	return m_iBaseScreenY;
}

