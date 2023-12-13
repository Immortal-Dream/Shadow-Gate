#include "header.h"
#include "LargeEnergyTile.h"

LargeEnergyTile::LargeEnergyTile() : ItemTile(80, 40)
{
	value = 200;
	image = ImageManager::loadImage("images/elements/LargeEnergy1.png", true);
	image2 = ImageManager::loadImage("images/elements/LargeEnergy2.png", true);

}

void LargeEnergyTile::virtDrawTileAt(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY, int iStartPositionScreenX, int iStartPositionScreenY) const
{
	// draw the tile only when map value is not 0
	int mapValue = getMapValue(iMapX, iMapY);
	if (mapValue == 1)
	{
		image.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX,
			iStartPositionScreenY, 40, 80);
	}
	if (mapValue == 2)
	{
		image2.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX,
			iStartPositionScreenY, 40, 80);
	}
}

void LargeEnergyTile::castEffect(Hero* hero)
{
	hero->setEnerge(min(hero->getEnerge() + value, hero->getMaximumEnerge()));
	// hide the item after applying the effect to hero
	hideItem(hero->getEngine());
}
