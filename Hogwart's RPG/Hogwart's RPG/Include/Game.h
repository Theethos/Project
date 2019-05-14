#ifndef _GAME_H_
#define _GAME_H_

#include "GameState.h"
#include "MenuState.h"
#include "MusicComponent.h"

class Game
{
public:
	// Construtor
	Game();
	// Destructor
	virtual ~Game();

	// It is the main fonction (this is where the magic happens)
	void Run();

private:
	sf::RenderWindow m_Window;

	bool m_Fullscreen;
	bool m_Running;
	sf::Event m_Event;
	std::stack<State*> m_States;
	sf::Clock m_Clock;
	// Delta time, time between 2 frames
	float m_DeltaTime;
	// Keys that Game uses
	std::map<std::string, int> m_Keys;
	MusicComponent m_Music;

	//Private functions
	void Update();
	void UpdateEvents();
	void UpdateMusic();
	void UpdateDt();
	void Render();
	void InitWindow();
	void InitStates();
	void DisplayFPS();
};

#endif // !_GAME_H_
