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
	sf::RenderWindow window;
	bool fullscreen;
	sf::Event event;
	std::stack<State*> states;
	sf::Clock clock;
	// Delta time, time between 2 frames
	float dt;
	// Keys that Game uses
	std::map<std::string, int> keys;
	MusicComponent music;

	//Private functions
	void Update();
	void UpdateEvents();
	void UpdateMusic();
	void UpdateDt();
	void Render();
	void InitWindow();
	void InitStates();
	void InitKeys();
	void DisplayFPS();
};

#endif // !_GAME_H_
