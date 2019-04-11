#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/GameState.h"
#include "../Include/MenuState.h"


GameState::GameState(sf::RenderWindow *window, std::map < std::string, int> *keys, std::stack<State*>* states, std::string config_file, int sprite_scale) : State(window, keys, states)
{
	initActions();
	this->player = new Player(1.5f, 0.0, 0.0, config_file, sprite_scale);
	this->map = new Map("../External/Images/Map/Floors_GBA/Courtyard.png", 3);

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
		this->playerView.move(0.f, -1.f * -2 * this->player->getMovement()->getVelocity().y);

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->actions["MOVE_DOWN"])))
	{
		this->player->move(dt, 0.f, 1.f);
		this->playerView.move(0.f , 1.f * 2 * this->player->getMovement()->getVelocity().y);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->actions["MOVE_LEFT"])))
	{
		this->player->move(dt, -1.f, 0.f);
		this->playerView.move(-1.f * -2 * this->player->getMovement()->getVelocity().x, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->actions["MOVE_RIGHT"])))
	{
		this->player->move(dt, 1.f, 0.f);
		this->playerView.move(1.f * 2 * this->player->getMovement()->getVelocity().x, 0.f);
	}
	/* Open pause menu "escape" is pressed */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->actions["MENU"])))
	{
		this->states->push(new MenuState(this->window, this->keys, this->states, "../External/Config/pause_menu_buttons.cfg", Menu::PAUSE_MENU));
	}
}

void GameState::update(const float& dt)
{
	updateMousePositions();

	handleInput(dt);
	
	this->player->update(dt);

	//this->checkOutOfMap();
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

void GameState::checkOutOfMap()
{
	
	sf::Vector2f view_center = this->playerView.getCenter();
	sf::Vector2f map_position = this->map->getPosition();
	sf::Vector2f map_size = this->map->getSize();
	map_size.x += map_position.x;
	map_size.y += map_position.y;

	if (map_position.x > view_center.x)
	{
		this->playerView.setCenter(map_position.x, view_center.y);
		this->player->getSprite()->setPosition(this->playerView.getCenter());
	}
	if (map_size.x < view_center.x)
	{
		this->playerView.setCenter(map_size.x, view_center.y);
		this->player->getSprite()->setPosition(this->playerView.getCenter());

	}
	if (map_position.y > view_center.y)
	{
		this->playerView.setCenter(view_center.x, map_position.x);
		this->player->getSprite()->setPosition(this->playerView.getCenter());

	}
	if (map_size.y < view_center.y)
	{
		this->playerView.setCenter(view_center.x, map_size.y);
		this->player->getSprite()->setPosition(this->playerView.getCenter());

	}
}

