#pragma once
#include "ItemTile.h"
class LargeEnergyTile :
    public ItemTile
{
public:
	LargeEnergyTile();
	virtual void  virtDrawTileAt(
		BaseEngine* pEngine,
		DrawingSurface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const override;
	void castEffect(Hero* hero) override;
};

