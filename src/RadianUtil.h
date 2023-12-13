#pragma once
/*
* util class used to manipulate Trigonometric functions
*/
class RadianUtil
{
public:
    const static int RIGHT = 0;
    const static int TOP_RIGHT = 45;
    const static int TOP = 90;
    const static int TOP_LEFT = 135;

    const static int LEFT = 180;
    const static int BOTTOM_LEFT = 225;
    const static int BOTTOM = 270;
    const static int BOTTOM_RIGHT = 315;

	static double convertDegreeToRadian(int degree);
	static int convertRadianToDegree(double radian);
	static double getRelativeRadian(int sourceX, int sourceY, int targetX, int targetY);
	static int getArea(int sourceX, int sourceY, int targetX, int targetY);
    static int getArea(double radian);
};

