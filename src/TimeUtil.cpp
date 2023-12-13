#include "header.h"
#include "TimeUtil.h"
TimeUtil::TimeUtil() {}

// get current system time in miLliseconds
long long TimeUtil::getCurrentTime()
{
	// get current time
	auto now = chrono::system_clock::now();
	// transfer current time to miLliseconds
	long long now_ms = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()).count();

	return now_ms;
}

long long TimeUtil::getTimeInterval(long long currentTime, long long previousTime)
{
	return currentTime - previousTime;
}


