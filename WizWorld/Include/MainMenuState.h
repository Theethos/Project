#ifndef _MAIN_MENU_STATE_H
#define _MAIN_MENU_STATE_H

#include "State.h"
#include "Button.h"


/*
 * ==================================================
 * =============== Class MainMenuState ==============
 * ==================================================
 */

class MainMenuState : public State
{
public:
	MainMenuState(sf::RenderWindow *window, std::map < std::string, int> *keys);
	virtual ~MainMenuState();

	virtual void handleInput(const float &dt);
	virtual void update(const float &dt);
	virtual void render(sf::RenderTarget* target);
	virtual void addState(State* state);
	
	void initializeActions();
	void initializeFonts();
	void initializeButtons();



private:
	sf::RectangleShape m_background;
	sf::Font m_font;
	Button **m_buttons;
	std::map <std::string, int> m_buttonText;

};

#endif // !_MAIN_MENU_STATE_H

