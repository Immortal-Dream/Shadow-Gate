#include "header.h"
#include "StartState.h"
#include "RunningState.h"
#include "SettingState.h"
#include "StoryState.h"
#include "MapState.h"
#include "Scyjl15Engine.h"
#include <memory>

StartState::StartState(BaseEngine* engine) : State(engine) 
{
	previousSurface = engine->getBackgroundSurface();
	lastDisplayTime = 0;
	backgroundIndex = 0;
	gameSettings = FileUtils::readFromFile("data/game_setting.txt");
	DrawingSurface* surface;
	// create 8 Drawing surfaces
	for (int i = 0; i < 8; i++)
	{
		surface = new DrawingSurface(m_Engine);
		surfaceVector.push_back(surface);
		surfaceVector[i]->createSurface(1300, 800);

	}
	caveatFont = m_Engine->getFont("resources/Caveat-SemiBold.ttf", 38);
};
StartState::~StartState() 
{
	for (int i = 0; i < 8; i++)
	{
		delete surfaceVector[i];
		surfaceVector[i] = nullptr;
	}	
	// give the engine a new background surface
	Scyjl15Engine* scyjl15Engine = dynamic_cast<Scyjl15Engine*>(m_Engine);
	scyjl15Engine->setBackgroundSurface(previousSurface);
	
}
void StartState::handleSetupBackgroundBuffer()
{
	
	for (int i = 0; i < 5; i++)
	{
		// lock the surfaces
		surfaceVector[i]->mySDLLockSurface();
		char path[50];
		sprintf(path, "images/backgrounds/Menu%d.png", i + 1);
		// load corresponding images
		SimpleImage menu = ImageManager::loadImage(path, true);
		menu.renderImage(surfaceVector[i], 0, 0, 0, 0,
			menu.getWidth(), menu.getHeight());
		// unlock the surface
		surfaceVector[i]->mySDLUnlockSurface();
	}
}

void StartState::handleMouseDown(int iButton, int iX, int iY)
{
	printf("Start:( %d , %d )\n", iX, iY);
	
	// down cast BaseEngine to Scyjl15Engine
	Scyjl15Engine* scyjl15Engine = dynamic_cast<Scyjl15Engine*>(m_Engine);
	// user click the begin button
	if (checkBeginButton(iX, iY))
	{
		State* story = new StoryState(m_Engine);
		scyjl15Engine->m_Context->changeState(story,m_Engine);
	}
	// user click the setting button
	if (checkSettingButton(iX, iY))
	{
		State* setting = new SettingState(m_Engine);
		scyjl15Engine->m_Context->changeState(setting, m_Engine);
	}
	// user click the map button
	if (checkMapButton(iX, iY))
	{
		State* mapState = new MapState(m_Engine);
		scyjl15Engine->m_Context->changeState(mapState, m_Engine);
	}
	// user click the exit button
	if (checkExitButton(iX,iY))
	{
		exit(0);
	}
	

}

int StartState::handleInitialiseObjects()
{
	m_Engine->drawableObjectsChanged();

	m_Engine->destroyOldObjects(true);

	return 0;
}

void StartState::handleDrawStringOnTop()
{
	// draw the welcome string
	char firstLine[50];
	sprintf(firstLine, "Hi, %s!", gameSettings["player name"].c_str());
	char secondLine[50] = "Are you ready for an adventure?";
	m_Engine->drawForegroundString(577, 675, firstLine, 0xbababa, caveatFont);
	m_Engine->drawBackgroundString(470, 728, secondLine, 0xbababa, caveatFont);
}

void StartState::handleMainLoopDoBeforeUpdate()
{
	if ((TimeUtil::getCurrentTime()-lastDisplayTime) > animationInterval)
	{
		lastDisplayTime = TimeUtil::getCurrentTime();
		backgroundIndex = (backgroundIndex + 1) % 8;
		Scyjl15Engine* scyjl15Engine = dynamic_cast<Scyjl15Engine*>(m_Engine);
		scyjl15Engine->setBackgroundSurface(surfaceVector[backgroundIndex]);
		scyjl15Engine->redrawDisplay();
	}

}


/*
	check whether the user click the begin button
*/
bool StartState::checkBeginButton(int x, int y) {
	return checkClick(x, y, 538, 793, 462, 531);
}

bool StartState::checkExitButton(int x, int y) {
	return checkClick(x,y,30,170,38,80);
}

bool StartState::checkSettingButton(int x, int y) {
	return checkClick(x, y, 1182, 1272, 21, 94);
}

bool StartState::checkMapButton(int x, int y)
{
	return checkClick(x, y, 30, 123, 721, 760);
}
