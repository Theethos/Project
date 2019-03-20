#ifndef _STATE_H_
#define _STATE_H_

#define _REQUIRE_SFML_
	#include "Macros_Includes.h"
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
	State(sf::RenderWindow *window, std::map < std::string, int> *keys);
	virtual ~State();

	virtual void initializeActions() = 0;
	virtual void handleInput(const float &dt) = 0;
	virtual void update(const float &dt) = 0;
	virtual void render(sf::RenderTarget & target) = 0;
	virtual void checkForQuit();

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
};

#endif // !_STATE_H_

