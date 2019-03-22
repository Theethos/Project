#define _REQUIRE_SFML_
	#include "../Include/Macro_Include.h"
#undef _REQUIRE_SFML_
#include "../Include/Game.h"

/*
 * ==================================================
 * =================== Class Game ===================
 * ==================================================
 */

Game::Game() : m_dt(0.0)
{
	initializeWindow();
	initializeKeys();
	initializeStates();
}

Game::~Game()
{
	/* Delete the stack */
	while (!m_states.empty())
	{
		delete m_states.top();
		m_states.pop();
	}
}

/* It is the main fonction (this is where the magic happens) */
void Game::run()
{
	/* Main loop */
	while (m_window.isOpen())
	{
		// Update @member[dt] to know how long it takes to do the entire loop
		updateDt();
		update();
		render();
		//std::cout << m_dt << std::endl; // To see the during between each loop
	}
}

void Game::update()
{
	updateEvents();
	// Updates from state
	if (!m_states.empty())
	{
		m_states.top()->update(m_dt);
		if (m_states.top()->getQuit())
		{
			delete m_states.top();
			m_states.pop();
		}
		else if (m_states.top()->getAdd())
		{
			State *newState = m_states.top()->getAdd();
			m_states.top()->resetAdd();
			m_states.push(newState);
		}
	}
	else
	{
		m_window.close();
	}
}

void Game::render()
{
	m_window.clear();
	// Renders from state
	if (!m_states.empty())
		m_states.top()->render(&m_window);

	m_window.display();
}
/* Initializes @member[window] with the parameters in the files "window.cfg" 
   Format :
		Title
		Width height
		FPS
		Vertical synchronisation enabled 
*/
void Game::initializeWindow()
{
	std::ifstream config_file("../External/Config/window.cfg");

	/* Window attributes */
	std::string title("None");
	sf::VideoMode video_mode(800, 600);
	unsigned fps = 120;
	bool vertical_sync_enabled = false;

	if (config_file.is_open())
	{
		std::getline(config_file, title);
		config_file >> video_mode.width >> video_mode.height;
		config_file >> fps;
		config_file >> vertical_sync_enabled;
	}

	config_file.close();

	m_window.create(video_mode, title);
	m_window.setFramerateLimit(fps);
	m_window.setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initializeStates()
{
	//m_states.push(new GameState(&m_window, &m_keys));
	m_states.push(new MainMenuState(&m_window, &m_keys));
}
/* Initializes @member[keys] with the parameters in the files "game_keys.cfg"
   Format :
		Key_Name SFML_Key_Value
*/
void Game::initializeKeys()
{
	std::ifstream config_file("../External/Config/game_keys.cfg");

	if (config_file.is_open())
	{
		std::string key = "";
		int key_value = 0;
		while (config_file >> key >> key_value)
		{
			m_keys[key] = key_value;
		}
	}

	config_file.close();
}

void Game::updateEvents()
{
	while (m_window.pollEvent(m_event))
	{
		/* User closed the window */
		if (m_event.type == sf::Event::Closed)
			m_window.close();
	}
}

void Game::updateDt()
{
	m_dt = m_clock.restart().asSeconds();
}

