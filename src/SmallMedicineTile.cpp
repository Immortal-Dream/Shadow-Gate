#include "header.h"
#include "SmallMedicineTile.h"

SmallMedicineTile::SmallMedicineTile() : ItemTile(60,30)
{
	value = 2;
	image = ImageManager::loadImage("images/elements/SmallMedicine1.png", true);
	image2 = ImageManager::loadImage("images/elements/SmallMedicine2.png", true);
}

void SmallMedicineTile::virtDrawTileAt(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY, int iStartPositionScreenX, int iStartPositionScreenY) const
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

/*
* hero will increase 2 hp
*/
void SmallMedicineTile::castEffect(Hero* hero)
{

	hero->setHP(min(hero->getHP() + value, hero->getMaximumHP()));
	// hide the item after applying the effect to hero
	hideItem(hero->getEngine());

}
