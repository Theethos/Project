#include "Precompiled_Header_OpenGL.h"
#include "DisplayManager.h"

SDL_GLContext DisplayManager::Settings;
SDL_Window * DisplayManager::Window	= nullptr;
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
			if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
			{
				std::cerr << "Can't initialize SDL, error in file " << __FILE__ << ", line " << __LINE__ << std::endl;
				throw std::exception();
			}
			
			SDL_GLprofile(SDL_GL_CONTEXT_PROFILE_CORE);
			SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

			DisplayManager::Width = w;
			DisplayManager::Height = h;

			DisplayManager::Window = SDL_CreateWindow("Hogwart's RPG in OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
			if (!DisplayManager::Window)
			{
				std::cerr << "Can't create the SDL_Window, error in file " << __FILE__ << ", line " << __LINE__ << std::endl;
				SDL_Quit();
				throw std::exception();
			}

			DisplayManager::Settings = SDL_GL_CreateContext(DisplayManager::Window);
			if (!DisplayManager::Settings)
			{
				std::cout << "Can't create the SDL_Contexte, error in file " << __FILE__ << ", line " << __LINE__ << std::endl;
				SDL_DestroyWindow(DisplayManager::Window);
				SDL_Quit();
				throw std::exception();
			}

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
	SDL_GL_SwapWindow(DisplayManager::Window);
}

void DisplayManager::Destroy()
{
	DisplayManager::IsInstantiated = false;
	SDL_GL_DeleteContext(DisplayManager::Settings);
	SDL_DestroyWindow(DisplayManager::Window);
	SDL_Quit();
}
