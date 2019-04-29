#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/TextField.h"

// Constructor
TextField::TextField(float x, float y, float w, float h, std::string text, sf::Font *font, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, int textSize, sf::RenderWindow* window, bool only_letter) :
Button(x, y, w, h, text, font, idleColor, hoverColor, activeColor, textSize),
textEntered(""),
window(window), 
thread(&TextField::CaptureText, this), 
blinking(false), 
threadIsRunning(false),
_onlyLetter(only_letter),
maxSize(12)
{
	this->shape.setSize(sf::Vector2f(w, h));
	this->shape.setPosition(sf::Vector2f(x, y));

	this->text.setPosition(sf::Vector2f(this->getPosition()) + sf::Vector2f(this->shape.getGlobalBounds().width * 0.02, this->shape.getGlobalBounds().height / 2.f - this->text.getGlobalBounds().height / 1.35));
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
TextField::~TextField()
{
	if (this->threadIsRunning)
	{
		this->thread.wait();
	}
}

// Functions
void TextField::Update(const sf::Vector2f mousePos)
{
	Button::Update(mousePos);

	sf::Text letter("a", *this->font, this->textSize);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		this->Deactivate();
	}                                                                        // Check that the text is not bigger than the shape
	// Launch the thread
	else if (this->activated && this->textEntered.size() < this->maxSize && !(textEnteredToRender.getGlobalBounds().width + 2 * letter.getGlobalBounds().width > shape.getSize().x) && !this->threadIsRunning)
	{
		// Lock the thread
		this->threadIsRunning = true;
		this->thread.launch();
	}
	// If user presses "BackSpace"
	else if (this->activated && (this->textEntered.size() == this->maxSize || (textEnteredToRender.getGlobalBounds().width + 2 * letter.getGlobalBounds().width > shape.getSize().x)))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
		{
			this->RemoveChar();
		}
	}
}

void TextField::Render(sf::RenderTarget* target)
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

void TextField::AddChar(char character)
{
	// Add the character to the text string
	this->textEntered += character;
	this->textEnteredToRender.setString(this->textEntered);
	// Then put a delay between 2 character
	sf::sleep(sf::milliseconds(150));
}

void TextField::RemoveChar()
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

void TextField::CaptureText()
{
	this->mutex.lock();
	// I can't use pollEvent because otherwise it may crash with the Game function "UpdateEvent"
	// and I have to use a thread in order to keep the game moving when the user enters its text */
	// Testing MAJ letter and SHIFT + key
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Slash) && !_onlyLetter)
			this->AddChar('/');
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Comma) && !_onlyLetter)
			this->AddChar('?');
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Period) && !_onlyLetter)
			this->AddChar(';');
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
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
		this->RemoveChar();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !_onlyLetter)
		this->AddChar(' ');
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Divide) && !_onlyLetter)
		this->AddChar('/');
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Slash) && !_onlyLetter)
		this->AddChar(':');
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Comma) && !_onlyLetter)
		this->AddChar(',');
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Period) && !_onlyLetter)
		this->AddChar('.');
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && !_onlyLetter)
		this->AddChar('"');
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) && !_onlyLetter)
		this->AddChar('\'');
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) && !_onlyLetter)
		this->AddChar('(');
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
		this->AddChar('-');
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LBracket) && !_onlyLetter)
		this->AddChar(')');
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

void TextField::Blink()
{
	// Set the background to RED. This function is used for example
	// when the user try to launch the game without entering a pseudo.
	this->blinking = true;
	this->backgroundColor = sf::Color::Red;
	this->backgroundColor.a = 128;
}

// Getter
const std::string & TextField::getTextEntered() const
{
	return this->textEntered;
}

void TextField::setPosition(float x, float y)
{ 
	this->shape.setPosition(x, y);
	this->text.setPosition(sf::Vector2f(this->getPosition()) +
										  sf::Vector2f(this->shape.getGlobalBounds().width * 0.02,
										  this->shape.getGlobalBounds().height / 2.f - this->text.getGlobalBounds().height / 1.35));
	this->textEnteredToRender.setPosition(this->text.getPosition());
}
