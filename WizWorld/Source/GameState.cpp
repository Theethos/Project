#include "../Include/Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/GameState.h"
#include "../Include/MenuState.h"


GameState::GameState(sf::RenderWindow *window, std::map < std::string, int> *keys, std::stack<State*>* states, std::string config_file, int sprite_scale) : State(window, keys, states)
{
	initActions();
	this->player = new Player(2.f, 0.0, 0.0, config_file, sprite_scale);
}

GameState::~GameState()
{
	delete this->player;
}

void GameState::handleInput(const float &dt)
{
	/* Move the character in the direction given by input */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->actions["MOVE_UP"])))
		this->player->move(dt, 0.f, -1.f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->actions["MOVE_DOWN"])))
		this->player->move(dt, 0.f, 1.f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->actions["MOVE_LEFT"])))
		this->player->move(dt, -1.f, 0.f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->actions["MOVE_RIGHT"])))
		this->player->move(dt, 1.f, 0.f);
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
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->player->render(target);
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

