#ifndef _MENU_STATE_H_
#define _MENU_STATE_H_

#include "GameState.h"
#include "TextField.h"
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
	void HandleInput(int input, const float &dt);

	// Getter
	const Menu & getMenuType() const;

private:
	Menu menuType;
	sf::RectangleShape background;
	std::map<std::string,sf::Font> font;
	std::map<std::string, Button*> buttons;
	int numberOfButtons;
	sf::Text title;
	std::string configFile;
	// The button that is activated in the character menu
	Button *activatedButton;
	// The class associated to the selected button
	std::string activatedClass;
	// The sprites in the character menu
	std::map<std::string, sf::Sprite*> sprites;
	// The sprite's animation that has to be displayed in the character menu
	std::map<std::string, AnimationComponent*> spritesAnimation;
	// Scale of the sprite in the character menu
	int spriteScale;
	// Background behind the sprites to help vizualize them
	sf::RectangleShape spritesBackground;
	sf::Cursor cursor;
	// Button that has the "focus"
	std::pair<int, int> selectedButton;
	std::vector<std::vector<std::string>> buttonsText;
	bool movedX, movedY;
	
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
};

#endif // !_MENU_STATE_H_

