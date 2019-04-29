#ifndef BUTTON_TEXT_H
#define BUTTON_TEXT_H

#include "../Include/Button.h"

class TextField : public Button
{
public:
	// Constructor
	TextField(float x = 0, float y = 0, float w = 0, float h = 0, std::string text = "", sf::Font *font = nullptr,
			  sf::Color idleColor = sf::Color::White, sf::Color hoverColor = sf::Color::White, sf::Color activeColor = sf::Color::White,
			  int textSize = 0, sf::RenderWindow* window = nullptr, bool only_letter = false);
	// Destructor
	virtual ~TextField();

	// Functions
	void Update(const sf::Vector2f mousePos);
	void Render(sf::RenderTarget* target);
	void Blink();

	// Getter
	const std::string& getTextEntered() const;

	// Setter
	inline void setMaxSize(int value) { this->maxSize = value; }
	inline void setRenderColor(sf::Color color) { this->textEnteredToRender.setFillColor(color); }
	inline void setTextEntered(std::string text) { this->textEntered = text; this->textEnteredToRender.setString(text); }
	void setPosition(float x, float y);

private:
	// Main window
	sf::RenderWindow* window;

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
	bool _onlyLetter;
	
	// Private functions
	void AddChar(char character);
	void RemoveChar();
	void CaptureText();
};

#endif // !BUTTON_TEXT_H
