#include "header.h"
#include "LargeMedicineTile.h"

LargeMedicineTile::LargeMedicineTile(): ItemTile(80, 40)
{
	value = 4;
	image = ImageManager::loadImage("images/elements/LargeMedicine1.png", true);
	image2 = ImageManager::loadImage("images/elements/LargeMedicine2.png", true);
}

void LargeMedicineTile::virtDrawTileAt(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY, int iStartPositionScreenX, int iStartPositionScreenY) const
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
/*
* hero will increase 4 hp
*/
void LargeMedicineTile::castEffect(Hero* hero)
{
	hero->setHP(min(hero->getHP() + 4, hero->getMaximumHP()));
	// hide the item after applying the effect to hero
	hideItem(hero->getEngine());
}
