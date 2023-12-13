#pragma once
#include "ItemTile.h"
class LargeMedicineTile :
    public ItemTile
{
public:
	LargeMedicineTile();
	virtual void  virtDrawTileAt(
		BaseEngine* pEngine,
		DrawingSurface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const override;
	void castEffect(Hero* hero) override;
};

