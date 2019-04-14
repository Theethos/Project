#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/ButtonText.h"

ButtonText::ButtonText(float x, float y, float w, float h, std::string text,
	sf::Font *font, sf::Color idleColor, sf::Color hoverColor,
	sf::Color activeColor, int textSize, sf::Window* window)
	: Button(x, y, w, h, text, font, idleColor, hoverColor, activeColor, textSize), textEntered(""),
	window(window), thread(&ButtonText::captureText, this), threaded(false), blinking(false), maxSize(12)
{
	this->textEnteredToRender.setString(this->textEntered);
	this->textEnteredToRender.setFont(*this->font);
	this->textEnteredToRender.setFillColor(this->idleColor);
	this->textEnteredToRender.setCharacterSize(this->textSize);
	this->textEnteredToRender.setPosition(this->text.getPosition());

	this->backgroundColor = sf::Color::Black;
	this->backgroundColor.a = 128;

	this->shape.setFillColor(this->backgroundColor);
}

ButtonText::~ButtonText()
{
	// End the thread if it is running
	this->deactivate();
}

void ButtonText::update(const sf::Vector2f mousePos)
{
	Button::update(mousePos);

	if (this->activated && this->textEntered.size() < this->maxSize && !this->threaded)
	{
		this->threaded = true;
		this->thread.launch();
	}
	else if (this->activated && this->textEntered.size() == this->maxSize)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
		{
			this->removeChar();
		}
	}
}

void ButtonText::render(sf::RenderTarget* target)
{
	if (this->activated)
	{
		// reset blinking state
		this->blinking = false;
		// Set background black
		this->backgroundColor = sf::Color::Black;
		this->backgroundColor.a = 128;
		this->shape.setFillColor(this->backgroundColor);

		target->draw(this->shape);
		target->draw(this->textEnteredToRender);
	}
	else if (this->textEntered != "")
	{
		if (!this->blinking)
		{
			// Set background transparent
			this->backgroundColor = sf::Color::Transparent;
		}
		this->shape.setFillColor(this->backgroundColor);
		target->draw(this->shape);
		target->draw(this->textEnteredToRender);
	}
	else
	{
		Button::render(target);
		if (!this->blinking)
		{
			// Set background transparent
			this->backgroundColor = sf::Color::Transparent;
		}
		this->shape.setFillColor(this->backgroundColor);
		target->draw(this->shape);
	}
}

void ButtonText::addChar(char character)
{
	this->textEntered += character;
	this->textEnteredToRender.setString(this->textEntered);
}

void ButtonText::removeChar()
{
	if (this->textEntered.size())
	{
		this->textEntered.pop_back();
		this->textEnteredToRender.setString(this->textEntered);
	}
}

void ButtonText::captureText()
{
	std::string textEntered;
	sf::Event event;
	this->window->pollEvent(event);
	while (event.type != sf::Event::TextEntered && this->activated)
	{
		this->window->pollEvent(event);
		/*while*/ if (event.type == sf::Event::TextEntered)
		{
			/*{
				this->window->pollEvent(event);
			}*/
			if (event.text.unicode >= 'A' && event.text.unicode <= 'z' || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				this->addChar(event.text.unicode);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
			{
				this->removeChar();
			}
		}
	}

	this->threaded = false;
}

void ButtonText::blink()
{
	this->blinking = true;
	this->backgroundColor = sf::Color::Red;
	this->backgroundColor.a = 128;
}

const std::string & ButtonText::getTextEntered() const
{
	return this->textEntered;
}
