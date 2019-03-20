#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include "States.h"
#include "Entity.h"

/*
 * ==================================================
 * ================= Class GameState ================
 * ==================================================
 */

class GameState : public State
{
public:
	GameState(sf::RenderWindow *window, std::map < std::string, int> *keys);
	virtual ~GameState();

	virtual void handleInput(const float &dt);
	virtual void update(const float &dt);
	virtual void render(sf::RenderTarget & target);
	virtual void initializeActions();


private:
	Entity m_player;
};

#endif // !_GAME_STATE_H_
