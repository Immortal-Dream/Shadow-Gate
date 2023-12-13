#pragma once
#include "ItemTile.h"
class SmallEnergyTile :
    public ItemTile
{
public:
	SmallEnergyTile();
	virtual void  virtDrawTileAt(
		BaseEngine* pEngine,
		DrawingSurface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const override;
	void castEffect(Hero* hero) override;
};

