#ifndef _MENU_STATE_H_
#define _MENU_STATE_H_

#include "GameState.h"
#include "Button.h"
#include "AnimationComponent.h"

enum class Menu {NONE, MAIN_MENU, PAUSE_MENU, CHARACTER_MENU};

class MenuState : public State
{
public:
	MenuState(sf::RenderWindow *window, std::map < std::string, int> *keys, std::stack<State*> *states, std::string configFile, Menu menuType);
	virtual ~MenuState();


	void handleInput(const float &dt);
	void update(const float &dt);
	void updateButtons();
	void render(sf::RenderTarget* target = nullptr);
	void renderButtons(sf::RenderTarget* target);
	void renderSprites(sf::RenderTarget* target);

	void useSelectedSprite();

	void initFonts();
	void initButtons();
	void initTitle();
	void initSprites();
	void initAnimations();

private:
	Menu menuType;
	sf::RectangleShape background;
	sf::Texture backgroundTexture;
	sf::Font font;
	std::map<std::string, Button*> buttons;
	int numberOfButtons;
	sf::Text title;
	std::string configFile;
	// The button that is activated in the character menu
	Button *selectedButton;
	// The class associated to the selected button
	std::string selectedClass;
	// The sprites in the character menu
	std::map<std::string, sf::Sprite*> sprites;
	// The sprite's animation that has to be displayed in the character menu
	std::map<std::string, AnimationComponent*> spritesAnimation;
	// Scale of the sprite in the character menu
	int spriteScale;
	// Background behind the sprites to help vizualize them
	sf::RectangleShape spritesBackground;


};

#endif // !_MENU_STATE_H_

