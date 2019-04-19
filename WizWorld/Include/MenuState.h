#ifndef _MENU_STATE_H_
#define _MENU_STATE_H_

#include "GameState.h"
#include "ButtonText.h"
#include "AnimationComponent.h"

class MenuState : public State
{
public:
	// Constructor
	MenuState(sf::RenderWindow *window, std::stack<State*> *states, WhichState state, std::string configFile, Menu menuType);
	// Destructor
	virtual ~MenuState();

	// Functions
	void Update(const float &dt);
	void Render(sf::RenderTarget* target = nullptr);

	// Getter
	const Menu & getMenuType() const;

private:
	Menu menuType;
	sf::RectangleShape background;
	sf::Texture backgroundTexture;
	std::map<std::string,sf::Font> font;
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
	sf::Cursor cursor;
	
	// Private functions
	void UpdateButtons();
	void UpdateCursor();
	void RenderButtons(sf::RenderTarget* target);
	void RenderSprites(sf::RenderTarget* target);
	void InitFonts();
	void InitButtons();
	void InitTitle();
	void InitSprites();
	void InitAnimations();
	void HandleKeyboardInput(const float &dt);
	void HandleControllerInput(const float &dt);
};

#endif // !_MENU_STATE_H_

