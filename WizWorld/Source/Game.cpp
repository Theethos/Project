#define _REQUIRE_SFML_
	#include "../Include/Macros_Includes.h"
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
		m_states.top()->render(m_window);

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
	std::ifstream window_config("../External/Config/window.cfg");

	/* Window attributes */
	std::string title("None");
	sf::VideoMode video_mode(800, 600);
	unsigned fps = 120;
	bool vertical_sync_enabled = false;

	if (window_config.is_open())
	{
		std::getline(window_config, title);
		window_config >> video_mode.width >> video_mode.height;
		window_config >> fps;
		window_config >> vertical_sync_enabled;
	}

	window_config.close();

	m_window.create(video_mode, title);
	m_window.setFramerateLimit(fps);
	m_window.setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initializeStates()
{
	m_states.push(new GameState(&m_window, &m_keys));
}

void Game::initializeKeys()
{
	m_keys.emplace("Z", sf::Keyboard::Key::Z);
	m_keys.emplace("Q", sf::Keyboard::Key::Q);
	m_keys.emplace("S", sf::Keyboard::Key::S);
	m_keys.emplace("D", sf::Keyboard::Key::D);
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

