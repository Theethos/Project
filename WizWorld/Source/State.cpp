#include "../Include/Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/State.h"

State::State(sf::RenderWindow* window, std::map < std::string, int> *keys, std::stack<State*>* states)
	: window(window), quit(false), keys(keys), mousePosScreen(0, 0),
	  mousePosWindow(0, 0), mousePosView(0, 0), states(states)
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

