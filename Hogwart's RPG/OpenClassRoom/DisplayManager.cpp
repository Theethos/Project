#include "pch.h"
#include "DisplayManager.h"

glm::mat4 DisplayManager::Projection;
glm::mat4 DisplayManager::ModelView;
glm::vec3 DisplayManager::Eyes(3,3,3), DisplayManager::Center(0,0,0), DisplayManager::Axe(0,1,0);
SDL_GLContext DisplayManager::Settings;
SDL_Window * DisplayManager::Window	= nullptr;
bool DisplayManager::IsInstantiated	= false;
bool DisplayManager::IsRunning		= true;
unsigned DisplayManager::Width		= 0;
unsigned DisplayManager::Height		= 0;
unsigned DisplayManager::FpsCap		= 120;

void DisplayManager::Create(unsigned w, unsigned h)
{
	if (!IsInstantiated)
	{
		auto tStart = std::chrono::high_resolution_clock::now();
		// Initialize the SDL
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			std::cout << "Can't initialize SDL, error in file " << __FILE__ << ", line " << __LINE__ << std::endl;
			throw std::exception("Can't initialize SDL");
		}
		std::chrono::duration<double> duree = std::chrono::high_resolution_clock::now() - tStart;
		std::cout << static_cast<double>(duree.count()) << std::endl;
		//SDL_GLprofile(SDL_GL_CONTEXT_PROFILE_CORE);

		// Set OpenGL's version
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		// Set double buffering
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		Width = w;
		Height = h;

		// Create the window
		Window = SDL_CreateWindow("Hogwart's RPG in OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
		if (!Window)
		{
			std::cerr << "Can't create the SDL_Window, error in file " << __FILE__ << ", line " << __LINE__ << std::endl;
			SDL_Quit();
			throw std::exception("Can't create the SDL_Window");
		}

		// Create the OpenGL's context
		Settings = SDL_GL_CreateContext(Window);
		if (!Settings)
		{
			std::cout << "Can't create the SDL_Context, error in file " << __FILE__ << ", line " << __LINE__ << std::endl;
			SDL_DestroyWindow(Window);
			SDL_Quit();
			throw std::exception("Can't create the SDL_Context");
		}

		if (glewInit() != GLEW_OK)
		{
			std::cerr << "Can't initialize glew, error in file " << __FILE__ << ", line " << __LINE__ << std::endl;
			throw std::exception();
		}

		glEnable(GL_DEPTH_TEST);

		Projection	= glm::perspective(70.0, static_cast<double>(Width) / Height, 1.0, 100.0);
		ModelView	= glm::mat4(1.0);

		//glEnable(GL_DEPTH_TEST);

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
	SDL_GL_SwapWindow(Window);
}

void DisplayManager::Destroy()
{
	IsInstantiated = false;
	SDL_GL_DeleteContext(Settings);
	SDL_DestroyWindow(Window);
	SDL_Quit();
}
