#ifndef BUTTON_TEXT_H
#define BUTTON_TEXT_H

#include "../Include/Button.h"


class ButtonText : public Button
{
public:
	ButtonText(float x, float y, float w, float h, std::string text,
		sf::Font *font, sf::Color idleColor, sf::Color hoverColor,
		sf::Color activeColor, int textSize, sf::Window* window);
	~ButtonText();

	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);

	void addChar(char character);
	void removeChar();
	void captureText();
	void blink();

	// Getter
	const std::string& getTextEntered() const;

private:
	sf::Window* window;
	sf::Text textEnteredToRender;
	std::string textEntered;
	sf::Thread thread;
	bool threaded;
	bool blinking;
	int maxSize;
	sf::Color backgroundColor;
};

#endif // !BUTTON_TEXT_H
