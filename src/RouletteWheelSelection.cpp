#include "header.h"
#include "RouletteWheelSelection.h"

/*
* initialise the directions and corresponding scores 
*/
RouletteWheelSelection::RouletteWheelSelection()
{
    for (int i = 0; i < 8; i++)
    {
        directionScores.insert(pair<int, int>(i * 45, INITIAL_SCORE));
    }

}

RouletteWheelSelection::~RouletteWheelSelection()
{
    
}



/*
* increase the score by 1
*/
void RouletteWheelSelection::increaseScore(int direction)
{
    // get the score
    int score = directionScores[direction];
    if (score < UPPER_BOUND)
    {
        directionScores[direction] = score + 1;
    }
}

/*
* decrease the score by 1
*/
void RouletteWheelSelection::decreaseScore(int direction)
{
    int score = directionScores[direction];
    if (score > LOWER_BOUND)
    {
        directionScores[direction] = score + 1;
    }
}

int RouletteWheelSelection::getTotalScore()
{
    int total = 0;
    map<int, int>::iterator iter;
    iter = directionScores.begin();
    while (iter != directionScores.end())
    {
        total += iter->second;
        iter++;
    }
    return total;
}
/*
* choose the direction to move, the direction with higher score will has 
* higher probability to be chosen
*/
int RouletteWheelSelection::selectDirection()
{

    int total = getTotalScore();
    // generate a int value belons to [0,total)
    int value = rand() % total;
    int cumulativeScore = 0;
    map<int, int>::iterator iter;
    iter = directionScores.begin();
    cumulativeScore += iter->second;

    while (cumulativeScore < value) {
        iter++;
        cumulativeScore += iter->second;
    }

    return iter->first;
}
/*
* reset all scores to initial score
*/
void RouletteWheelSelection::resetScore()
{
    for (int i = 0; i < 8; i++)
    {
        directionScores[i * 45] = INITIAL_SCORE;
    }
}
