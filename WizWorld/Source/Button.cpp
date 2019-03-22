#include "../Include/Button.h"

/*
 * ==================================================
 * ================== Class Button ==================
 * ==================================================
 */

Button::Button(float x, float y, float w, float h, std::string text, sf::Font *font, sf::Color idleColor, sf::Color hoverColor,
																	 sf::Color activeColor, sf::Color textColor, int textSize
)
	: m_font(font), m_idleColor(idleColor), m_hoverColor(hoverColor), m_activeColor(activeColor), m_textColor(textColor),
	  m_textSize(textSize), m_pressed(false)
{
	m_shape.setSize(sf::Vector2f(w, h));
	m_shape.setPosition(sf::Vector2f(x, y));
	m_shape.setFillColor(m_idleColor);

	m_text.setFont(*m_font);
	m_text.setString(text);
	m_text.setFillColor(m_textColor);
	m_text.setCharacterSize(m_textSize);
	m_text.setPosition(sf::Vector2f(m_shape.getPosition().x + (m_shape.getGlobalBounds().width / 2.f - m_text.getGlobalBounds().width / 2.f),
									m_shape.getPosition().y + (m_shape.getGlobalBounds().height / 2.f - m_text.getGlobalBounds().height / 1.5)
	));
}

Button::~Button()
{
}

void Button::update(const sf::Vector2f mousePos)
{
	m_shape.setFillColor(m_idleColor);
	if (m_shape.getGlobalBounds().contains(mousePos))
	{
		m_shape.setFillColor(m_hoverColor);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			m_shape.setFillColor(m_activeColor);
			m_pressed = true;
		}
		else if (m_pressed)
		{
			m_shape.setFillColor(m_hoverColor);
			m_pressed = false;
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
