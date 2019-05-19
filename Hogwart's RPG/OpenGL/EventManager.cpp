#include "Precompiled_Header_OpenGL.h"
#include "EventManager.h"
#include "DisplayManager.h"

bool EventManager::IsInstantiated = false;
SDL_Event EventManager::Event;

void EventManager::Create() 
{
	try
	{
		if (!EventManager::IsInstantiated)
			EventManager::IsInstantiated = true;
		else
			throw std::exception("An EventManager has already been instantiated\n");
	}
	catch (std::exception & e)
	{
		std::cout << e.what();
	}
}

void EventManager::Update() 
{
	while (SDL_PollEvent(&EventManager::Event))
	{
		if (EventManager::Event.window.event == SDL_WINDOWEVENT_CLOSE)
			DisplayManager::IsRunning = false;
		else if (EventManager::Event.type == SDL_KEYUP)
		{
			switch (EventManager::Event.key.keysym.sym)
			{
			case SDLK_ESCAPE:	DisplayManager::IsRunning = false;	break;
			default:												break;
			}
		}
	}
}

void EventManager::Destroy() 
{
	EventManager::IsInstantiated = false;
}

EventManager::EventManager() {}

EventManager::~EventManager() {}
