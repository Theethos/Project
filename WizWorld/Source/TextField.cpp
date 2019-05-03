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
}

// Functions
void TextField::Update(const Vector2f mouse_position)
{
	Button::Update(mouse_position);
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
	if (m_TextEntered.size() < m_MaxSize)
	{
		m_TextEntered += character;
		m_TextRendered.setString(m_TextEntered);
	}
}

void TextField::RemoveChar()
{
	// If there is at least one character in the text string
	if (m_TextEntered.size())
	{
		// Remove the character to the text string
		m_TextEntered.pop_back();
		m_TextRendered.setString(m_TextEntered);
	}
}

void TextField::HandleInput(int input)
{
	if (Keyboard::isKeyPressed(Keyboard::LShift) || Keyboard::isKeyPressed(Keyboard::RShift))
	{
		if (input == Keyboard::Slash && !m_OnlyLetter)
			AddChar('/');
		else if (input == Keyboard::Comma && !m_OnlyLetter)
			AddChar('?');
		else if (input == Keyboard::Period && !m_OnlyLetter)
			AddChar(';');
		else if (input == Keyboard::Num0 && !m_OnlyLetter)
			AddChar('0');
		else if (input == Keyboard::Num1 && !m_OnlyLetter)
			AddChar('1');
		else if (input == Keyboard::Num2 && !m_OnlyLetter)
			AddChar('2');
		else if (input == Keyboard::Num3 && !m_OnlyLetter)
			AddChar('3');
		else if (input == Keyboard::Num4 && !m_OnlyLetter)
			AddChar('4');
		else if (input == Keyboard::Num5 && !m_OnlyLetter)
			AddChar('5');
		else if (input == Keyboard::Num6 && !m_OnlyLetter)
			AddChar('6');
		else if (input == Keyboard::Num7 && !m_OnlyLetter)
			AddChar('7');
		else if (input == Keyboard::Num8 && !m_OnlyLetter)
			AddChar('8');
		else if (input == Keyboard::Num9 && !m_OnlyLetter)
			AddChar('9');
		else if (input == Keyboard::A)
			AddChar('A');
		else if (input == Keyboard::B)
			AddChar('B');
		else if (input == Keyboard::C)
			AddChar('C');
		else if (input == Keyboard::D)
			AddChar('D');
		else if (input == Keyboard::E)
			AddChar('E');
		else if (input == Keyboard::F)
			AddChar('F');
		else if (input == Keyboard::G)
			AddChar('G');
		else if (input == Keyboard::H)
			AddChar('H');
		else if (input == Keyboard::I)
			AddChar('I');
		else if (input == Keyboard::J)
			AddChar('J');
		else if (input == Keyboard::K)
			AddChar('K');
		else if (input == Keyboard::L)
			AddChar('L');
		else if (input == Keyboard::M)
			AddChar('M');
		else if (input == Keyboard::N)
			AddChar('N');
		else if (input == Keyboard::O)
			AddChar('O');
		else if (input == Keyboard::P)
			AddChar('P');
		else if (input == Keyboard::Q)
			AddChar('Q');
		else if (input == Keyboard::R)
			AddChar('R');
		else if (input == Keyboard::S)
			AddChar('S');
		else if (input == Keyboard::T)
			AddChar('T');
		else if (input == Keyboard::U)
			AddChar('U');
		else if (input == Keyboard::V)
			AddChar('V');
		else if (input == Keyboard::W)
			AddChar('W');
		else if (input == Keyboard::X)
			AddChar('X');
		else if (input == Keyboard::Y)
			AddChar('Y');
		else if (input == Keyboard::Z)
			AddChar('Z');
	}
	else if (input == Keyboard::BackSpace)
		RemoveChar();
	else if (input == Keyboard::Space && !m_OnlyLetter)
		AddChar(' ');
	else if (input == Keyboard::Divide && !m_OnlyLetter)
		AddChar('/');
	else if (input == Keyboard::Slash && !m_OnlyLetter)
		AddChar(':');
	else if (input == Keyboard::Comma && !m_OnlyLetter)
		AddChar(',');
	else if (input == Keyboard::Period && !m_OnlyLetter)
		AddChar('.');
	else if (input == Keyboard::Num0 && !m_OnlyLetter)
		AddChar('à');
	else if (input == Keyboard::Num1 && !m_OnlyLetter)
		AddChar('&');
	else if (input == Keyboard::Num3 && !m_OnlyLetter)
		AddChar('é');
	else if (input == Keyboard::Num3 && !m_OnlyLetter)
		AddChar('"');
	else if (input == Keyboard::Num4 && !m_OnlyLetter)
		AddChar('\'');
	else if (input == Keyboard::Num5 && !m_OnlyLetter)
		AddChar('(');
	else if (input == Keyboard::Num6)
		AddChar('-');
	else if (input == Keyboard::Num7 && !m_OnlyLetter)
		AddChar('è');
	else if (input == Keyboard::Num8 && !m_OnlyLetter)
		AddChar('_');
	else if (input == Keyboard::Num9 && !m_OnlyLetter)
		AddChar('ç');
	else if (input == Keyboard::LBracket && !m_OnlyLetter)
		AddChar(')');
	else if (input == Keyboard::Numpad0 && !m_OnlyLetter)
		AddChar('0');
	else if (input == Keyboard::Numpad1 && !m_OnlyLetter)
		AddChar('1');
	else if (input == Keyboard::Numpad2 && !m_OnlyLetter)
		AddChar('2');
	else if (input == Keyboard::Numpad3 && !m_OnlyLetter)
		AddChar('3');
	else if (input == Keyboard::Numpad4 && !m_OnlyLetter)
		AddChar('4');
	else if (input == Keyboard::Numpad5 && !m_OnlyLetter)
		AddChar('5');
	else if (input == Keyboard::Numpad6 && !m_OnlyLetter)
		AddChar('6');
	else if (input == Keyboard::Numpad7 && !m_OnlyLetter)
		AddChar('7');
	else if (input == Keyboard::Numpad8 && !m_OnlyLetter)
		AddChar('8');
	else if (input == Keyboard::Numpad9 && !m_OnlyLetter)
		AddChar('9');
	else if (input == Keyboard::A)
		AddChar('a');
	else if (input == Keyboard::B)
		AddChar('b');
	else if (input == Keyboard::C)
		AddChar('c');
	else if (input == Keyboard::D)
		AddChar('d');
	else if (input == Keyboard::E)
		AddChar('e');
	else if (input == Keyboard::F)
		AddChar('f');
	else if (input == Keyboard::G)
		AddChar('g');
	else if (input == Keyboard::H)
		AddChar('h');
	else if (input == Keyboard::I)
		AddChar('i');
	else if (input == Keyboard::J)
		AddChar('j');
	else if (input == Keyboard::K)
		AddChar('k');
	else if (input == Keyboard::L)
		AddChar('l');
	else if (input == Keyboard::M)
		AddChar('m');
	else if (input == Keyboard::N)
		AddChar('n');
	else if (input == Keyboard::O)
		AddChar('o');
	else if (input == Keyboard::P)
		AddChar('p');
	else if (input == Keyboard::Q)
		AddChar('q');
	else if (input == Keyboard::R)
		AddChar('r');
	else if (input == Keyboard::S)
		AddChar('s');
	else if (input == Keyboard::T)
		AddChar('t');
	else if (input == Keyboard::U)
		AddChar('u');
	else if (input == Keyboard::V)
		AddChar('v');
	else if (input == Keyboard::W)
		AddChar('w');
	else if (input == Keyboard::X)
		AddChar('x');
	else if (input == Keyboard::Y)
		AddChar('y');
	else if (input == Keyboard::Z)
		AddChar('z');
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
