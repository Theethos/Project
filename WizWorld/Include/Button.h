#ifndef _BUTTON_H_
#define _BUTTON_H_

#define _REQUIRE_SFML_
	#include "Macro_Include.h"
#undef _REQUIRE_SFML_

class Button
{
public:
	Button(float x, float y, float w, float h, std::string text,
		   sf::Font *font, sf::Color idleColor, sf::Color hoverColor,
		   sf::Color activeColor, sf::Color textColor, int textSize);
	virtual ~Button();

	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
	void activate();
	void deactivate();

	/* Getter */
	bool getPressed() const;
	bool getActivated() const;

private:
	/* Shape of the button (area) */
	sf::RectangleShape shape;
	
	sf::Font *font;
	sf::Text text;
	sf::Color textColor;
	int textSize;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

	bool pressed;
	bool click;
	bool activated;
};

#endif // !_BUTTON_H_
