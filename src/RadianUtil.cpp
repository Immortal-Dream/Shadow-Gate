#include "header.h"
#include "RadianUtil.h"
double RadianUtil::convertDegreeToRadian(int degree)
{
    return (2 * M_PI) * degree / 360;
}

int RadianUtil::convertRadianToDegree(double radian)
{
    int degree = (int)(360 * radian / (2 * M_PI));
    return degree;
}
/*
* Assuming that (sourceX, sourceY) serves as the origin, this function determines the radian 
* value of the angle included between the line that connects (targetX, targetY) and 
* (sourceX, sourceY) and the positive x-axis.
*/
double RadianUtil::getRelativeRadian(int sourceX, int sourceY, int targetX, int targetY)
{
    double radian = 0.0;
	double opposite = targetY - sourceY;
	double adjacent = targetX - sourceX;
	double hypotenuse = sqrt(opposite * opposite + adjacent * adjacent);
	radian = acos(adjacent / hypotenuse);
	// target coordinate is on the third or fourth quadrant 
	if (targetY > sourceY)
	{
		radian = 2 * M_PI - radian;
	}
	return radian;
}
/*
* Assuming that (sourceX, sourceY) serves as the origin, coordinate system can be divided
* into eight areas. RIGHT Area [0,45) -> 0; TOP_RIGHT Area [45,90) -> 45
* TOP Area [90,135) -> 90; TOP_LEFT Area [135,180) ->  135
* LEFT Area [180,225) -> 180; BOTTOM_LEFT Area [225,270) -> 225
* BOTTOM Area [270,315) -> 270; BOTTOM_RIGHT Area [315,360) -> 315
* 
* This process involves the conversion from double to int
*/ 
int RadianUtil::getArea(int sourceX, int sourceY, int targetX, int targetY)
{
	double radian = getRelativeRadian(sourceX, sourceY, targetX, targetY);
	int area = floor(radian / (M_PI / 4)) * 45;
    return area;
}

int RadianUtil::getArea(double radian)
{
	int area = floor(radian / (M_PI / 4)) * 45;
	return area;
}
