#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include "State.h"
#include "Player.h"
#include "Map.h"
#include "TransitionComponent.h"

class GameState : public State
{
public:
	// Construtor
	GameState(sf::RenderWindow *window, std::map < std::string, int> *keys, std::stack<State*>* states, WhichState state, std::string config_file, int sprite_scale, std::string player_name, sf::Font* player_name_font);
	// Destructor
	virtual ~GameState();

	// Functions
	void Update(const float &dt);
	void Render(sf::RenderTarget* target);

private:
	Player *player;	
	std::string previousMove;
	bool movementLocked;
	
	// Map managers
	std::map<std::string, Map*> maps;
	std::map<std::string, Map*> collisionMaps;
	std::string currentMap;
	TransitionComponent transition;
	sf::Color transitionColor;

	// Camera managers
	sf::View playerView;
	std::map<std::string, int> viewLocked;
	sf::RectangleShape viewMovementArea;
	
	// Private functions
	void InitActions();
	void InitMaps(int scale);
	void InitView();
	void ResetView();
	void HandleInput(const float &dt);
	void ChangeMap(sf::Color color);
	bool CheckSpriteCollision(const float & dt, std::string movement);
	bool CheckViewPosition(std::string movement);
};

#endif // !_GAME_STATE_H_
