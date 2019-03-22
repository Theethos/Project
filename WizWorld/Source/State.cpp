#include "../Include/State.h"

/*
 * ==================================================
 * =================== Class State ==================
 * ==================================================
 */

State::State(sf::RenderWindow* window, std::map < std::string, int> *keys) 
	: m_window(window), m_quit(false), m_keys(keys), m_add(nullptr),
	  m_mousePosScreen(0,0), m_mousePosWindow(0,0), m_mousePosView(0,0)
{}

State::~State()
{}

void State::checkForQuit(const float &dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_actions["END_STATE"])))
	{
		m_quit = true;
	}
}

void State::updateMousePositions()
{
	m_mousePosScreen = sf::Mouse::getPosition();
	m_mousePosWindow = sf::Mouse::getPosition(*m_window);
	m_mousePosView = m_window->mapPixelToCoords(m_mousePosWindow);
}

void State::addState(State * state)
{
	m_add = state;
}

const bool& State::getQuit() const
{
	return m_quit;
}

State * State::getAdd() const
{
	return m_add;
}

void State::resetAdd()
{
	m_add = nullptr;
}

