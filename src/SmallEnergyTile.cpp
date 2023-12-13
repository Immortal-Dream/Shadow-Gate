#include "header.h"
#include "SmallEnergyTile.h"

SmallEnergyTile::SmallEnergyTile() : ItemTile(60, 30)
{
	value = 100;
	image = ImageManager::loadImage("images/elements/SmallEnergy1.png", true);
	image2 = ImageManager::loadImage("images/elements/SmallEnergy2.png", true);
}

void SmallEnergyTile::virtDrawTileAt(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY, int iStartPositionScreenX, int iStartPositionScreenY) const
{
	// draw the tile only when map value is not 0
	int mapValue = getMapValue(iMapX, iMapY);
	if (mapValue == 1)
	{
		image.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX,
			iStartPositionScreenY, 30, 60);
	}
	if (mapValue == 2)
	{
		image2.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX,
			iStartPositionScreenY, 30, 60);
	}
		
}

void SmallEnergyTile::castEffect(Hero* hero)
{
	hero->setEnerge(min(hero->getEnerge() + value, hero->getMaximumEnerge()));
	// hide the item after applying the effect to hero
	hideItem(hero->getEngine());
}
