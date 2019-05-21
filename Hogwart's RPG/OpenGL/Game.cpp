#include "Precompiled_Header_OpenGL.h"
#include "Game.h"


GameGL::GameGL() :
m_Settings(24, 8, 0, 3, 3),
m_Window(sf::VideoMode(640, 480), "OpenGl des ses morts", sf::Style::Default, m_Settings),
m_IsRunning(true)
{
	Initialize();
}


GameGL::~GameGL()
{
}

void GameGL::Run()
{
	while (m_IsRunning)
	{
		m_Window.clear();
		UpdateEvents();
		Update();
	}
}

void GameGL::Initialize()
{
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Can't initialize GLEW. Error in file " << __FILE__ << " line " << __LINE__ << ".\n";
		throw std::exception("Can't initialize GLEW");
	}
}

void GameGL::Update()
{
	m_Window.display();
}

void GameGL::UpdateEvents()
{
	while (m_Window.pollEvent(m_Event))
	{
		if (m_Event.type == sf::Event::Closed)
			m_IsRunning = false;
		else if (m_Event.type == sf::Event::KeyReleased)
		{
			switch (m_Event.key.code)
			{
			case sf::Keyboard::Escape:	m_IsRunning = false;	break;
			default:														break;
			}
		}
	}
}
