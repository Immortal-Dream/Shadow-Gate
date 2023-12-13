#pragma once
#include <chrono>
using namespace std;
class TimeUtil
{
private:
	TimeUtil(); // private constructor to prevent direct instantiation
public:
	static long long getCurrentTime();
	static long long getTimeInterval(long long currentTime, long long previousTime);
};

