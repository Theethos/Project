#include "pch.h"

// Clear color
glm::vec4 DisplayManager::ClearColor(0.4, 0.9, 1.0, 1.0);///(0.4, 0.9, 1.0, 1.0); /// (0.4, 0.05, 0.05, 1.0);
// FPS Management
Uint32 DisplayManager::StartTime(0);
Uint32 DisplayManager::DeltaTime(0);
float DisplayManager::FpsCap(1000/60);			// (1000 / FpsDesired)
// Window and OpenGl
SDL_GLContext DisplayManager::Settings;
SDL_Window * DisplayManager::Window(nullptr);
unsigned DisplayManager::Width(0);
unsigned DisplayManager::Height(0);
// Internal state boolean
bool DisplayManager::IsInstantiated(false);
bool DisplayManager::IsRunning(true);
// Projection matrix
double DisplayManager::Fov(70.0);
double DisplayManager::AspectRatio((double)Width / (double)Height);
double DisplayManager::Near(0.1);
double DisplayManager::Far(1000.0);
glm::mat4 DisplayManager::ProjectionMatrix;

void DisplayManager::Create(unsigned w, unsigned h, const bool & fullscreen)
{
	if (!IsInstantiated)
	{
		// Initialize the SDL
		if (SDL_Init( SDL_INIT_EVERYTHING ) < 0)
		{
			std::cout << "Can't initialize SDL, error in file " << __FILE__ << ", line " << __LINE__ << std::endl;
			throw std::exception("Can't initialize SDL");
		}

		// Set OpenGL's version
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		
		// Set OpenGL' profile to core
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		// Set double buffering
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		Width = w;
		Height = h;

		AspectRatio = (double)w / (double)h;
		std::cout << AspectRatio << std::endl;

		ProjectionMatrix = glm::perspective(Fov, AspectRatio, Near, Far);

		unsigned int flags;
		if (fullscreen)
			flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN;
		else
			flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;

		// Create the window
		Window = SDL_CreateWindow("Hogwart's RPG in OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, flags);
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

		if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
		{
			std::cerr << "Failed to initialize GLAD" << std::endl;
			throw std::exception("Failed to initialize GLAD");
		}

		glClearColor(ClearColor.x, ClearColor.y, ClearColor.z, ClearColor.w);
		glViewport(0, 0, w, h);
		glEnable(GL_DEPTH_TEST);

		IsInstantiated = true;
	}
	// Only one window can be created
	else
	{
		std::cerr << "A window has already been instantiated\n";
	}
}

void DisplayManager::StartLoop()
{
	if (IsInstantiated)
	{
		StartTime = SDL_GetTicks();
		InputManager::Update();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}

void DisplayManager::EndLoop()
{
	if (IsInstantiated)
	{
		SDL_GL_SwapWindow(Window);

		// Managing FPS
		DeltaTime = SDL_GetTicks() - StartTime;
		// Display the fps -> 
		SDL_SetWindowTitle(Window, ("FPS : " + std::to_string(( 1 / (DeltaTime / 1000.f)))).c_str());
		//if (DeltaTime < FpsCap)
			//SDL_Delay(FpsCap - DeltaTime);
	}
}

void DisplayManager::Destroy()
{
	if (IsInstantiated)
	{
		IsInstantiated = false;
		SDL_GL_DeleteContext(Settings);
		SDL_DestroyWindow(Window);
		SDL_Quit();
	}
}
