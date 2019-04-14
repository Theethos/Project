#ifndef _BUTTON_H_
#define _BUTTON_H_

class Button
{
public:
	Button(float x, float y, float w, float h, std::string text,
		   sf::Font *font, sf::Color idleColor, sf::Color hoverColor,
		   sf::Color activeColor, int textSize);
	virtual ~Button();

	virtual void update(const sf::Vector2f mousePos);
	virtual void render(sf::RenderTarget* target);
	virtual void activate();
	virtual void deactivate();

	/* Getter */
	bool getPressed() const;
	bool getActivated() const;
	bool getHovered() const;
	sf::Vector2f getPosition() const;
	sf::Vector2f getSize() const;	

	// Setter
	void setPressed(bool pressed);

protected:
	/* Shape of the button (area) */
	sf::RectangleShape shape;
	
	sf::Font *font;
	sf::Text text;
	int textSize;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

	bool pressed;
	bool click;
	bool activated;
	bool hovered;
};

#endif // !_BUTTON_H_
