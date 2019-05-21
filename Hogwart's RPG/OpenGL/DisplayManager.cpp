#include "Precompiled_Header_OpenGL.h"
#include "DisplayManager.h"

sf::ContextSettings DisplayManager::Settings(24, 8, 0, 3, 3);
sf::RenderWindow DisplayManager::Window(sf::VideoMode(DisplayManager::Width, DisplayManager::Height), "OpenGL de ses morts", sf::Style::Default, DisplayManager::Settings);
bool DisplayManager::IsInstantiated	= false;
bool DisplayManager::IsRunning		= true;
unsigned DisplayManager::Width		= 0;
unsigned DisplayManager::Height		= 0;
unsigned DisplayManager::FpsCap		= 120;

DisplayManager::DisplayManager() {}

DisplayManager::~DisplayManager() {}

void DisplayManager::Create(unsigned w, unsigned h)
{
	try
	{
		if (!DisplayManager::IsInstantiated)
		{
			DisplayManager::Width = w;
			DisplayManager::Height = h;

			DisplayManager::Window.setSize(sf::Vector2u(w, h));

			if (glewInit() != GLEW_OK)
			{
				std::cerr << "Can't initialize glew, error in file " << __FILE__ << ", line " << __LINE__ << std::endl;
				throw std::exception();
			}

			DisplayManager::IsInstantiated = true;
		}
		// Only one window can be created
		else
		{
			throw std::exception("A window is already instantiated\n");
		}
	}
	catch (std::exception &e)
	{
		std::cout << e.what();
	}
}

void DisplayManager::Update()
{
	DisplayManager::Window.display();
}

void DisplayManager::Destroy()
{
	DisplayManager::IsInstantiated = false;
}
