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

	virtual void update(const sf::Vector2f mousePos);
	virtual void render(sf::RenderTarget* target);

	/* Getter */
	bool getPressed() const;

private:
	/* Shape of the button (area) */
	sf::RectangleShape m_shape;
	
	sf::Font *m_font;
	sf::Text m_text;
	sf::Color m_textColor;
	int m_textSize;

	sf::Color m_idleColor;
	sf::Color m_hoverColor;
	sf::Color m_activeColor;

	bool m_pressed;
};

#endif // !_BUTTON_H_
