#ifndef _GAME_H_
#define _GAME_H_

#include "GameState.h"

class Game
{
public:
	Game();
	virtual ~Game();

	/* It is the main fonction (this is where the magic happens) */
	void run();

private:
	/*=== Attributes ===*/
	sf::RenderWindow m_window;
	sf::Event m_event;
	std::stack<State*> m_states;
	/* Clock*/
	sf::Clock m_clock;
	/* Delta time, time between 2 frames */
	float m_dt;
	/* Keys that Game uses */
	std::map<std::string, int> m_keys;


	/*=== Private methods ===*/

	void update();
	void updateEvents();
	void updateDt();
	void render();
	/* Initializes @member[window] with the parameters in the files "window.cfg" */
	void initializeWindow();
	/* Initializes @member[states] */
	void initializeStates();
	/* Initializes @member[keys] */
	void initializeKeys();
	/* Initalizes @member[actions] */
	void initializeActions();
};

#endif // !_GAME_H_
