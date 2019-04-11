#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include "State.h"
#include "Player.h"

class GameState : public State
{
public:
	GameState(sf::RenderWindow *window, std::map < std::string, int> *keys, std::stack<State*>* states, std::string config_file, int sprite_scale);
	virtual ~GameState();

	virtual void handleInput(const float &dt);
	virtual void update(const float &dt);
	virtual void render(sf::RenderTarget* target);
	virtual void initActions();

private:
	Player *player;	
	std::map<std::string, sf::Texture> textures;
};

#endif // !_GAME_STATE_H_
