#define _REQUIRE_SFML_
	#include "../Include/Macros_Includes.h"
#undef _REQUIRE_SFML_
#include "../Include/Game.h"


/*
 * ==================================================
 * =================== Class Game ===================
 * ==================================================
 */

Game::Game()
{
	initializeWindow();
}

Game::~Game()
{}

/* It is the main fonction (this is where the magic happens) */
void Game::run()
{
	/* Main loop */
	while (m_window.isOpen())
	{
		this->update();
		this->render();
	}
}

void Game::update()
{
	updateEvents();
}

void Game::render()
{
	m_window.clear();

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

void Game::updateEvents()
{
	while (m_window.pollEvent(m_event))
	{
		/* User closed the window */
		if (m_event.type == sf::Event::Closed)
			m_window.close();
		/* User pressed a key */
		if ((m_event.type == sf::Event::KeyPressed))
		{
			/* 'Escape' */
			if (m_event.key.code == sf::Keyboard::Escape)
				m_window.close();
		}
	}
}

