#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/TextField.h"

using namespace sf;

// Constructor
TextField::TextField(RenderWindow& window, Font &font, float x, float y, float width, float height, std::string text, Color idle_color, Color hover_color,
Color active_color, int text_size, bool only_letter) :
Button(x, y, width, height, text, font, idle_color, hover_color, active_color, text_size),
m_TextEntered(""),
m_Window(window), 
m_Thread(&TextField::CaptureText, this), 
m_Blinking(false), 
m_Running(false),
m_OnlyLetter(only_letter),
m_MaxSize(12)
{
	m_BackgroundColor = Color(0, 0, 0, 128);
	
	m_Shape.setSize(Vector2f(width, height));
	m_Shape.setPosition(Vector2f(x, y));
	m_Shape.setFillColor(m_BackgroundColor);
	m_Shape.setOutlineThickness(0);

	m_Text.setPosition(Vector2f(m_Shape.getPosition()) 
					 + Vector2f(m_Shape.getGlobalBounds().width * 0.02, m_Shape.getGlobalBounds().height * 0.1));
	
	m_TextRendered.setString(m_TextEntered);
	m_TextRendered.setFont(m_Font);
	m_TextRendered.setFillColor(m_IdleColor);
	m_TextRendered.setCharacterSize(m_TextSize);
	m_TextRendered.setPosition(m_Text.getPosition());
}
// Destructor
TextField::~TextField()
{
	if (m_Running)
		m_Thread.wait();
}

// Functions
void TextField::Update(const Vector2f mouse_position)
{
	Button::Update(mouse_position);

	Text letter("a", m_Font, m_TextSize);                                                       
	// Launch the m_Thread                                    Check that the text is not bigger than the shape
	if (m_Activated && m_TextEntered.size() < m_MaxSize && !(m_TextRendered.getGlobalBounds().width + 2 * letter.getGlobalBounds().width > m_Shape.getSize().x) && !m_Running)
	{
		// Lock the m_Thread
		m_Running = true;
		m_Thread.launch();
	}
	// If user presses "BackSpace"
	else if (m_Activated && (m_TextEntered.size() == m_MaxSize || (m_TextRendered.getGlobalBounds().width + 2 * letter.getGlobalBounds().width > m_Shape.getSize().x)))
	{
		if (Keyboard::isKeyPressed(Keyboard::BackSpace))
		{
			RemoveChar();
		}
	}
}

void TextField::Render(RenderTarget& target)
{
	if (m_Activated)
	{
		// Reset the m_Blinking state
		m_Blinking = false;
		// Set background black
		m_BackgroundColor = Color::Black;
		m_BackgroundColor.a = 128;
		m_Shape.setFillColor(m_BackgroundColor);

		target.draw(m_Shape);
		target.draw(m_TextRendered);
	}
	// If the user entered a text but is not over the button anymore
	else if (m_TextEntered != "")
	{
		if (!m_Blinking)
		{
			// Set background transparent
			m_BackgroundColor = Color::Transparent;
		}
		m_Shape.setFillColor(m_BackgroundColor);
		target.draw(m_Shape);
		target.draw(m_TextRendered);
	}
	// If the user did not yet enter a text and is not over the button
	else
	{
		Button::Render(target);
		if (!m_Blinking)
		{
			// Set background transparent
			m_BackgroundColor = Color::Transparent;
		}
		m_Shape.setFillColor(m_BackgroundColor);
		target.draw(m_Shape);
	}
}

void TextField::AddChar(char character)
{
	// Add the character to the text string
	m_TextEntered += character;
	m_TextRendered.setString(m_TextEntered);
	// Then put a delay between 2 character
	sleep(milliseconds(150));
}

void TextField::RemoveChar()
{
	// If there is at least one character in the text string
	if (m_TextEntered.size())
	{
		// Remove the character to the text string
		m_TextEntered.pop_back();
		m_TextRendered.setString(m_TextEntered);
		// Then put a delay between 2 character
		sleep(milliseconds(150));
	}
}

