#pragma once

#include "InputManager.h"

////////////////////////////////////////////////////////////
/// \brief Static class that manages the window display 
///
////////////////////////////////////////////////////////////

class DisplayManager
{
public:
	static void Create(unsigned w = 800, unsigned h = 600);
	static void Clear();
	static void Display();
	static void Destroy();
	inline static bool ShouldBeRunning() { return DisplayManager::IsRunning; }

	static glm::mat4 Projection;	// 3D --> 2D
	static glm::mat4 ModelView;		// Toutes les transformations
private:
	static SDL_Window * Window;
	static SDL_GLContext Settings;
	static bool IsInstantiated, IsRunning;
	static unsigned Width, Height;
	static float FpsCap;
	static Uint32 StartTime, DeltaTime;
	static glm::vec3 Eyes, Center, Axe;

	DisplayManager() = delete;
	~DisplayManager() = delete;

	friend InputManager;
};

