#include "pch.h"
#include "DisplayManager.h"

/////////////////////////////////////////////////////
/// STATIC CLASS
/////////////////////////////////////////////////////
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
		else if (EventManager::Event.type == sf::Event::KeyPressed)
		{
			switch (EventManager::Event.key.code)
			{
			case sf::Keyboard::Z:  DisplayManager::IsRunning = false;  break;
			case sf::Keyboard::Q:  DisplayManager::IsRunning = false;  break;
			case sf::Keyboard::S:  DisplayManager::IsRunning = false;  break;
			case sf::Keyboard::D:  DisplayManager::IsRunning = false;  break;
			default:												   break;
			}
		}
	}
}

void EventManager::Destroy() 
{
	EventManager::IsInstantiated = false;
}
