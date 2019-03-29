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
	initializeTextures();
	m_player = new Player(200.0, 0.0, 0.0, &m_textures["PLAYER_IDLE"]);
}

GameState::~GameState()
{
	delete m_player;
}

void GameState::handleInput(const double &dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_actions["MOVE_UP"])))
		m_player->move(dt, 0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_actions["MOVE_DOWN"])))
		m_player->move(dt, 0.f, 1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_actions["MOVE_LEFT"])))
		m_player->move(dt, -1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_actions["MOVE_RIGHT"])))
		m_player->move(dt, 1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_actions["MENU"])))
	{
		m_states->push(new MenuState(m_window, m_keys, m_states, "../External/Config/pause_menu_buttons.cfg"));
	}
}

void GameState::update(const double& dt)
{
	updateMousePositions();
	handleInput(dt);

	m_player->update(dt);
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
	}

	config_file.close();
}

void GameState::initializeTextures()
{
	if (!m_textures["PLAYER_IDLE"].loadFromFile("C:/Users/Théo Brichet/Desktop/Project/WizWorld/External/Images/Sprites/wizard/1_IDLE_000.png"))
	{
		std::cerr << "Could not load PLAYER_IDLE image" << std::endl;
	}
}

