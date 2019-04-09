#ifndef _MENU_STATE_H_
#define _MENU_STATE_H_

#include "GameState.h"
#include "Button.h"
#include "AnimationComponent.h"

enum class Menu {NONE, MAIN_MENU, PAUSE_MENU, CHARACTER_MENU};

class MenuState : public State
{
public:
	MenuState(sf::RenderWindow *window, std::map < std::string, int> *keys, std::stack<State*> *states, std::string configFile, Menu currentMenu);
	virtual ~MenuState();

	void handleInput(const float &dt);
	void update(const float &dt);
	void updateButtons();
	void render(sf::RenderTarget* target = nullptr);
	void renderButtons(sf::RenderTarget* target = nullptr);
	
	void initFonts();
	void initButtons();
	void initTitle();
	void initSprites();

private:
	Menu currentMenu;
	sf::RectangleShape background;
	sf::Texture backgroundTexture;
	sf::Font font;
	std::map<std::string, Button*> buttons;
	int numberOfButtons;
	sf::Text title;
	std::string configFile;
	// The button that is activated in the "choose character" menu
	Button *currentClassButton;
	// The sprite's animation that has to be displayed in the "choose character" menu
	AnimationComponent* currentSpriteAnimation;
	sf::Sprite* menuSprite;

};

#endif // !_MENU_STATE_H_