void TextField::CaptureText()
{
	m_Mutex.lock();
	// I can't use pollEvent because otherwise it may crash with the Game function "UpdateEvent"
	// and I have to use a m_Thread in order to keep the game moving when the user enters its text */
	// Testing MAJ letter and SHIFT + key
	if (Keyboard::isKeyPressed(Keyboard::LShift) || Keyboard::isKeyPressed(Keyboard::RShift))
	{
		if (Keyboard::isKeyPressed(Keyboard::Slash) && !m_OnlyLetter)
			AddChar('/');
		else if (Keyboard::isKeyPressed(Keyboard::Comma) && !m_OnlyLetter)
			AddChar('?');
		else if (Keyboard::isKeyPressed(Keyboard::Period) && !m_OnlyLetter)
			AddChar(';');
		else if (Keyboard::isKeyPressed(Keyboard::Num0) && !m_OnlyLetter)
			AddChar('0');
		else if (Keyboard::isKeyPressed(Keyboard::Num1) && !m_OnlyLetter)
			AddChar('1');
		else if (Keyboard::isKeyPressed(Keyboard::Num2) && !m_OnlyLetter)
			AddChar('2');
		else if (Keyboard::isKeyPressed(Keyboard::Num3) && !m_OnlyLetter)
			AddChar('3');
		else if (Keyboard::isKeyPressed(Keyboard::Num4) && !m_OnlyLetter)
			AddChar('4');
		else if (Keyboard::isKeyPressed(Keyboard::Num5) && !m_OnlyLetter)
			AddChar('5');
		else if (Keyboard::isKeyPressed(Keyboard::Num6) && !m_OnlyLetter)
			AddChar('6');
		else if (Keyboard::isKeyPressed(Keyboard::Num7) && !m_OnlyLetter)
			AddChar('7');
		else if (Keyboard::isKeyPressed(Keyboard::Num8) && !m_OnlyLetter)
			AddChar('8');
		else if (Keyboard::isKeyPressed(Keyboard::Num9) && !m_OnlyLetter)
			AddChar('9');
		else if (Keyboard::isKeyPressed(Keyboard::A))
		{
			AddChar('A');
		}
		else if (Keyboard::isKeyPressed(Keyboard::B))
		{
			AddChar('B');
		}
		else if (Keyboard::isKeyPressed(Keyboard::C))
		{
			AddChar('C');
		}
		else if (Keyboard::isKeyPressed(Keyboard::D))
		{
			AddChar('D');
		}
		else if (Keyboard::isKeyPressed(Keyboard::E))
		{
			AddChar('E');
		}
		else if (Keyboard::isKeyPressed(Keyboard::F))
		{
			AddChar('F');
		}
		else if (Keyboard::isKeyPressed(Keyboard::G))
		{
			AddChar('G');
		}
		else if (Keyboard::isKeyPressed(Keyboard::H))
		{
			AddChar('H');
		}
		else if (Keyboard::isKeyPressed(Keyboard::I))
		{
			AddChar('I');
		}
		else if (Keyboard::isKeyPressed(Keyboard::J))
		{
			AddChar('J');
		}
		else if (Keyboard::isKeyPressed(Keyboard::K))
		{
			AddChar('K');
		}
		else if (Keyboard::isKeyPressed(Keyboard::L))
		{
			AddChar('L');
		}
		else if (Keyboard::isKeyPressed(Keyboard::M))
		{
			AddChar('M');
		}
		else if (Keyboard::isKeyPressed(Keyboard::N))
		{
			AddChar('N');
		}
		else if (Keyboard::isKeyPressed(Keyboard::O))
		{
			AddChar('O');
		}
		else if (Keyboard::isKeyPressed(Keyboard::P))
		{
			AddChar('P');
		}
		else if (Keyboard::isKeyPressed(Keyboard::Q))
		{
			AddChar('Q');
		}
		else if (Keyboard::isKeyPressed(Keyboard::R))
		{
			AddChar('R');
		}
		else if (Keyboard::isKeyPressed(Keyboard::S))
		{
			AddChar('S');
		}
		else if (Keyboard::isKeyPressed(Keyboard::T))
		{
			AddChar('T');
		}
		else if (Keyboard::isKeyPressed(Keyboard::U))
		{
			AddChar('U');
		}
		else if (Keyboard::isKeyPressed(Keyboard::V))
		{
			AddChar('V');
		}
		else if (Keyboard::isKeyPressed(Keyboard::W))
		{
			AddChar('W');
		}
		else if (Keyboard::isKeyPressed(Keyboard::X))
		{
			AddChar('X');
		}
		else if (Keyboard::isKeyPressed(Keyboard::Y))
		{
			AddChar('Y');
		}
		else if (Keyboard::isKeyPressed(Keyboard::Z))
		{
			AddChar('Z');
		}
	}
	// Backspace
	else if (Keyboard::isKeyPressed(Keyboard::BackSpace))
		RemoveChar();
	else if (Keyboard::isKeyPressed(Keyboard::Space) && !m_OnlyLetter)
		AddChar(' ');
	else if (Keyboard::isKeyPressed(Keyboard::Divide) && !m_OnlyLetter)
		AddChar('/');
	else if (Keyboard::isKeyPressed(Keyboard::Slash) && !m_OnlyLetter)
		AddChar(':');
	else if (Keyboard::isKeyPressed(Keyboard::Comma) && !m_OnlyLetter)
		AddChar(',');
	else if (Keyboard::isKeyPressed(Keyboard::Period) && !m_OnlyLetter)
		AddChar('.');
	else if (Keyboard::isKeyPressed(Keyboard::Num3) && !m_OnlyLetter)
		AddChar('"');
	else if (Keyboard::isKeyPressed(Keyboard::Num4) && !m_OnlyLetter)
		AddChar('\'');
	else if (Keyboard::isKeyPressed(Keyboard::Num5) && !m_OnlyLetter)
		AddChar('(');
	else if (Keyboard::isKeyPressed(Keyboard::Num6))
		AddChar('-');
	else if (Keyboard::isKeyPressed(Keyboard::LBracket) && !m_OnlyLetter)
		AddChar(')');
	else if (Keyboard::isKeyPressed(Keyboard::Numpad0) && !m_OnlyLetter)
		AddChar('0');
	else if (Keyboard::isKeyPressed(Keyboard::Numpad1) && !m_OnlyLetter)
		AddChar('1');
	else if (Keyboard::isKeyPressed(Keyboard::Numpad2) && !m_OnlyLetter)
		AddChar('2');
	else if (Keyboard::isKeyPressed(Keyboard::Numpad3) && !m_OnlyLetter)
		AddChar('3');
	else if (Keyboard::isKeyPressed(Keyboard::Numpad4) && !m_OnlyLetter)
		AddChar('4');
	else if (Keyboard::isKeyPressed(Keyboard::Numpad5) && !m_OnlyLetter)
		AddChar('5');
	else if (Keyboard::isKeyPressed(Keyboard::Numpad6) && !m_OnlyLetter)
		AddChar('6');
	else if (Keyboard::isKeyPressed(Keyboard::Numpad7) && !m_OnlyLetter)
		AddChar('7');
	else if (Keyboard::isKeyPressed(Keyboard::Numpad8) && !m_OnlyLetter)
		AddChar('8');
	else if (Keyboard::isKeyPressed(Keyboard::Numpad9) && !m_OnlyLetter)
		AddChar('9');
	// NORMALE letter
	else
	{
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			AddChar('a');
		}
		else if (Keyboard::isKeyPressed(Keyboard::B))
		{
			AddChar('b');
		}
		else if (Keyboard::isKeyPressed(Keyboard::C))
		{
			AddChar('c');
		}
		else if (Keyboard::isKeyPressed(Keyboard::D))
		{
			AddChar('d');
		}
		else if (Keyboard::isKeyPressed(Keyboard::E))
		{
			AddChar('e');
		}
		else if (Keyboard::isKeyPressed(Keyboard::F))
		{
			AddChar('f');
		}
		else if (Keyboard::isKeyPressed(Keyboard::G))
		{
			AddChar('g');
		}
		else if (Keyboard::isKeyPressed(Keyboard::H))
		{
			AddChar('h');
		}
		else if (Keyboard::isKeyPressed(Keyboard::I))
		{
			AddChar('i');
		}
		else if (Keyboard::isKeyPressed(Keyboard::J))
		{
			AddChar('j');
		}
		else if (Keyboard::isKeyPressed(Keyboard::K))
		{
			AddChar('k');
		}
		else if (Keyboard::isKeyPressed(Keyboard::L))
		{
			AddChar('l');
		}
		else if (Keyboard::isKeyPressed(Keyboard::M))
		{
			AddChar('m');
		}
		else if (Keyboard::isKeyPressed(Keyboard::N))
		{
			AddChar('n');
		}
		else if (Keyboard::isKeyPressed(Keyboard::O))
		{
			AddChar('o');
		}
		else if (Keyboard::isKeyPressed(Keyboard::P))
		{
			AddChar('p');
		}
		else if (Keyboard::isKeyPressed(Keyboard::Q))
		{
			AddChar('q');
		}
		else if (Keyboard::isKeyPressed(Keyboard::R))
		{
			AddChar('r');
		}
		else if (Keyboard::isKeyPressed(Keyboard::S))
		{
			AddChar('s');
		}
		else if (Keyboard::isKeyPressed(Keyboard::T))
		{
			AddChar('t');
		}
		else if (Keyboard::isKeyPressed(Keyboard::U))
		{
			AddChar('u');
		}
		else if (Keyboard::isKeyPressed(Keyboard::V))
		{
			AddChar('v');
		}
		else if (Keyboard::isKeyPressed(Keyboard::W))
		{
			AddChar('w');
		}
		else if (Keyboard::isKeyPressed(Keyboard::X))
		{
			AddChar('x');
		}
		else if (Keyboard::isKeyPressed(Keyboard::Y))
		{
			AddChar('y');
		}
		else if (Keyboard::isKeyPressed(Keyboard::Z))
		{
			AddChar('z');
		}
	}

	m_Running = false;
	m_Mutex.unlock();
}

void TextField::Blink()
{
	// Set the background to RED. This function is used for example
	// when the user try to launch the game without entering a pseudo.
	m_Blinking = true;
	m_BackgroundColor = Color::Red;
	m_BackgroundColor.a = 128;
}

// Setter
void TextField::SetPosition(float x, float y)
{ 
	m_Shape.setPosition(x, y);
	m_Text.setPosition(Vector2f(GetPosition()) +
										  Vector2f(m_Shape.getGlobalBounds().width * 0.02,
										  m_Shape.getGlobalBounds().height / 2.f - m_Text.getGlobalBounds().height / 1.35));
	m_TextRendered.setPosition(m_Text.getPosition());
}
