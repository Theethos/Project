#ifndef BUTTON_TEXT_H
#define BUTTON_TEXT_H

#include "../Include/Button.h"

class ButtonText : public Button
{
public:
	// Constructor
	ButtonText(float x, float y, float w, float h, std::string text, sf::Font *font, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, int textSize, sf::Window* window);
	// Destructor
	virtual ~ButtonText();

	// Functions
	void Update(const sf::Vector2f mousePos);
	void Render(sf::RenderTarget* target);
	void Blink();

	// Getter
	const std::string& getTextEntered() const;

private:
	// Main window
	sf::Window* window;

	// Text entered
	std::string textEntered;
	sf::Text textEnteredToRender;
	// Maximum size of the text entered
	int maxSize;
	// Background when the text is entered
	sf::Color backgroundColor;
	
	// Thread managing
	sf::Thread thread;
	sf::Mutex mutex;
	
	// States of the button
	bool threadIsRunning;
	bool blinking;
	
	// Private functions
	void AddChar(char character);
	void RemoveChar();
	void CaptureText();
};

#endif // !BUTTON_TEXT_H
