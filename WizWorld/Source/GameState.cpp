#include "../Include/GameState.h"
#include "../Include/MenuState.h"

/*
 * ==================================================
 * ================= Class GameState ================
 * ==================================================
 */

GameState::GameState(sf::RenderWindow *window, std::map < std::string, int> *keys, std::stack<State*>* states) : State(window, keys, states), m_player()
{
	initializeActions();
}

GameState::~GameState()
{

}

void GameState::handleInput(const double &dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_actions["MOVE_UP"])))
		m_player.move(dt, 0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_actions["MOVE_DOWN"])))
		m_player.move(dt, 0.f, 1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_actions["MOVE_LEFT"])))
		m_player.move(dt, -1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_actions["MOVE_RIGHT"])))
		m_player.move(dt, 1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_actions["MENU"])))
	{
		m_states->push(new MenuState(m_window, m_keys, m_states, "../External/Config/pause_menu_buttons.cfg"));
	}
}

void GameState::update(const double& dt)
{
	updateMousePositions();
	handleInput(dt);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = m_window;

	m_player.render(target);
}

/* Initializes @member[actions] with the parameters in the files "game_actions.cfg"
   Format :
		Action_Name Key_Name
*/
void GameState::initializeActions()
{
	std::ifstream config_file("../External/Config/game_actions.cfg");

	if (config_file.is_open())
	{
		std::string action = "";
		std::string key = "";
		while (config_file >> action >> key)
		{
			m_actions[action] = m_keys->at(key);
		}
	}

	config_file.close();
}

