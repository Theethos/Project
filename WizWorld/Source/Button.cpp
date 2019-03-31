#include "../Include/Button.h"

/*	Constructor
	Parameters : 
	- x, y -> position
	- w, h -> size
	- text, text_size and font -> text on the button 
	- idle_color -> main color 
	- hover_color -> color when the mouse is over the button 
	- active_color -> color when we click on the button */
Button::Button(float x, float y, float w, float h, std::string text,
	sf::Font *font, sf::Color idleColor, sf::Color hoverColor,
	sf::Color activeColor, sf::Color textColor, int textSize)
	: m_font(font), m_idleColor(idleColor), m_hoverColor(hoverColor), m_activeColor(activeColor),
	m_textColor(textColor), m_textSize(textSize), m_pressed(false), m_click(false)
{
	m_shape.setSize(sf::Vector2f(w, h));
	m_shape.setPosition(sf::Vector2f(x, y));
	m_shape.setFillColor(m_idleColor);

	m_text.setFont(*m_font);
	m_text.setString(text);
	m_text.setFillColor(m_textColor);
	m_text.setCharacterSize(m_textSize);
	m_text.setPosition(sf::Vector2f(m_shape.getPosition().x + (m_shape.getGlobalBounds().width / 2.f - m_text.getGlobalBounds().width / 2.f),
									m_shape.getPosition().y + (m_shape.getGlobalBounds().height / 2.f - m_text.getGlobalBounds().height / 1.35)
	));
}

/* Destructor */
Button::~Button()
{}

/* Functions */
void Button::update(const sf::Vector2f mousePos)
{
	/* Set button to idle_color */
	m_shape.setFillColor(m_idleColor);
	/* If the mouse is over the button */
	if (m_shape.getGlobalBounds().contains(mousePos))
	{
		/* If the user clicks over the button */
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_click = true;
		}
		/* When user released the click and he is still over the button (simulate mouse button up event) */
		else if (sf::Event::MouseButtonReleased && m_click)
		{
			/* Set to active_color */
			m_shape.setFillColor(m_activeColor);
			m_pressed = true;
			m_click = false;
		}
		/* Else set it to hover_color */
		else
		{
			m_shape.setFillColor(m_hoverColor);
			if (m_pressed)
				m_pressed = false;
		}
	}
	/* Else, if user clicked on the button but is not over it anymore */
	else
	{
		// Reset the click (because it means the user didn't want to click on this button
		if (m_click)
		{
			m_click = false;
		}
	}
}

void Button::render(sf::RenderTarget * target)
{
	if (target)
	{
		target->draw(m_shape);
		target->draw(m_text);
	}		
}

bool Button::getPressed() const
{
	return m_pressed;
}
