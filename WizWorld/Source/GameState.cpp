#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/GameState.h"
#include "../Include/MenuState.h"


GameState::GameState(sf::RenderWindow *window, std::map < std::string, int> *keys, std::stack<State*>* states, WhichState state, std::string config_file, int sprite_scale, std::string player_name, sf::Font* player_name_font)
	: State(window, keys, states, state)
{
	initActions();
	this->player = new Player(1.5f, 0.0, 0.0, config_file, player_name, player_name_font, sprite_scale);
	this->map = new Map("../External/Images/Map/Floors_GBA/Courtyard.png", sprite_scale);

	this->playerView.setSize(this->window->getSize().x, this->window->getSize().y);
	this->playerView.setCenter(this->window->getSize().x / 2, this->window->getSize().y / 2);
	this->player->getSprite()->setPosition(this->playerView.getCenter());
}

GameState::~GameState()
{
	delete this->player;
	delete this->map;
}

void GameState::handleInput(const float &dt)
{
	/* Move the character in the direction given by input */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->actions["MOVE_UP"])))
	{
		this->player->move(dt, 0.f, -1.f);
		if (!this->checkSpritePosition() && !this->checkViewPosition("MOVE_UP"))
			// * 2 * is in hard, don't know why but otherwise the camera is slower than the player
			this->playerView.move(0.f, 1.f * 2 * this->player->getMovement()->getVelocity().y);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->actions["MOVE_DOWN"])))
	{
		this->player->move(dt, 0.f, 1.f);
		if (!this->checkSpritePosition() && !this->checkViewPosition("MOVE_DOWN"))
			this->playerView.move(0.f , 1.f * 2 * this->player->getMovement()->getVelocity().y);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->actions["MOVE_LEFT"])))
	{
		this->player->move(dt, -1.f, 0.f);
		if (!this->checkSpritePosition() && !this->checkViewPosition("MOVE_LEFT"))
			this->playerView.move(1.f * 2 * this->player->getMovement()->getVelocity().x, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->actions["MOVE_RIGHT"])))
	{
		this->player->move(dt, 1.f, 0.f);
		if (!this->checkSpritePosition() && !this->checkViewPosition("MOVE_RIGHT"))
			this->playerView.move(1.f * 2 * this->player->getMovement()->getVelocity().x, 0.f);
	}
	/* Open pause menu "escape" is pressed */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->actions["MENU"])))
	{
		this->states->push(new MenuState(this->window, this->keys, this->states, WhichState::MENU_STATE, "../External/Config/pause_menu_buttons.cfg", Menu::PAUSE_MENU));
	}
}

void GameState::update(const float& dt)
{
	this->updateMousePositions();

	this->handleInput(dt);
	
	this->player->update(dt);

	this->checkSpritePosition();
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->setView(this->playerView);
	this->map->render(target);
	this->player->render(target);

	target->setView(this->window->getDefaultView());
}

/* Initializes @member[actions] with the parameters in the files "game_actions.cfg"
   Format :
		Action_Name Key_Name
*/
void GameState::initActions()
{
	std::ifstream config_file("../External/Config/game_actions.cfg");

	if (config_file.is_open())
	{
		std::string action = "";
		std::string key = "";
		while (config_file >> action >> key)
		{
			this->actions[action] = this->keys->at(key);
		}
		config_file.close();
	}

}
/* Checks if player is going out of the map */
bool GameState::checkSpritePosition()
{
	sf::Vector2f map_size = sf::Vector2f(this->map->getShape().getGlobalBounds().width, this->map->getShape().getGlobalBounds().height);
	sf::Vector2f map_position = sf::Vector2f(this->map->getShape().getGlobalBounds().left, this->map->getShape().getGlobalBounds().top);

	sf::Vector2f sprite_size = sf::Vector2f(this->player->getSprite()->getGlobalBounds().width, this->player->getSprite()->getGlobalBounds().height);
	sf::Vector2f sprite_position = sf::Vector2f(this->player->getSprite()->getPosition());

	if (sprite_position.x < map_position.x)
	{
		sprite_position.x = map_position.x;
	}
	// 1.5 in hard
	else if (sprite_position.x + 1.5 * sprite_size.x > map_size.x + map_position.x)
	{
		sprite_position.x = map_size.x + map_position.x - 1.5 * sprite_size.x;
	}

	else if (sprite_position.y < map_position.y)
	{
		sprite_position.y = map_position.y;
	}
	else if (sprite_position.y + sprite_size.y > map_size.y + map_position.y)
	{
		sprite_position.y = map_size.y + map_position.y - sprite_size.y;
	}

	if (this->player->getSprite()->getPosition() != sprite_position)
	{
		this->player->getSprite()->setPosition(sprite_position);
		return true;
	}
	return false;
}
/* Checks if the camera should move or not based on the sprite movements */
bool GameState::checkViewPosition(std::string movement)
{
	sf::Vector2f map_size = sf::Vector2f(this->map->getShape().getGlobalBounds().width, this->map->getShape().getGlobalBounds().height);
	sf::Vector2f map_position = sf::Vector2f(this->map->getShape().getGlobalBounds().left, this->map->getShape().getGlobalBounds().top);

	sf::Vector2f sprite_size = sf::Vector2f(this->player->getSprite()->getGlobalBounds().width, this->player->getSprite()->getGlobalBounds().height);
	sf::Vector2f sprite_position = sf::Vector2f(this->player->getSprite()->getPosition());

	sf::Vector2f window_size = sf::Vector2f(this->window->getSize());

	// (window_size / 2) because the camera is in the center of the window
	if (movement == "MOVE_LEFT" || movement == "MOVE_RIGHT")
	{																											// 2 in hard
		return sprite_position.x - (window_size.x / 2) < map_position.x || sprite_position.x + (window_size.x / 2) + 2 * sprite_size.x > map_size.x + map_position.x;
	}
	else if (movement == "MOVE_UP" || movement == "MOVE_DOWN")
	{
		return sprite_position.y - (window_size.y / 2) < map_position.y || sprite_position.y + (window_size.y / 2) + sprite_size.y > map_size.y + map_position.y;
	}
}

