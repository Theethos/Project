#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include "State.h"
#include "Player.h"
#include "Map.h"

class GameState : public State
{
public:
	GameState(sf::RenderWindow *window, std::map < std::string, int> *keys, std::stack<State*>* states, WhichState state,
		std::string config_file, int sprite_scale, std::string player_name, sf::Font* player_name_font);
	virtual ~GameState();

	void handleInput(const float &dt);
	void update(const float &dt);
	void render(sf::RenderTarget* target);
	void initActions();
	bool checkSpritePosition();
	bool checkViewPosition(std::string movement);

private:
	Player *player;	
	Map *map;
	sf::View playerView;
	std::map<std::string, int> playerSpriteOffset;
	sf::Music music;
};

#endif // !_GAME_STATE_H_
