#include "../Include/State.h"

/*
 * ==================================================
 * =================== Class State ==================
 * ==================================================
 */

State::State(sf::RenderWindow* window, std::map < std::string, int> *keys, std::stack<State*>* states)
	: m_window(window), m_quit(false), m_keys(keys), m_mousePosScreen(0, 0),
	  m_mousePosWindow(0, 0), m_mousePosView(0, 0), m_states(states)
{}

State::~State()
{}

void State::updateMousePositions()
{
	m_mousePosScreen = sf::Mouse::getPosition();
	m_mousePosWindow = sf::Mouse::getPosition(*m_window);
	m_mousePosView = m_window->mapPixelToCoords(m_mousePosWindow);
}

const bool& State::getQuit() const
{
	return m_quit;
}

