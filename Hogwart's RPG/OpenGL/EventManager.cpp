#include "Precompiled_Header_OpenGL.h"
#include "EventManager.h"
#include "DisplayManager.h"

bool EventManager::IsInstantiated = false;
sf::Event EventManager::Event;

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
	while (DisplayManager::Window.pollEvent(EventManager::Event))
	{
		if (EventManager::Event.type == sf::Event::Closed)
			DisplayManager::IsRunning = false;
		else if (EventManager::Event.type == sf::Event::KeyReleased)
		{
			switch (EventManager::Event.key.code)
			{
			case sf::Keyboard::Escape:	DisplayManager::IsRunning = false;	break;
			default:														break;
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
