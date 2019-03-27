#ifndef _STATE_H_
#define _STATE_H_

#define _REQUIRE_SFML_
	#include "Macro_Include.h"
#undef _REQUIRE_SFML_

#include <stack>

/*
 * ==================================================
 * =================== Class State ==================
 * ==================================================
 */

class State
{
public:
	State(sf::RenderWindow *window, std::map < std::string, int> *keys, std::stack<State*>* states);
	virtual ~State();

	virtual void handleInput(const double &dt) = 0;
	virtual void update(const double &dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;

	virtual void updateMousePositions();

	/*=== Getters ===*/

	const bool& getQuit() const;

protected:
	sf::RenderWindow *m_window;
	/* If the state wants to quit */
	bool m_quit;
	/* Supported keys */
	std::map < std::string, int> *m_keys;
	/* Actions associated to those keys */
	std::map < std::string, int> m_actions;
	/* Mouse positions */
	sf::Vector2i m_mousePosScreen;
	sf::Vector2i m_mousePosWindow;
	sf::Vector2f m_mousePosView;
	/* Pointer to the stack of States */
	std::stack<State*>* m_states;
};

#endif // !_STATE_H_

