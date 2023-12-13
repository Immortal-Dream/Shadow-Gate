#pragma once
#include "header.h"
#include <vector>
#include <memory>
#include "Character.h"
#include "Bullet.h"
#include "DataPair.h"
#include "TileManager.h"
using namespace std;
class CollisionUtil
{
	
public:
	static bool pointInCircle(int centreX, int centreY, int pointX, int pointY, int radius);
	static bool pointInRectangle(int leftTopX, int leftTopY, int width, int height, int pointX, int pointY);
	static bool pixelPerfectDetection(Character *character, Bullet *bullet);
	static bool pixelPerfectDetection(Character* character, TileManager* tileManager);
	static bool pixelPerfectDetection(Character* character, shared_ptr<TileManager> tileManager);
};

