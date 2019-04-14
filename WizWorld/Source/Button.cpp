#include "Precompiled_Header.h"
#include "../Include/Macros.h"
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
	sf::Color activeColor, int textSize)
	: font(font), idleColor(idleColor), hoverColor(hoverColor), activeColor(activeColor),
	textSize(textSize), pressed(false), click(false), activated(false),
	hovered(false)
{
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(this->idleColor);
	this->text.setCharacterSize(this->textSize);

	this->shape.setSize(sf::Vector2f(w, h));
	this->shape.setPosition(sf::Vector2f(x, y));

	this->text.setPosition(sf::Vector2f(this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f - this->text.getGlobalBounds().width / 2.f),
									this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f - this->text.getGlobalBounds().height / 1.35)
	));
	
}

/* Destructor */
Button::~Button()
{}
	
/* Functions */
void Button::update(const sf::Vector2f mousePos)
{
	/* Set button to idle_color */
	this->text.setFillColor(this->idleColor);
	/* If the mouse is over the button */
	if (this->text.getGlobalBounds().contains(mousePos))
	{
		this->hovered = true;
		/* If the user clicks over the button */
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->click = true;
		}
		/* When user released the click and he is still over the button (simulate mouse button up event) */
		else if (sf::Event::MouseButtonReleased && this->click)
		{
			/* Set to active_color */
			this->text.setFillColor(this->activeColor);
			this->pressed = true;
			this->click = false;
		}
		/* Else set it to hover_color */
		else
		{
			this->text.setFillColor(this->hoverColor);
			if (this->pressed)
				this->pressed = false;
		}
	}
	/* Else, if user clicked on the button but is not over it anymore */
	else
	{
		if (this->hovered)
		{
			this->hovered = false;
		}
		// Reset the click (because it means the user didn't want to click on this button
		if (this->click)
		{
			this->click = false;
		}
	}
	if (this->activated)
	{
		this->text.setFillColor(this->hoverColor);
	}
}

void Button::render(sf::RenderTarget * target)
{
	if (target)
	{
		//target->draw(this->shape);
		target->draw(this->text);
	}		
}

void Button::activate()
{
	if (!this->activated)
	{
		this->activated = true;
	}

}

void Button::deactivate()
{
	if (this->activated)
	{
		this->activated = false;
	}
}

bool Button::getPressed() const
{
	return this->pressed;
}

bool Button::getActivated() const
{
	return this->activated;
}

bool Button::getHovered() const
{
	return this->hovered;
}

sf::Vector2f Button::getPosition() const
{
	return this->shape.getPosition();
}

sf::Vector2f Button::getSize() const
{
	return this->shape.getSize();
}

void Button::setPressed(bool pressed)
{
	this->pressed = pressed;
}
