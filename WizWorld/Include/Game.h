#ifndef _GAME_H_
#define _GAME_H_

#include "GameState.h"
#include "MenuState.h"
#include "MusicComponent.h"

class Game
{
public:
	Game();
	virtual ~Game();

	/* It is the main fonction (this is where the magic happens) */
	void run();

private:
	sf::RenderWindow window;
	bool fullscreen;
	sf::Event event;
	std::stack<State*> states;
	sf::Clock clock;
	/* Delta time, time between 2 frames */
	float dt;
	/* Keys that Game uses */
	std::map<std::string, int> keys;
	MusicComponent music;

	/* Private functions */

	void update();
	void updateEvents();
	void updateMusic(const float & dt);
	void updateDt();
	void render();
	void initWindow();
	void initStates();
	void initKeys();

};

#endif // !_GAME_H_
