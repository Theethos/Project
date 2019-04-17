#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/ButtonText.h"

// Constructor
ButtonText::ButtonText(float x, float y, float w, float h, std::string text, sf::Font *font, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, int textSize, sf::Window* window) :
Button(x, y, w, h, text, font, idleColor, hoverColor, activeColor, textSize),
textEntered(""),
window(window), 
thread(&ButtonText::CaptureText, this), 
blinking(false), 
threadIsRunning(false),
maxSize(12)
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
// Destructor
ButtonText::~ButtonText()
{
	if (this->threadIsRunning)
	{
		this->thread.wait();
	}
}

// Functions
void ButtonText::Update(const sf::Vector2f mousePos)
{
	Button::Update(mousePos);

	// Launch the thread
	if (this->activated && this->textEntered.size() < this->maxSize && !this->threadIsRunning)
	{
		// Lock the thread
		this->threadIsRunning = true,
		this->thread.launch();
	}
	// If user presses "BackSpace"
	else if (this->activated && this->textEntered.size() == this->maxSize)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
		{
			this->RemoveChar();
		}
	}
}

void ButtonText::Render(sf::RenderTarget* target)
{
	if (this->activated)
	{
		// Reset the blinking state
		this->blinking = false;
		// Set background black
		this->backgroundColor = sf::Color::Black;
		this->backgroundColor.a = 128;
		this->shape.setFillColor(this->backgroundColor);

		target->draw(this->shape);
		target->draw(this->textEnteredToRender);
	}
	// If the user entered a text but is not over the button anymore
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
	// If the user did not yet enter a text and is not over the button
	else
	{
		Button::Render(target);
		if (!this->blinking)
		{
			// Set background transparent
			this->backgroundColor = sf::Color::Transparent;
		}
		this->shape.setFillColor(this->backgroundColor);
		target->draw(this->shape);
	}
}

void ButtonText::AddChar(char character)
{
	// Add the character to the text string
	this->textEntered += character;
	this->textEnteredToRender.setString(this->textEntered);
	// Then put a delay between 2 character
	sf::sleep(sf::milliseconds(150));
}

void ButtonText::RemoveChar()
{
	// If there is at least one character in the text string
	if (this->textEntered.size())
	{
		// Remove the character to the text string
		this->textEntered.pop_back();
		this->textEnteredToRender.setString(this->textEntered);
		// Then put a delay between 2 character
		sf::sleep(sf::milliseconds(150));
	}
}

void ButtonText::CaptureText()
{
	this->mutex.lock();
	// I can't use pollEvent because otherwise it may crash with the Game function "UpdateEvent"
	// and I have to use a thread in order to keep the game moving when the user enters its text */
	// Testing MAJ letter
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			this->AddChar('A');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
		{
			this->AddChar('B');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		{
			this->AddChar('C');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			this->AddChar('D');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			this->AddChar('E');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			this->AddChar('F');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
		{
			this->AddChar('G');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
		{
			this->AddChar('H');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
		{
			this->AddChar('I');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
		{
			this->AddChar('J');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
		{
			this->AddChar('K');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		{
			this->AddChar('L');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
		{
			this->AddChar('M');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
		{
			this->AddChar('N');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
		{
			this->AddChar('O');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			this->AddChar('P');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			this->AddChar('Q');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			this->AddChar('R');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			this->AddChar('S');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
		{
			this->AddChar('T');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
		{
			this->AddChar('U');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
		{
			this->AddChar('V');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			this->AddChar('W');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			this->AddChar('X');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
		{
			this->AddChar('Y');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			this->AddChar('Z');
		}
	}
	// Backspace
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
	{
		this->RemoveChar();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		this->AddChar(' ');
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
	{
		this->AddChar('-');
	}
	// NORMALE letter
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			this->AddChar('a');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
		{
			this->AddChar('b');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		{
			this->AddChar('c');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			this->AddChar('d');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			this->AddChar('e');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			this->AddChar('f');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
		{
			this->AddChar('g');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
		{
			this->AddChar('h');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
		{
			this->AddChar('i');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
		{
			this->AddChar('j');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
		{
			this->AddChar('k');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		{
			this->AddChar('l');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
		{
			this->AddChar('m');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
		{
			this->AddChar('n');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
		{
			this->AddChar('o');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			this->AddChar('p');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			this->AddChar('q');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			this->AddChar('r');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			this->AddChar('s');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
		{
			this->AddChar('t');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
		{
			this->AddChar('u');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
		{
			this->AddChar('v');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			this->AddChar('w');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			this->AddChar('x');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
		{
			this->AddChar('y');
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			this->AddChar('z');
		}
	}

	this->threadIsRunning = false;
	this->mutex.unlock();
}

void ButtonText::Blink()
{
	// Set the background to RED. This function is used for example
	// when the user try to launch the game without entering a pseudo.
	this->blinking = true;
	this->backgroundColor = sf::Color::Red;
	this->backgroundColor.a = 128;
}

// Getter
const std::string & ButtonText::getTextEntered() const
{
	return this->textEntered;
}
