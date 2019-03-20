#include "../Include/GameState.h"

/*
 * ==================================================
 * ================= Class GameState ================
 * ==================================================
 */

GameState::GameState(sf::RenderWindow *window, std::map < std::string, int> *keys) : State(window, keys), m_player()
{
	initializeActions();
}

GameState::~GameState()
{

}

void GameState::handleInput(const float &dt)
{
	checkForQuit();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_actions.at("MOVE_UP"))))
		m_player.move(dt, 0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_actions.at("MOVE_DOWN"))))
		m_player.move(dt, 0.f, 1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_actions.at("MOVE_LEFT"))))
		m_player.move(dt, -1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_actions.at("MOVE_RIGHT"))))
		m_player.move(dt, 1.f, 0.f);
}

void GameState::update(const float& dt)
{
	handleInput(dt);
	m_player.update(dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		std::cout << "A" << std::endl;
}

void GameState::render(sf::RenderTarget & target)
{
	m_player.render(target);
}

void GameState::initializeActions()
{
	m_actions.emplace("MOVE_UP", m_keys->at("Z"));
	m_actions.emplace("MOVE_LEFT", m_keys->at("Q"));
	m_actions.emplace("MOVE_DOWN", m_keys->at("S"));
	m_actions.emplace("MOVE_RIGHT", m_keys->at("D"));
}

