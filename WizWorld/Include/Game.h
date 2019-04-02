#ifndef _GAME_H_
#define _GAME_H_

#include "GameState.h"
#include "MenuState.h"

class Game
{
public:
	Game();
	virtual ~Game();

	/* It is the main fonction (this is where the magic happens) */
	void run();

private:
	sf::RenderWindow m_window;
	bool m_fullscreen;

	sf::Event m_event;

	std::stack<State*> m_states;

	sf::Clock m_clock;
	/* Delta time, time between 2 frames */
	float m_dt;

	/* Keys that Game uses */
	std::map<std::string, int> m_keys;


	/* Private functions */

	void update();
	void updateEvents();
	void updateDt();
	void render();
	void initializeWindow();
	void initializeStates();
	void initializeKeys();
};

#endif // !_GAME_H_