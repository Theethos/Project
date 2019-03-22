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
	State(sf::RenderWindow *window, std::map < std::string, int> *keys);
	virtual ~State();

	virtual void initializeActions() = 0;
	virtual void handleInput(const float &dt) = 0;
	virtual void update(const float &dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;

	virtual void updateMousePositions();
	virtual void addState(State* state);
	virtual void checkForQuit(const float &dt);

	/*=== Getters ===*/

	const bool& getQuit() const;
	State* getAdd() const;
	void resetAdd();

protected:
	sf::RenderWindow *m_window;
	/* If the state wants to quit */
	bool m_quit;
	/* Supported keys */
	std::map < std::string, int> *m_keys;
	/* Actions associated to those keys */
	std::map < std::string, int> m_actions;
	/* State to add in the stack */
	State *m_add;
	/* Mouse positions */
	sf::Vector2i m_mousePosScreen;
	sf::Vector2i m_mousePosWindow;
	sf::Vector2f m_mousePosView;
};

#endif // !_STATE_H_

