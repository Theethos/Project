#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include "State.h"
#include "Player.h"

/*
 * ==================================================
 * ================= Class GameState ================
 * ==================================================
 */

class GameState : public State
{
public:
	GameState(sf::RenderWindow *window, std::map < std::string, int> *keys, std::stack<State*>* states);
	virtual ~GameState();

	virtual void handleInput(const double &dt);
	virtual void update(const double &dt);
	virtual void render(sf::RenderTarget* target);
	virtual void initializeActions();
	virtual void initializeTextures();

private:
	Player *m_player;	
	std::map<std::string, sf::Texture> m_textures;
};

#endif // !_GAME_STATE_H_
