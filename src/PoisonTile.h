#pragma once
#include "TileManager.h"

class PoisonTile :
    public TileManager
{
private:
	bool visible;
	const int COLUMNS = 35;
	const int ROWS = 35;
	long long lastPoisonedTime;
	// time interval of get hurt by poison, in milliseconds
	int poisonInterval;
	// damage caused by poison
	int damage;
public:
    PoisonTile();
	virtual void  virtDrawTileAt(
		BaseEngine* pEngine,
		DrawingSurface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const override;
	bool isVisible();
	void setVisible(bool visible);

	void setLastPoisonedTime(long long time);
	long long getLastPoisonedTime();
	int getPoisonInterval();
	void hideAllTiles(BaseEngine* engine);
	int getDamage();
	void displayPoison(BaseEngine* engine);
	int getBaseX();
	int getBaseY();
};

