#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/Game.h"

/* Constructor */
Game::Game() : dt(0.0), fullscreen(false), music("../External/Config/music.cfg")
{
	initWindow();
	initKeys();
	initStates();
}

/* Destructor */
Game::~Game()
{
	// Delete the states stack
	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

/* It is the main fonction (this is where the magic happens) */
void Game::run()
{
	/* Main loop */
	while (this->window.isOpen())
	{
		// Update delta_time to know how long it takes to do the entire loop
		this->updateDt();
		this->update();
		this->render();
	}
}

void Game::update()
{
	// Check if user close the window
	this->updateEvents();

	// Updates from top state
	if (!this->states.empty())
	{
		this->states.top()->update(this->dt);
		// Pops the state it is finished/closed 
		if (this->states.top()->getQuit())
		{
			delete this->states.top();
			this->states.pop();
		}
		this->updateMusic(this->dt);
	}
	// There is no more states
	else
	{
		this->window.close();
	}
}

void Game::render()
{
	this->window.clear();

	// Renders from state
	if (!this->states.empty())
		this->states.top()->render(&this->window);

	this->window.display();
}

/* Initializes the window with the parameters in the file "window.cfg" 
   Format :
		Title
		Width Height
		FullScreen
		FPS
		Vertical synchronisation enabled 
*/
void Game::initWindow()
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
		config_file >> this->fullscreen;
		config_file >> fps;
		config_file >> vertical_sync_enabled;
		
		config_file.close();
	}

	if (this->fullscreen)
		this->window.create(video_mode, title, sf::Style::Fullscreen);
	else
		this->window.create(video_mode, title);

	this->window.setFramerateLimit(fps);
	this->window.setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initStates()
{
	this->states.push(new MenuState(&this->window, &this->keys, &this->states, WhichState::MENU_STATE, "../External/Config/main_menu_buttons.cfg", Menu::MAIN_MENU));
}

/* Initializes @member[keys] with the parameters in the files "game_keys.cfg"
   Format :
		Key_Name SFML_Key_Value
*/
void Game::initKeys()
{
	std::ifstream config_file("../External/Config/game_keys.cfg");

	if (config_file.is_open())
	{
		std::string key = "";
		int key_value = 0;
		while (config_file >> key >> key_value)
		{
			this->keys[key] = key_value;
		}
	}

	config_file.close();
}

void Game::updateEvents()
{
	while (this->window.pollEvent(this->event))
	{
		// User closed the window
		if (this->event.type == sf::Event::Closed)
		{
			this->window.close();
			break;
		}
	}
}

void Game::updateMusic(const float & dt)
{
	if (this->states.top()->getState() == WhichState::MENU_STATE)
	{
		MenuState* menu = static_cast<MenuState*>(this->states.top());
		if (menu->getMenuType() == Menu::PAUSE_MENU)
		{
			this->music.pause("GAME");
			this->music.play(dt, "PAUSE_MENU");
		}
		else
		{
			this->music.stop("PAUSE_MENU");
			this->music.stop("GAME");
			this->music.play(dt, "MENU");
		}
	}
	else if (this->states.top()->getState() == WhichState::GAME_STATE)
	{
		this->music.stop("PAUSE_MENU");
		this->music.stop("MENU");
		this->music.play(dt, "GAME");
	}
}

void Game::updateDt()
{
	this->dt = this->clock.restart().asSeconds();
}

