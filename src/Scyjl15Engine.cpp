#include "header.h"
#include "Scyjl15Engine.h"
#include "ctime"

#include "Context.h"
#include "StartState.h"
#include "RunningState.h"

using namespace std;

Scyjl15Engine::Scyjl15Engine():BaseEngine() 
{

	edgePointsMap = FileUtils::getEdgePointsMap();
	// true means background music is playing, false means mute
	isPlaying = true;

}

Scyjl15Engine::~Scyjl15Engine()
{
	for each (auto pair in edgePointsMap)
	{
		FileUtils::clearPairsInVector(pair.second);
	}
}

void Scyjl15Engine::virtSetupBackgroundBuffer()
{
	m_Context->requestSetupBackgroundBuffer();
}

// draw dynamic word on the top of moving object
void Scyjl15Engine::virtDrawStringsOnTop()
{
	m_Context->requestDrawStringOnTop();
}

void Scyjl15Engine::virtKeyUp(int iKeyCode)
{
}

// mouse click listener
void Scyjl15Engine::virtMouseDown(int iButton, int iX, int iY)
{
	m_Context->requestMouseDown(iButton, iX, iY);

}



int Scyjl15Engine::virtInitialiseObjects()
{
	m_Context->requestInitialiseObjects();
	return 0;
}


void Scyjl15Engine::virtKeyDown(int iKeyCode)
{
	m_Context->requestKeyDown(iKeyCode);
	// player can press 'M' key to mute or replay the music
	// at any states
	if (iKeyCode == SDLK_m)
	{
		if (isPlaying)
		{
			stopAndCloseMusic("mainMusic");
			setIsPlaying(false);
		}
		else
		{
			playMusicLoop(mainMusicPath, "mainMusic");
			setIsPlaying(true);
		}
	}
}


void Scyjl15Engine::virtMainLoopDoBeforeUpdate()
{
	m_Context->requestMainLoopDoBeforeUpdate();

}
// set the update period of this engine in milliseconds
void Scyjl15Engine::setUpdatePeriod(int milliseconds)
{
	m_iDefaultUpdatePeriod = milliseconds;
}

void Scyjl15Engine::copyAllBackgroundBuffer()
{

	m_Context->requestCopyAllBackgroundBuffer();
}

void Scyjl15Engine::setBackgroundSurface(DrawingSurface* surface)
{
	m_pBackgroundSurface = surface;
}

/*
* get the edge points of characters based on character's name
*/
vector<DataPair<int, int>*> Scyjl15Engine::getEdgePointsByName(string name)
{
	return edgePointsMap[name];
}
// play music once
void Scyjl15Engine::playMusic(const std::string& musicFilePath, const std::string& alias)
{
	std::string openCommand = "open \"" + musicFilePath + "\" type mpegvideo alias " + alias;
	mciSendString(openCommand.c_str(), NULL, 0, NULL);


	std::string playCommand = "play " + alias;
	mciSendString(playCommand.c_str(), NULL, 0, NULL);

}

/*
* directly use the alias to play the music
*/
void Scyjl15Engine::playMusic(const std::string& alias)
{
	std::string playPath = "music/" + alias + ".wav";
	PlaySound(TEXT(playPath.c_str()), NULL, SND_FILENAME | SND_ASYNC);
}

/*
* load the music
*/
void Scyjl15Engine::loadMusic(const std::string& musicFilePath, const std::string& alias)
{
	std::string openCommand = "open \"" + musicFilePath + "\" type mpegvideo alias " + alias;
	mciSendString(openCommand.c_str(), NULL, 0, NULL);
}



/*
* keep playing one music
*/
void Scyjl15Engine::playMusicLoop(const std::string& musicFilePath, const std::string& alias)
{
	// open music file
	std::string openCommand = "open \"" + musicFilePath + "\" type mpegvideo alias " + alias;
	mciSendString(openCommand.c_str(), NULL, 0, NULL);

	// play the music in a loop
	std::string playCommand = "play " + alias + " repeat";
	mciSendString(playCommand.c_str(), NULL, 0, NULL);

}

// stop playing music
void Scyjl15Engine::stopAndCloseMusic(const std::string& alias)
{
	std::string stopCommand = "stop " + alias;
	std::string closeCommand = "close " + alias;
	mciSendString(stopCommand.c_str(), NULL, 0, NULL);
	mciSendString(closeCommand.c_str(), NULL, 0, NULL);

}

bool Scyjl15Engine::getIsPlaying()
{
	return isPlaying;
}

void Scyjl15Engine::setIsPlaying(bool playing)
{
	isPlaying = playing;
}

void Scyjl15Engine::virtMouseWheel(int x, int y, int which, int timestamp)
{
	m_Context->requestMouseWheel(x, y, which, timestamp);
}