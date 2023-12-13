#include "header.h"
#include "ItemTile.h"

ItemTile::ItemTile(int height, int width) : TileManager(height, width, 2, 1)
{
    value = 0;
    setTopLeftPositionOnScreen(0, 0);
    setMapValue(0, 0, 0);
    setMapValue(1, 0, 0);
    visible = false;
}


bool ItemTile::isVisible()
{
    return visible;
}

void ItemTile::setVisible(bool visible)
{
    this->visible = visible;
}

void ItemTile::hideItem(BaseEngine* engine)
{
    this->visible = false;
    setMapValue(0, 0, 0);
    setMapValue(1, 0, 0);
    // hide tiles
    engine->lockBackgroundForDrawing();
    drawAllTiles(engine, engine->getBackgroundSurface());
    engine->virtSetupBackgroundBuffer();
    engine->unlockBackgroundForDrawing();
    setTopLeftPositionOnScreen(0, 0);
}

void ItemTile::enableItem(int x, int y, BaseEngine* engine)
{
    setMapValue(0, 0, 1);
    setMapValue(1, 0, 2);
    this->visible = true;
    setTopLeftPositionOnScreen(x, y);
    // display tiles
    engine->lockBackgroundForDrawing();
    drawAllTiles(engine, engine->getBackgroundSurface());
    engine->virtSetupBackgroundBuffer();
    engine->unlockBackgroundForDrawing();
}

/*
* display the item in random place in the screen
*/
void ItemTile::enableItem(BaseEngine* engine)
{
    this->visible = true;
    setMapValue(0, 0, 1);
    setMapValue(1, 0, 2);
    int x = rand() % (1200 - 50) + 50;
    int y = rand() % (630 - 200) + 200;

    setTopLeftPositionOnScreen(x, y);
    // display tiles
    engine->lockBackgroundForDrawing();
    drawAllTiles(engine, engine->getBackgroundSurface());
    engine->virtSetupBackgroundBuffer();
    engine->unlockBackgroundForDrawing();
}

int ItemTile::getValue()
{
    return value;
}

// apply effect of this item to hero
void ItemTile::castEffect(Hero* hero)
{
}

void ItemTile::virtDrawTileAt(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY, int iStartPositionScreenX, int iStartPositionScreenY) const
{
}

int ItemTile::getBaseX()
{
    return m_iBaseScreenX;
}

int ItemTile::getBaseY()
{
    return m_iBaseScreenY;
}

