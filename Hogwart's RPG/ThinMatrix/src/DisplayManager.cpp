#include "pch.h"

// Clear color
glm::vec4 DisplayManager::DayClearColor(0.9, 0.9, 0.9, 1.0);///(0.4, 0.9, 1.0, 1.0); /// (0.4, 0.05, 0.05, 1.0);
glm::vec4 DisplayManager::NightClearColor(0.0, 0.0, 0.0, 1.0);
glm::vec4 DisplayManager::FogColor(0.0, 0.0, 0.0, 1.0);
float DisplayManager::BlendFactor(0);
// FPS Management
Uint32 DisplayManager::StartTime(0);
Uint32 DisplayManager::DeltaTime(0);
double DisplayManager::Time(250.0);
float DisplayManager::FpsCap(1000/60);			// (1000 / FpsDesired)
// Window and OpenGl
SDL_GLContext DisplayManager::Settings;
SDL_Window * DisplayManager::Window(nullptr);
unsigned DisplayManager::Width(0);
unsigned DisplayManager::Height(0);
// Internal state boolean
bool DisplayManager::IsInstantiated(false);
bool DisplayManager::IsRunning(true);
bool DisplayManager::WireframeMode(false);
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

		// Set the window to fullscreen if no size is given
		if (!w && !h)
		{
			SDL_DisplayMode display_mode;
			SDL_GetDesktopDisplayMode(0, &display_mode);

			w = display_mode.w;
			h = display_mode.h;
		}

		Width = w;
		Height = h;
		AspectRatio = (double)w / (double)h;

		ProjectionMatrix = glm::perspective(glm::radians(Fov), AspectRatio, Near, Far);

		unsigned int flags;
		if (fullscreen)
			flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP;
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

		glClearColor(DayClearColor.x, DayClearColor.y, DayClearColor.z, DayClearColor.w);
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
		ToggleModes();
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
		if (DeltaTime < FpsCap)
			SDL_Delay(FpsCap - DeltaTime);
		SetFogColor();
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

void DisplayManager::ToggleModes()
{
	if (GetKeyOnce(SDL_SCANCODE_Z))
	{
		if (WireframeMode)
		{
			WireframeMode = false;
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		else
		{
			WireframeMode = true;
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
	}
}

void DisplayManager::SetFogColor()
{
	Time += (double)DeltaTime / 1000.f;
	Time = std::fmodf(Time, 500.f);
	if (Time >= 0 && Time < 230.f)
		BlendFactor = 1.f;
	else if (Time >= 230.f && Time < 250.f)
		BlendFactor = (Time - 250.f) / (230.f - 250.f);
	else if (Time >= 250.f && Time < 480.f)
		BlendFactor = 0.f;
	else
		BlendFactor = (Time - 480.f) / (500.f - 480.f);
	FogColor = DayClearColor * (1 - BlendFactor) + NightClearColor * BlendFactor;
}