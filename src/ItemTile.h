#pragma once
#include "TileManager.h"
#include "ImageManager.h"
#include "Hero.h"
/*
* Parent class of all game items such as hp recovery medicine and energy
* recovery item
*/
class ItemTile :
    public TileManager
{
protected:
    int value;
    bool visible;
    SimpleImage image;
    SimpleImage image2;
public:
    ItemTile(int width, int height);

    bool isVisible();
    void setVisible(bool visible);
    void hideItem(BaseEngine* engine);
    void enableItem(int x, int y,BaseEngine* engine);
    void enableItem(BaseEngine* engine);
    int getValue();
    virtual void castEffect(Hero* hero);
    virtual void  virtDrawTileAt(
        BaseEngine* pEngine,
        DrawingSurface* pSurface,
        int iMapX, int iMapY,
        int iStartPositionScreenX, int iStartPositionScreenY) const override;
    int getBaseX();
    int getBaseY();
};

