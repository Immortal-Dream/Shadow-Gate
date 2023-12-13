#pragma once
#include "ItemTile.h"
class SmallMedicineTile
	: public ItemTile
{
public:
	SmallMedicineTile();
	virtual void  virtDrawTileAt(
		BaseEngine* pEngine,
		DrawingSurface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const override;
	void castEffect(Hero* hero) override;
};

