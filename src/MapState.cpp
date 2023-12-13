#include "header.h"
#include "MapState.h"
#include "Scyjl15Engine.h"
#include "StartState.h"
MapState::MapState(BaseEngine* engine) :State(engine)
 ,m_filterScaling(0, 0, engine), m_filterTranslation(0, 0, &m_filterScaling)
{

	m_Engine->getBackgroundSurface()->setDrawPointsFilter(&m_filterTranslation);
	m_Engine->getForegroundSurface()->setDrawPointsFilter(&m_filterTranslation);
}

MapState::~MapState()
{
	m_Engine->getBackgroundSurface()->setDrawPointsFilter(nullptr);
	m_Engine->getForegroundSurface()->setDrawPointsFilter(nullptr);

}


void MapState::handleSetupBackgroundBuffer()
{
	m_Engine->fillBackground(0x000000);
	SimpleImage mapBackground = ImageManager::loadImage("images/backgrounds/Dark.png", true);

	mapBackground.renderImage(m_Engine->getBackgroundSurface(), 0, 0, 0, 0
		, mapBackground.getWidth(), mapBackground.getHeight());

	SimpleImage hints = ImageManager::loadImage("images/backgrounds/ReturnHints.png", true);

	hints.renderImage(m_Engine->getBackgroundSurface(), 0, 0, 0, 0
		, hints.getWidth(), hints.getHeight());
}

void MapState::handleMainLoopDoBeforeUpdate()
{

}

void MapState::handleCopyAllBackgroundBuffer()
{
	m_Engine->getForegroundSurface()->copyEntireSurface(m_Engine->getBackgroundSurface());
}

int MapState::handleInitialiseObjects()
{
	m_Engine->drawableObjectsChanged();

	m_Engine->destroyOldObjects(true);

	m_Engine->createObjectArray(1);

	m_Engine->storeObjectInArray(0, new DragableImageObject(600, 425, m_Engine, "images/backgrounds/Map.png", false));
	return 0;
}

void MapState::handleKeyDown(int keyCode)
{
	// press escape key to return to home screen
	if (keyCode == SDLK_ESCAPE)
	{
		Scyjl15Engine* scyjl15Engine = dynamic_cast<Scyjl15Engine*>(m_Engine);
		State* start = new StartState(m_Engine);
		scyjl15Engine->m_Context->changeState(start, m_Engine);
	}
}

void MapState::handleMouseDown(int iButton, int iX, int iY)
{
	printf("Map: (%d, %d)\n", iX, iY);
}

void MapState::handleMouseWheel(int x, int y, int which, int timestamp)
{
	// mouse wheel moves down and press left 'Ctrl' key:zoom out 
	if (y < 0 && m_Engine->isKeyPressed(SDLK_LCTRL))
		m_filterScaling.compress();
	// mouse wheel moves up and press left 'Ctrl' key: zoom in
	else if (y > 0 && m_Engine->isKeyPressed(SDLK_LCTRL))
		m_filterScaling.stretch();
	m_Engine->redrawDisplay(); // Force total redraw
}

