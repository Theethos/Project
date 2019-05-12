#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/Game.h"

using namespace sf;

// Constructor
Game::Game() :
m_DeltaTime(0.0), 
m_Fullscreen(false),
m_Running(true),
m_Music("../External/Config/Music/Music.cfg")
{
	InitWindow();
	InitStates();
	if (Joystick::isConnected(0))
		m_Window.setMouseCursorVisible(false);
	else
		m_Window.setMouseCursorVisible(true);

	m_Window.setActive(true);
}
// Destructor
Game::~Game()
{
	// Delete the states stack
	while (!m_States.empty())
	{
		delete m_States.top();
		m_States.pop();
	}
}

// It is the main fonction (this is where the magic happens)
void Game::Run()
{
	// Main loop
	while (m_Running)
	{
		// Update delta time to know how long it takes to do the entire loop
		UpdateDt();
		Update();
		Render();
	}
}

void Game::Update()
{
	UpdateEvents();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Updates from top state
	if (!m_States.empty())
	{
		UpdateMusic();
		m_States.top()->Update(m_DeltaTime);
		// Pops the state it is finished/closed 
		if (m_States.top()->GetQuit())
		{
			delete m_States.top();
			m_States.pop();
		}
	}
	// There is no more states
	else
	{
		m_Running = false;
	}
}

void Game::UpdateEvents()
{
	while (m_Window.pollEvent(m_Event))
	{
		if (m_Event.type == Event::Closed)
		{
			m_Running = false;
			break;
		}
		else if (m_Event.type == sf::Event::Resized)
		{
			glViewport(0, 0, m_Event.size.width, m_Event.size.height);
		}
		else if (m_Event.type == Event::JoystickConnected)
		{
			m_States.top()->InitControllerKeys();
			m_States.top()->InitControllerActions();
			m_Window.setMouseCursorVisible(false);
		}
		else if (m_Event.type == Event::JoystickDisconnected)
		{
			m_States.top()->InitKeyboardKeys();
			m_States.top()->InitKeyboardActions();
			m_Window.setMouseCursorVisible(true);
		}
		else if (m_Event.type == Event::JoystickMoved)
		{
			if (std::abs(m_Event.joystickMove.position) > 80)
				m_States.top()->HandleInput(-1, m_DeltaTime);
		}
		else if (m_Event.type == Event::JoystickButtonReleased)
			m_States.top()->HandleInput(m_Event.joystickButton.button, m_DeltaTime);
		else if (m_Event.type == Event::KeyReleased)
		{
			m_States.top()->HandleInput(m_Event.key.code, m_DeltaTime);
		}
		else if (m_Event.type == Event::MouseButtonReleased && m_States.top()->GetState() == WhichState::EDITOR_STATE)
		{
			auto state = static_cast<EditorState*>(m_States.top());
			state->Update(m_DeltaTime, &m_Event);
		}
	}
}

void Game::UpdateMusic()
{
	if (m_States.top()->GetState() == WhichState::MENU_STATE)
	{
		MenuState* menu = static_cast<MenuState*>(m_States.top());
		if (menu->GetMenuType() == Menu::PAUSE_MENU)
		{
			m_Music.Pause("GAME");
			m_Music.Play(m_DeltaTime, "PAUSE_MENU");
		}
		else
		{
			m_Music.Stop("PAUSE_MENU");
			m_Music.Stop("GAME");
			m_Music.Play(m_DeltaTime, "MENU");
		}
	}
	else if (m_States.top()->GetState() == WhichState::GAME_STATE)
	{
		m_Music.Stop("PAUSE_MENU");
		m_Music.Stop("MENU");
		m_Music.Play(m_DeltaTime, "GAME");
	}
	else if (m_States.top()->GetState() == WhichState::EDITOR_STATE)
	{
		m_Music.Stop("PAUSE_MENU");
		m_Music.Stop("MENU");
	}
}

void Game::UpdateDt()
{
	m_DeltaTime = m_Clock.restart().asSeconds();
}

void Game::Render()
{
	// Renders from state
	if (!m_States.empty())
	{
		// Render the game under the pause menu 
		if (m_States.top()->GetState() == WhichState::MENU_STATE)
		{
			auto menu = static_cast<MenuState*>(m_States.top());
			if (menu->GetMenuType() == Menu::PAUSE_MENU)
			{
				m_States.pop();
				m_States.top()->Render(m_Window);
				m_States.push(menu);
			}
		}
		m_States.top()->Render(m_Window);
	}

	//_DisplayFPS();

	m_Window.display();
}
/////////////////////////////////////////////////////////////////////
/// Initializes the m_Window with the parameters in the file "m_Window.cfg" 
/// Format :
/// Title
///	Width Height
///	FullScreen
///	FPS
///	Vertical synchronisation enabled 
/////////////////////////////////////////////////////////////////////
void Game::InitWindow()
{
	std::ifstream config_file("../External/Config/window/window.cfg");

	std::string title("None");
	ContextSettings contexte;
	VideoMode video_mode(VideoMode::getDesktopMode());
	unsigned fps = 120;
	bool vertical_sync_enabled = false;

	if (config_file.is_open())
	{
		std::getline(config_file, title);
		config_file >> contexte.depthBits >> contexte.stencilBits >> contexte.antialiasingLevel >> contexte.majorVersion >> contexte.minorVersion;
		config_file >> video_mode.width >> video_mode.height;
		config_file >> m_Fullscreen;
		config_file >> fps;
		config_file >> vertical_sync_enabled;
		config_file.close();
	}
	if (m_Fullscreen)
		m_Window.create(video_mode, title, Style::Fullscreen, contexte);
	else
		m_Window.create(video_mode, title, Style::Close, contexte);

	m_Window.setFramerateLimit(fps);
	m_Window.setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::InitStates()
{
	m_States.push(new MenuState(m_Window, m_States, WhichState::MENU_STATE, m_Running, "../External/Config/Buttons/Main_menu.cfg", Menu::MAIN_MENU));
}

void Game::DisplayFPS()
{
	Font font;
	font.loadFromFile("../External/Fonts/Animales_Fantastic.otf");

	Text fps;
	fps.setString(std::to_string(static_cast<int>(1 / m_DeltaTime)));
	fps.setCharacterSize(60);
	fps.setFont(font);
	fps.setFillColor(Color::Black);
	m_Window.draw(fps);
}

