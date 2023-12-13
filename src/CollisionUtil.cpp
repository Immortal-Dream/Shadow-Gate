#include "header.h"
#include "CollisionUtil.h"

/*
* judge whether a point is in a circle
*/
bool CollisionUtil::pointInCircle(int centreX, int centreY, int pointX, int pointY, int radius)
{
	return (pow(centreX-pointX,2) + pow(centreY-pointY,2) < pow(radius,2));
}

bool CollisionUtil::pointInRectangle(int leftTopX, int leftTopY, int width, int height, int pointX, int pointY)
{
	return (pointX >= leftTopX) && (pointX <= leftTopX+width)&&
		(pointY >= leftTopY) && (pointY <= leftTopY + height);
}

/*
* pixel perfect collition detection between bullet and character using a vector
* of edge points of the character
*/
bool CollisionUtil::pixelPerfectDetection(Character* character, Bullet* bullet)
{
	bool isCollition = false;
	int characterX = character->getDrawingRegionLeft();
	int characterY = character->getDrawingRegionTop();

	int bulletXCentre = bullet->getXCentre();
	int bulletYCentre = bullet->getYCentre();
	int radius = (bullet->getDrawingRegionTop() - bullet->getDrawingRegionBottom()) / 2;
	vector<DataPair<int, int>*> edgePoints = character->getEdgePoints();

	for (int i = 0; i < edgePoints.size(); i++)
	{
		if (pointInCircle(bulletXCentre, bulletYCentre, characterX+edgePoints[i]->getFirst(),
			characterY+edgePoints[i]->getSecond(),radius))
		{
			isCollition = true;
			break;
		}
	}
	return isCollition;
}

/*
* detect the collition between tile manager and 
*/
bool CollisionUtil::pixelPerfectDetection(Character* character, TileManager* tileManager)
{
	int characterX = character->getDrawingRegionLeft();
	int characterY = character->getDrawingRegionTop();
	bool isCollition = false;
	vector<DataPair<int, int>*> edgePoints = character->getEdgePoints();
	for (int i = 0; i < edgePoints.size(); i++)
	{
		if (tileManager->isValidTilePosition(characterX+edgePoints[i]->getFirst(),
			characterY+ edgePoints[i]->getSecond()))
		{
			isCollition = true;
			break;
		}
	}
	return isCollition;
}

bool CollisionUtil::pixelPerfectDetection(Character* character, shared_ptr<TileManager> tileManager)
{
	int characterX = character->getDrawingRegionLeft();
	int characterY = character->getDrawingRegionTop();
	bool isCollition = false;
	vector<DataPair<int, int>*> edgePoints = character->getEdgePoints();
	for (int i = 0; i < edgePoints.size(); i++)
	{
		if (tileManager->isValidTilePosition(characterX + edgePoints[i]->getFirst(),
			characterY + edgePoints[i]->getSecond()))
		{
			isCollition = true;
			break;
		}
	}
	return isCollition;
}
