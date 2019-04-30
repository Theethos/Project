#ifndef BUTTON_TEXT_H
#define BUTTON_TEXT_H

#include "../Include/Button.h"

class TextField : public Button
{
public:
	// Constructor
	TextField(sf::RenderWindow& window, sf::Font& font, float x = 0, float y = 0, float width = 0, float height = 0, std::string text = "",
			  sf::Color idle_color = sf::Color::White, sf::Color hover_color = sf::Color::White, sf::Color active_color = sf::Color::White,
			  int text_size = 0, bool only_letter = false);
	// Destructor
	virtual ~TextField();

	// Functions
	void Update(const sf::Vector2f mouse_position);
	void Render(sf::RenderTarget& target);
	void Blink();

	// Getter
	inline std::string& GetTextEntered() { return m_TextEntered; }
	inline std::string GetTextEnteredConst() const { return m_TextEntered; }

	// Setter
	inline void SetMaxSize(const int value) { m_MaxSize = value; }
	inline void SetRenderColor(const sf::Color color) { m_TextRendered.setFillColor(color); }
	inline void SetTextEntered(const std::string text) { m_TextEntered = text; m_TextRendered.setString(text); }
	void SetPosition(float x, float y);

private:
	// Main window
	sf::RenderWindow& m_Window;

	// Text entered
	std::string m_TextEntered;
	sf::Text m_TextRendered;
	// Maximum size of the text entered
	int m_MaxSize;
	// Background when the text is entered
	sf::Color m_BackgroundColor;
	
	// Thread managing
	sf::Thread m_Thread;
	sf::Mutex m_Mutex;
	
	// States of the button
	bool m_Running;
	bool m_Blinking;
	bool m_OnlyLetter;
	
	// Private functions
	void AddChar(const char character);
	void RemoveChar();
	void CaptureText();
};

#endif // !BUTTON_TEXT_H
