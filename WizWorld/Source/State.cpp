#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/State.h"

State::State(sf::RenderWindow* window, std::map < std::string, int> *keys, std::stack<State*>* states, WhichState state)
	: window(window), quit(false), keys(keys), mousePosScreen(0, 0),
	  mousePosWindow(0, 0), mousePosView(0, 0), states(states), state(state)
{}

State::~State()
{}

void State::updateMousePositions()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

const bool& State::getQuit() const
{
	return this->quit;
}

const WhichState & State::getState() const
{
	return this->state;
}
