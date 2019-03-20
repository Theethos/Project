#include "../Include/States.h"

/*
 * ==================================================
 * =================== Class State ==================
 * ==================================================
 */

State::State(sf::RenderWindow* window, std::map < std::string, int> *keys) : m_window(window), m_quit(false), m_keys(keys)
{}

State::~State()
{}

void State::checkForQuit()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		m_quit = true;
	}
}

const bool& State::getQuit() const
{
	return m_quit;
}

