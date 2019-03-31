#include "../Include/GameState.h"
#include "../Include/MenuState.h"

/*
 * ==================================================
 * ================= Class GameState ================
 * ==================================================
 */


GameState::GameState(sf::RenderWindow *window, std::map < std::string, int> *keys, std::stack<State*>* states) : State(window, keys, states)
{
	initializeActions();
	m_player = new Player(2.f, 0.0, 0.0);
}

GameState::~GameState()
{
	delete m_player;
}

void GameState::handleInput(const float &dt)
{
	/* Move the character in the direction given by input. Reset the animation if the key is realesed */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_actions["MOVE_UP"])))
		m_player->move(dt, 0.f, -1.f);
	else
		m_player->getAnimation()->resetAnimation("MOVE_UP");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_actions["MOVE_DOWN"])))
		m_player->move(dt, 0.f, 1.f);
	else
		m_player->getAnimation()->resetAnimation("MOVE_DOWN");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_actions["MOVE_LEFT"])))
		m_player->move(dt, -1.f, 0.f);
	else
		m_player->getAnimation()->resetAnimation("MOVE_LEFT");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_actions["MOVE_RIGHT"])))
		m_player->move(dt, 1.f, 0.f);
	else
		m_player->getAnimation()->resetAnimation("MOVE_RIGHT");
	/* Open pause menu "escape" is pressed */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_actions["MENU"])))
	{
		m_states->push(new MenuState(m_window, m_keys, m_states, "../External/Config/pause_menu_buttons.cfg"));
	}
}

void GameState::update(const float& dt)
{
	updateMousePositions();

	m_player->update(dt);

	handleInput(dt);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = m_window;

	m_player->render(target);
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
		config_file.close();
	}

}

