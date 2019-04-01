#define _REQUIRE_SFML_
	#include "../Include/Macro_Include.h"
#undef _REQUIRE_SFML_
#include "../Include/Game.h"

/* Constructor */
Game::Game() : m_dt(0.0), m_fullscreen(false)
{
	initializeWindow();
	initializeKeys();
	initializeStates();
}

/* Destructor */
Game::~Game()
{
	// Delete the states stack
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
		// Update delta_time to know how long it takes to do the entire loop
		updateDt();
		update();
		render();
	}
}

void Game::update()
{
	// Check if user close the window
	updateEvents();

	// Updates from top state
	if (!m_states.empty())
	{
		m_states.top()->update(m_dt);
		// Pops the state it is finished/closed 
		if (m_states.top()->getQuit())
		{
			delete m_states.top();
			m_states.pop();
		}
	}
	// There is no more states
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

/* Initializes the window with the parameters in the file "window.cfg" 
   Format :
		Title
		Width Height
		FullScreen
		FPS
		Vertical synchronisation enabled 
*/
void Game::initializeWindow()
{
	std::ifstream config_file("../External/Config/window.cfg");

	/* Window's attributes */
	std::string title("None");
	sf::VideoMode video_mode(sf::VideoMode::getDesktopMode());
	unsigned fps = 120;
	bool vertical_sync_enabled = false;

	if (config_file.is_open())
	{
		std::getline(config_file, title);
		config_file >> video_mode.width >> video_mode.height;
		config_file >> m_fullscreen;
		config_file >> fps;
		config_file >> vertical_sync_enabled;
		
		config_file.close();
	}

	if (m_fullscreen)
		m_window.create(video_mode, title, sf::Style::Fullscreen);
	else
		m_window.create(video_mode, title);

	m_window.setFramerateLimit(fps);
	m_window.setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initializeStates()
{
	m_states.push(new MenuState(&m_window, &m_keys, &m_states, "../External/Config/main_menu_buttons.cfg"));
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
		// User closed the window
		if (m_event.type == sf::Event::Closed)
			m_window.close();
	}
}

void Game::updateDt()
{
	m_dt = m_clock.restart().asSeconds();
}

