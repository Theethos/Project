#ifndef _BUTTON_H_
#define _BUTTON_H_

class Button
{
public:
	// Construtor
	Button(float x, float y, float w, float h, std::string text, sf::Font *font, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, int textSize);
	// Destructor
	virtual ~Button();

	// Functions
	virtual void Update(const sf::Vector2f mousePos);
	virtual void Render(sf::RenderTarget* target);
	virtual void Activate();
	virtual void Deactivate();

	// Getters
	bool getPressed() const;
	bool getActivated() const;
	bool getHovered() const;
	bool getSelected() const;
	sf::Vector2f getPosition() const;
	sf::Vector2f getSize() const;	

	// Setters
	void setPressed(bool pressed);
	void setHovered(bool hovered);
	void setSelected(bool selected);

protected:
	// Shape of the button
	sf::RectangleShape shape;
	
	// Text of the button
	sf::Font *font;
	sf::Text text;
	int textSize;
	
	// Colors of the button
	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

	// States of the button
	bool pressed;
	bool clicked;
	bool activated;
	bool hovered;
	bool selected;
};

#endif // !_BUTTON_H_
