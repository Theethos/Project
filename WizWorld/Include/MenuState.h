#ifndef _MENU_STATE_H_
#define _MENU_STATE_H_

#include "GameState.h"
#include "Button.h"


/*
 * ==================================================
 * =============== Class MenuState ==============
 * ==================================================
 */

class MenuState : public State
{
public:
	MenuState(sf::RenderWindow *window, std::map < std::string, int> *keys, std::stack<State*>* states, std::string configFile);
	virtual ~MenuState();

	void handleInput(const float &dt);
	void update(const float &dt);
	void updateButtons();
	void render(sf::RenderTarget* target = nullptr);
	void renderButtons(sf::RenderTarget* target = nullptr);
	
	void initializeFonts();
	void initializeButtons();
	void initializeTitle();

private:
	sf::RectangleShape m_background;
	sf::Texture m_backgroundTexture;
	sf::Font m_font;
	std::map<std::string, Button*> m_buttons;
	int m_numberOfButtons;
	sf::Text m_title;
	std::string m_configFile;
};

#endif // !_MENU_STATE_H_

