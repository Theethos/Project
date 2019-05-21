#include "pch.h"
#include "DisplayManager.h"

glm::mat4 DisplayManager::Projection;
glm::mat4 DisplayManager::ModelView;
bool DisplayManager::IsInstantiated	= false;
bool DisplayManager::IsRunning		= true;
unsigned DisplayManager::Width		= 0;
unsigned DisplayManager::Height		= 0;
unsigned DisplayManager::FpsCap		= 120;
sf::ContextSettings DisplayManager::Settings;
sf::RenderWindow DisplayManager::Window;

void DisplayManager::Create(unsigned w, unsigned h)
{
	if (!DisplayManager::IsInstantiated)
	{	
		DisplayManager::Width = w;
		DisplayManager::Height = h;

		DisplayManager::Settings = sf::ContextSettings();

		// Update the window
		DisplayManager::Window.create(sf::VideoMode(w, h), "OpenGL de ses morts", sf::Style::Default, DisplayManager::Settings);

		if (glewInit() != GLEW_OK)
		{
			std::cerr << "Can't initialize glew, error in file " << __FILE__ << ", line " << __LINE__ << std::endl;
			throw std::exception();
		}

		DisplayManager::Projection	= glm::perspective(70.0, static_cast<double>(DisplayManager::Width) / static_cast<double>(DisplayManager::Height), 1.0, 100.0);
		DisplayManager::ModelView	= glm::mat4(1.0);

		DisplayManager::IsInstantiated = true;
	}
	// Only one window can be created
	else
	{
		std::cerr << "A window has already been instantiated\n";
	}
}

void DisplayManager::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
	DisplayManager::ModelView = glm::mat4(1.0);
}

void DisplayManager::Display()
{
	DisplayManager::Window.display();
}

void DisplayManager::Destroy()
{
	DisplayManager::IsInstantiated = false;
}
