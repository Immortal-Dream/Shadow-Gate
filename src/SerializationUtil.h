#pragma once
// this class is used to save the current state to file
#include "Episode1State.h"
#include "Episode2State.h"
#include "Episode3State.h"
#include <fstream>
#include <map>

using namespace std;

class SerializationUtil
{

public:
	// save the data of a running state to file
	void serialize(RunningState* runningState, BaseEngine* engine);
	// read the state's data from csv file
	RunningState* deserialize(BaseEngine* engine);
};

