#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/ButtonText.h"

ButtonText::ButtonText(float x, float y, float w, float h, std::string text,
	sf::Font *font, sf::Color idleColor, sf::Color hoverColor,
	sf::Color activeColor, int textSize, sf::Window* window)
	: Button(x, y, w, h, text, font, idleColor, hoverColor, activeColor, textSize), textEntered(""),
	window(window), thread(&ButtonText::captureText, this), blinking(false), threadIsRunning(false), maxSize(12)
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

	if (this->activated && this->textEntered.size() < this->maxSize && !this->threadIsRunning)
	{
		this->threadIsRunning = true,
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
	Sleep(150);
}

void ButtonText::removeChar()
{
	if (this->textEntered.size())
	{
		this->textEntered.pop_back();
		this->textEnteredToRender.setString(this->textEntered);
		Sleep(150);
	}
}

void ButtonText::captureText()
{
	/*sf::Event event;
	this->window->pollEvent(event);
	while (event.type != sf::Event::TextEntered) // && this->activated) 
	{
		this->window->pollEvent(event);
		if (event.type == sf::Event::TextEntered)
		{
			if (event.text.unicode >= 'A' && event.text.unicode <= 'z' || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				this->addChar(event.text.unicode);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
			{
				this->removeChar();
			}
			break;
		}
	}*/
	/*	I can't use pollEvent because otherwise it may crash with the Game function "updateEvent"
		and I have to use a thread in order to keep the game moving when the user enters its text */
		// Testing MAJ letter
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			this->addChar('A');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
		{
			this->addChar('B');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		{
			this->addChar('C');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			this->addChar('D');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			this->addChar('E');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			this->addChar('F');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
		{
			this->addChar('G');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
		{
			this->addChar('H');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
		{
			this->addChar('I');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
		{
			this->addChar('J');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
		{
			this->addChar('K');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		{
			this->addChar('L');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
		{
			this->addChar('M');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
		{
			this->addChar('N');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
		{
			this->addChar('O');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			this->addChar('P');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			this->addChar('Q');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			this->addChar('R');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			this->addChar('S');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
		{
			this->addChar('T');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
		{
			this->addChar('U');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
		{
			this->addChar('V');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			this->addChar('W');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			this->addChar('X');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
		{
			this->addChar('Y');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			this->addChar('Z');
		}
	}
	// Backspace
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
	{
		this->removeChar();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		this->addChar(' ');
	}
	// NORMALE letter
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			this->addChar('a');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
		{
			this->addChar('b');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		{
			this->addChar('c');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			this->addChar('d');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			this->addChar('e');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			this->addChar('f');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
		{
			this->addChar('g');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
		{
			this->addChar('h');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
		{
			this->addChar('i');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
		{
			this->addChar('j');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
		{
			this->addChar('k');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		{
			this->addChar('l');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
		{
			this->addChar('m');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
		{
			this->addChar('n');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
		{
			this->addChar('o');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			this->addChar('p');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			this->addChar('q');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			this->addChar('r');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			this->addChar('s');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
		{
			this->addChar('t');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
		{
			this->addChar('u');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
		{
			this->addChar('v');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			this->addChar('w');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			this->addChar('x');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
		{
			this->addChar('y');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			this->addChar('z');
		}
	}

	this->threadIsRunning = false;
	this->mutex.unlock();
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
