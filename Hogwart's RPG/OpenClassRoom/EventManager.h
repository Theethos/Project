#pragma once

////////////////////////////////////////////////////////////
/// \brief Static class that manages the game events
///
////////////////////////////////////////////////////////////
class EventManager
{
public:
	static void Create();
	static void Update();
	static void Destroy();

private:
	static bool IsInstantiated;
	static SDL_Event Event;

	EventManager() = delete;
	~EventManager() = delete;
};

