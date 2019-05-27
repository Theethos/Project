#pragma once

class InputManager;

////////////////////////////////////////////////////////////
/// \brief Static class that manages the window display 
///
////////////////////////////////////////////////////////////

class DisplayManager
{
public:
	static void Create(unsigned w = 800, unsigned h = 600);
	static void StartLoop();
	static void EndLoop();
	static void Destroy();
	inline static bool ShouldBeRunning() { return DisplayManager::IsRunning; }

	inline static const unsigned & GetWidth() { return Width; }
	inline static const unsigned & GetHeight() { return Height; }
	inline static const glm::vec4 & GetClearColor() { return ClearColor; }

private:
	static SDL_Window * Window;
	static SDL_GLContext Settings;
	static bool IsInstantiated, IsRunning;
	static unsigned Width, Height;
	static float FpsCap;
	static Uint32 StartTime, DeltaTime;
	static glm::vec4 ClearColor;

	DisplayManager() = delete;
	~DisplayManager() = delete;

	friend InputManager;
};

