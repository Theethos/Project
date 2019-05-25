#include "pch.h"

// Matrix4
glm::mat4 DisplayManager::Projection;
glm::mat4 DisplayManager::ModelView;
glm::mat4 DisplayManager::SavedModelView;
// Clear color
glm::vec4 DisplayManager::ClearColor(0.4, 0.7, 1.0, 1.0);
// Camera
Camera DisplayManager::Camera(glm::vec3(3, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
double DisplayManager::Fovy(70.0);
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

void DisplayManager::Create(unsigned w, unsigned h)
{
	if (!IsInstantiated)
	{
		auto tStart = std::chrono::high_resolution_clock::now();
		// Initialize the SDL
		if (SDL_Init( SDL_INIT_EVERYTHING ) < 0)
		{
			std::cout << "Can't initialize SDL, error in file " << __FILE__ << ", line " << __LINE__ << std::endl;
			throw std::exception("Can't initialize SDL");
		}
		std::chrono::duration<double> duree = std::chrono::high_resolution_clock::now() - tStart;
		std::cout << static_cast<double>(duree.count()) << std::endl;

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

		glClearColor(ClearColor.x, ClearColor.y, ClearColor.z, ClearColor.w);
		glEnable(GL_DEPTH_TEST);

		Projection	= glm::perspective(Fovy, static_cast<double>(Width) / Height, 1.0, 100.0);
		ModelView	= glm::mat4(1.0);

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
	StartTime = SDL_GetTicks();
	InputManager::Update();
	Camera.Move();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Camera.LookAt();
}

void DisplayManager::EndLoop()
{
	SDL_GL_SwapWindow(Window);

	// Managing FPS
	DeltaTime = SDL_GetTicks() - StartTime;
	if (DeltaTime < FpsCap)
		SDL_Delay(FpsCap - DeltaTime);
}

void DisplayManager::Destroy()
{
	IsInstantiated = false;
	SDL_GL_DeleteContext(Settings);
	SDL_DestroyWindow(Window);
	SDL_Quit();
}

struct Zooms
{
	double none = 70.0;
	double in = 69.5;
	double out = 71.0;
} Zooms;

void DisplayManager::Zoom(const bool & in)
{
	if (in && (Fovy == static_cast<double>(Zooms.none)))
		Fovy = static_cast<double>(Zooms.in);
	else if (in && (Fovy == static_cast<double>(Zooms.out)))
		Fovy = static_cast<double>(Zooms.none);
	else if (!in && (Fovy == static_cast<double>(Zooms.none)))
		Fovy = static_cast<double>(Zooms.out);
	else if (!in && (Fovy == static_cast<double>(Zooms.in)))
		Fovy = static_cast<double>(Zooms.none);

	Projection = glm::perspective(Fovy, static_cast<double>(Width) / Height, 1.0, 100.0);
}
