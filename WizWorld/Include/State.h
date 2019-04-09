#ifndef _STATE_H_
#define _STATE_H_

#define _REQUIRE_SFML_
	#include "Macro_Include.h"
#undef _REQUIRE_SFML_

#include <stack>

class State
{
public:
	State(sf::RenderWindow *window, std::map < std::string, int> *keys, std::stack<State*>* states);
	virtual ~State();

	virtual void handleInput(const float &dt) = 0;
	virtual void update(const float &dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;

	virtual void updateMousePositions();

	/*=== Getters ===*/

	const bool& getQuit() const;

protected:
	sf::RenderWindow *window;
	/* If the state wants to quit */
	bool quit;
	/* Supported keys */
	std::map < std::string, int> *keys;
	/* Actions associated to those keys */
	std::map < std::string, int> actions;
	/* Mouse positions */
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	/* Pointer to the stack of States */
	std::stack<State*>* states;
};

#endif // !_STATE_H_

