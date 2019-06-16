#pragma once

class InputManager;

////////////////////////////////////////////////////////////
/// \brief Static class that manages the window display 
///
////////////////////////////////////////////////////////////

class DisplayManager
{
public:
	static void Create(unsigned w = 0, unsigned h = 0, const bool & fullscreen = true);
	static void StartLoop();
	static void EndLoop();
	static void Destroy();
	static void ToggleModes();

	inline static bool ShouldBeRunning() { return DisplayManager::IsRunning; }
	inline static const unsigned & GetWidth() { return Width; }
	inline static const unsigned & GetHeight() { return Height; }
	inline static const glm::vec4 & GetDayClearColor() { return DayClearColor; }
	inline static const glm::vec4 & GetNightClearColor() { return NightClearColor; }
	inline static const glm::vec4 & GetFogColor() { return FogColor; }
	inline static const glm::mat4 & GetProjectionMatrix() { return ProjectionMatrix; }
	inline static const double & GetFrameTime() { return (double)FpsCap / 1000.f; }
	inline static const double & GetDeltaTime() { return (double)DeltaTime / 1000.f; }
	inline static const double & GetTime() { return Time; }
	inline static const double & GetFov() { return Fov; }
	inline static const double & GetFar() { return Far; }
	inline static const double & GetNear() { return Near; }
	inline static const float & GetBlendFactor() { return BlendFactor; }

	inline static void SetFov(const double & value) { Fov = value; ProjectionMatrix = glm::perspective(glm::radians(Fov), AspectRatio, Near, Far); }

private:
	static SDL_Window * Window;
	static SDL_GLContext Settings;
	static bool IsInstantiated, IsRunning, WireframeMode;
	static unsigned Width, Height;
	static float FpsCap, BlendFactor;
	static double Time;
	static Uint32 StartTime, DeltaTime;
	static glm::vec4 DayClearColor, NightClearColor, FogColor;
	// Projection matrix
	static glm::mat4 ProjectionMatrix;
	static double Fov, AspectRatio, Near, Far;

	DisplayManager() = delete;
	~DisplayManager() = delete;

	static void SetFogColor();

	friend InputManager;
};

