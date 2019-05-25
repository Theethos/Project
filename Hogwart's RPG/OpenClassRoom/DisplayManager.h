#pragma once

#include "Camera.h"
class InputManager;

#define MV DisplayManager::ModelView
#define SMV DisplayManager::SavedModelView
#define MVP DisplayManager::ModelViewProjection
#define Push SMV = MV
#define Pop MV = SMV

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
	static void Zoom(const bool & in);
	inline static bool ShouldBeRunning() { return DisplayManager::IsRunning; }
	inline static void MoveCamera() { Camera.Move(); }

	inline static const unsigned & GetWidth() { return Width; }
	inline static const unsigned & GetHeight() { return Height; }
	inline static const glm::vec4 & GetClearColor() { return ClearColor; }
	inline static const float & GetSpeed() { return Camera.GetSpeed(); }
	inline static const float & GetSensitivty() { return Camera.GetSensitivity(); }
	inline static void SetSpeed(const float & speed) { Camera.SetSpeed(speed); }
	inline static void SetSensitivty(const float & sensitivity) { Camera.SetSensitivity(sensitivity); }


	static glm::mat4 Projection;			// 3D --> 2D
	static glm::mat4 ModelView;				// Toutes les transformations
	static glm::mat4 SavedModelView;		// Save of ModelView before transformations

	static Camera Camera;
private:
	static SDL_Window * Window;
	static SDL_GLContext Settings;
	static bool IsInstantiated, IsRunning;
	static unsigned Width, Height;
	static float FpsCap;
	static Uint32 StartTime, DeltaTime;
	static glm::vec4 ClearColor;
	static double Fovy;

	DisplayManager() = delete;
	~DisplayManager() = delete;

	friend InputManager;
};

