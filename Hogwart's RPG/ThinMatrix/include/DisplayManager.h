#pragma once

class InputManager;

////////////////////////////////////////////////////////////
/// \brief Static class that manages the window display 
///
////////////////////////////////////////////////////////////

class DisplayManager
{
public:
	static void Create(unsigned w = 1920, unsigned h = 1080, const bool & fullscreen = false);
	static void StartLoop();
	static void EndLoop();
	static void Destroy();
	inline static bool ShouldBeRunning() { return DisplayManager::IsRunning; }

	inline static const unsigned & GetWidth() { return Width; }
	inline static const unsigned & GetHeight() { return Height; }
	inline static const glm::vec4 & GetClearColor() { return ClearColor; }
	inline static const glm::mat4 & GetProjectionMatrix() { return ProjectionMatrix; }
	inline static const double & GetDeltaTime() { return (double)DeltaTime / 1000.f; }

private:
	static SDL_Window * Window;
	static SDL_GLContext Settings;
	static bool IsInstantiated, IsRunning;
	static unsigned Width, Height;
	static float FpsCap;
	static Uint32 StartTime, DeltaTime;
	static glm::vec4 ClearColor;

	// Projection matrix
	static glm::mat4 ProjectionMatrix;
	static double Fov, AspectRatio, Near, Far;

	DisplayManager() = delete;
	~DisplayManager() = delete;

	friend InputManager;
};

