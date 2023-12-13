#pragma once
/*
* Roulette Wheel Selection to determine the AI monster to choose which direction to 
* move. It is a reinforcement learning AI method to make desicion, which is inpired by 
* Year2 AI method module.
* 
*  It is called roulette wheel selection because it works similarly to a roulette wheel,
*  where each individual's fitness value determines its position on the wheel. The 
*  probability of an individual being selected for reproduction is proportional to its
*  fitness value, so individuals with higher fitness values are more likely to be selected.
*/
#include "header.h"
#include <map>

using namespace std;
class RouletteWheelSelection
{

private:
    /*
    * map of radian and its score, radian represents the degrees of
    * character's moving direction. right is 0, left is pi.
    */
	map<int, int> directionScores;
    /*
    * initial score of choose the moving direction
    */
    const int INITIAL_SCORE = 8;
    /*
    * initial score of choose the moving direction
    */
    const int UPPER_BOUND = 15;
    /*
    * initial score of choose the moving direction
    */
    const int LOWER_BOUND = 1;

public:


	RouletteWheelSelection();
	~RouletteWheelSelection();

    map<int, int> getDirectinScores() {
        return directionScores;
    }
    void increaseScore(int direction);
    void decreaseScore(int direction);
    int getTotalScore();
    int selectDirection();
    void resetScore();
};

