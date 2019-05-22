#include "pch.h"
#include "DisplayManager.h"

// Matrix4
glm::mat4 DisplayManager::Projection;
glm::mat4 DisplayManager::ModelView;
// Vector3
glm::vec3 DisplayManager::Eyes(3, 3, 3);
glm::vec3 DisplayManager::Center(0, 0, 0);
glm::vec3 DisplayManager::Axe(0, 1, 0);
// FPS Management
unsigned DisplayManager::FpsCap(120);
// Window and OpenGl
sf::ContextSettings DisplayManager::Settings;
sf::RenderWindow DisplayManager::Window;
unsigned DisplayManager::Width(0);
unsigned DisplayManager::Height(0);
// Internal state boolean
bool DisplayManager::IsInstantiated(false);
bool DisplayManager::IsRunning(true);

void DisplayManager::Create(unsigned w, unsigned h)
{
	if (!IsInstantiated)
	{	
		Width = w;
		Height = h;

		// Update the window
		Window.create(sf::VideoMode(w, h), "OpenGL de ses morts", sf::Style::Default, Settings);

		if (glewInit() != GLEW_OK)
		{
			std::cerr << "Can't initialize glew, error in file " << __FILE__ << ", line " << __LINE__ << std::endl;
			throw std::exception();
		}

		Window.setFramerateLimit(FpsCap);

		glEnable(GL_DEPTH_TEST);

		Projection	= glm::perspective(70.0, static_cast<double>(Width) / Height, 1.0, 100.0);
		ModelView	= glm::mat4(1.0);

		IsInstantiated = true;
	}
	// Only one window can be created
	else
	{
		std::cerr << "A window has already been instantiated\n";
	}
}

void DisplayManager::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	ModelView = glm::lookAt(Eyes, Center, Axe);
}

void DisplayManager::Display()
{
	Window.display();
}

void DisplayManager::Destroy()
{
	IsInstantiated = false;
}
