#ifndef _BUTTON_H_
#define _BUTTON_H_

class Button
{
public:
	// Construtor
	Button(float x, float y, float width, float height, std::string text, sf::Font& font, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, int textSize);
	// Destructor
	virtual ~Button();

	// Functions
	virtual void Update(const sf::Vector2f mouse_position);
	virtual void Render(sf::RenderTarget& target);
	inline virtual void Activate() { if (!m_Activated) m_Activated = true; }
	inline virtual void Deactivate() { if (m_Activated) m_Activated = false;}

	// Getters
	inline sf::Vector2f GetPosition() const { return m_Shape.getPosition(); }
	inline sf::Vector2f GetSize() const { return m_Shape.getSize(); }
	inline bool GetPressed() const { return m_Pressed; }
	inline bool GetActivated() const { return m_Activated; }
	inline bool GetHovered() const { return m_Hovered; }
	inline bool GetSelected() const { return m_Selected; }

	// Setters
	inline void SetPressed(const bool pressed) { m_Pressed = pressed; }
	inline void SetHovered(const bool hovered) { m_Hovered = hovered; }
	inline void SetSelected(const bool selected) { m_Selected = selected; }

protected:
	// Shape of the button
	sf::RectangleShape m_Shape;
	
	// Text of the button
	sf::Font& m_Font;
	sf::Text m_Text;
	int m_TextSize;
	
	// Colors of the button
	sf::Color m_IdleColor;
	sf::Color m_HoverColor;
	sf::Color m_ActiveColor;

	// States of the button
	bool m_Pressed;
	bool m_Clicked;
	bool m_Activated;
	bool m_Hovered;
	bool m_Selected;
};

#endif // !_BUTTON_H_
