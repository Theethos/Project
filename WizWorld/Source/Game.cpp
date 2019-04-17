#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/Game.h"

// Constructor
Game::Game() :
dt(0.0), 
fullscreen(false),
music("../External/Config/music.cfg")
{
	InitWindow();
	InitKeys();
	InitStates();
}
// Destructor
Game::~Game()
{
	// Delete the states stack
	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

// It is the main fonction (this is where the magic happens)
void Game::Run()
{
	// Main loop
	while (this->window.isOpen())
	{
		// Update delta time to know how long it takes to do the entire loop
		this->UpdateDt();
		this->Update();
		this->Render();
	}
}

void Game::Update()
{
	// Check if user close the window
	this->UpdateEvents();

	// Updates from top state
	if (!this->states.empty())
	{
		this->states.top()->Update(this->dt);
		// Pops the state it is finished/closed 
		if (this->states.top()->getQuit())
		{
			delete this->states.top();
			this->states.pop();
		}
		this->UpdateMusic();
	}
	// There is no more states
	else
	{
		this->window.close();
	}
}

void Game::UpdateEvents()
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

void Game::UpdateMusic()
{
	if (this->states.top()->getState() == WhichState::MENU_STATE)
	{
		MenuState* menu = static_cast<MenuState*>(this->states.top());
		if (menu->getMenuType() == Menu::PAUSE_MENU)
		{
			this->music.Pause("GAME");
			this->music.Play(this->dt, "PAUSE_MENU");
		}
		else
		{
			this->music.Stop("PAUSE_MENU");
			this->music.Stop("GAME");
			this->music.Play(this->dt, "MENU");
		}
	}
	else if (this->states.top()->getState() == WhichState::GAME_STATE)
	{
		this->music.Stop("PAUSE_MENU");
		this->music.Stop("MENU");
		this->music.Play(this->dt, "GAME");
	}
}

void Game::UpdateDt()
{
	this->dt = this->clock.restart().asSeconds();
}

void Game::Render()
{
	this->window.clear();

	// Renders from state
	if (!this->states.empty())
		this->states.top()->Render(&this->window);

	//this->DisplayFPS();

	this->window.display();
}
/* Initializes @member[keys] with the parameters in the files "game_keys.cfg"
   Format :
		Key_Name SFML_Key_Value
*/
void Game::InitKeys()
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
/* Initializes the window with the parameters in the file "window.cfg" 
   Format :
		Title
		Width Height
		FullScreen
		FPS
		Vertical synchronisation enabled 
*/
void Game::InitWindow()
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

void Game::InitStates()
{
	this->states.push(new MenuState(&this->window, &this->keys, &this->states, WhichState::MENU_STATE, "../External/Config/main_menu_buttons.cfg", Menu::MAIN_MENU));
}

void Game::DisplayFPS()
{
	sf::Font font;
	font.loadFromFile("../External/Fonts/Animales_Fantastic.otf");

	sf::Text fps;
	fps.setString(std::to_string(static_cast<int>(1 / this->dt)));
	fps.setCharacterSize(60);
	fps.setFont(font);
	fps.setFillColor(sf::Color::Black);
	this->window.draw(fps);
}

