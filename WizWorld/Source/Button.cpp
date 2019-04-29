#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/Button.h"

// Constructor
Button::Button(float x, float y, float w, float h, std::string text, sf::Font *font, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, int textSize) : 
font(font), 
idleColor(idleColor),
hoverColor(hoverColor),
activeColor(activeColor),
textSize(textSize),
pressed(false), 
clicked(false), 
activated(false),
hovered(false),
selected(false)
{
	this->shape.setSize(sf::Vector2f(w, h));
	this->shape.setPosition(sf::Vector2f(x, y));
	
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(this->idleColor);
	this->text.setCharacterSize(this->textSize);
	this->text.setPosition(sf::Vector2f(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width  / 2.f - this->text.getGlobalBounds().width  / 2.f),
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f - this->text.getGlobalBounds().height / 1.35)));
	this->shape.setSize(sf::Vector2f(this->text.getGlobalBounds().width, this->text.getGlobalBounds().height));
	this->shape.setPosition(sf::Vector2f(this->text.getGlobalBounds().left, this->text.getGlobalBounds().top));
}
// Destructor
Button::~Button()
{}
	
// Functions
void Button::Update(const sf::Vector2f mousePos)
{
	// If the mouse is over the button
	if (this->shape.getGlobalBounds().contains(mousePos) && !sf::Joystick::isConnected(0))
	{
		this->hovered = true;
		// If the user clicks over the button
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->clicked = true;
		}
		// When user releases the click and is still over the button (simulate mouse button up event)
		else if (this->clicked)
		{
			// Set to active_color
			this->pressed = true;
			this->clicked = false;
		}
	}
	// Else, if user clicked on the button but is not over it anymore
	else if (!this->selected)
	{
		if (this->hovered)
		{
			this->hovered = false;
		}
		// Reset the click (because it means the user didn't want to clicked on this button
		if (this->clicked)
		{
			this->clicked = false;
		}
	}
}

void Button::Render(sf::RenderTarget * target)
{
	if (this->activated && this->selected)
		this->text.setFillColor(sf::Color::Black);
	else if (this->activated)
		this->text.setFillColor(sf::Color::Red);
	else if (this->hovered || this->selected)
		this->text.setFillColor(this->hoverColor);
	else
		this->text.setFillColor(this->idleColor);
	if (target)
	{
		target->draw(this->text);
	}		
}

void Button::Activate()
{
	if (!this->activated)
	{
		this->activated = true;
	}
}

void Button::Deactivate()
{
	if (this->activated)
	{
		this->activated = false;
	}
}

// Getters
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

bool Button::getSelected() const
{
	return this->selected;
}

sf::Vector2f Button::getPosition() const
{
	return this->shape.getPosition();
}

sf::Vector2f Button::getSize() const
{
	return this->shape.getSize();
}

// Setters
void Button::setPressed(bool pressed)
{
	this->pressed = pressed;
}

void Button::setHovered(bool hovered)
{
	this->hovered = hovered;
}

void Button::setSelected(bool selected)
{
	this->selected = selected;
}
