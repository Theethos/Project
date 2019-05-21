#pragma once

#include "EventManager.h"

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
	static sf::RenderWindow Window;
	static sf::ContextSettings Settings;
	static bool IsInstantiated, IsRunning;
	static unsigned Width, Height, FpsCap;

	DisplayManager() = delete;
	~DisplayManager() = delete;

	friend EventManager;
};

