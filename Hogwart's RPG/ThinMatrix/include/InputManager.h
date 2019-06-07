#pragma once

#define GetKey InputManager::IsKeyPressed
#define GetButton InputManager::IsButtonPressed

////////////////////////////////////////////////////////////
/// \brief Static class that manages the game events
///
////////////////////////////////////////////////////////////
class InputManager
{
public:
	static void Create();
	static void Update();
	static void Destroy();

	static bool IsKeyPressed(const int & keyCode);
	static bool IsButtonPressed(const int & buttonCode);
	static bool DidMouseMove();
	static glm::vec2 GetMousePosition();
	static glm::vec2 GetMouseRelativePosition();
	inline static int GetMouseWheelY() { return MouseWheelY; }
	static void HideCursor(const bool & hide);
	static void CatchCursor(const bool & _catch);


private:
	static bool IsInstantiated;
	static SDL_Event Event;

	static std::vector<bool> Keys;
	static std::vector<bool> Mouse;

	static int MouseX, MouseY, MouseRelX, MouseRelY, MouseWheelY;

	InputManager() = delete;
	~InputManager() = delete;
};

