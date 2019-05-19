#pragma once

#include "EventManager.h"

////////////////////////////////////////////////////////////
/// \brief Static class that manages the window display 
///
////////////////////////////////////////////////////////////
class DisplayManager
{
public:
	static void Create(unsigned w = 1280, unsigned h = 720);
	static void Update();
	static void Destroy();

	inline static bool ShouldBeRunning() { return DisplayManager::IsRunning; }
private:
	static SDL_Window * Window;
	static SDL_GLContext Settings;
	static bool IsInstantiated, IsRunning;
	static unsigned Width, Height, FpsCap;
	
	DisplayManager();
	~DisplayManager();

	friend EventManager;
};

