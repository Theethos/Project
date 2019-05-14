#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/Button.h"

using namespace sf;

// Constructor
Button::Button(float x, float y, float width, float height, std::string text, Font& font, Color idle_color, Color hover_color, Color active_color,
int text_size) : 
m_Font(font), 
m_IdleColor(idle_color),
m_HoverColor(hover_color),
m_ActiveColor(active_color),
m_TextSize(text_size),
m_Pressed(false), 
m_Clicked(false), 
m_Activated(false),
m_Hovered(false),
m_Selected(false)
{
	m_Shape.setSize(Vector2f(width, height));
	m_Shape.setPosition(Vector2f(x, y));
	m_Shape.setFillColor(Color(0, 0, 255, 128));
	m_Shape.setOutlineColor(Color(0, 0, 255, 128));
	m_Shape.setOutlineThickness(15);
	
	m_Text.setFont(m_Font);
	m_Text.setString(text);
	m_Text.setFillColor(m_IdleColor);
	m_Text.setCharacterSize(m_TextSize);
	m_Text.setPosition(Vector2f(
		m_Shape.getPosition().x + (m_Shape.getGlobalBounds().width  / 2.f - m_Text.getGlobalBounds().width  / 2.f),
		m_Shape.getPosition().y + (m_Shape.getGlobalBounds().height / 2.f - m_Text.getGlobalBounds().height / 1.35)));
	
	m_Shape.setSize(Vector2f(m_Text.getGlobalBounds().width, m_Text.getGlobalBounds().height));
	m_Shape.setPosition(Vector2f(m_Text.getGlobalBounds().left, m_Text.getGlobalBounds().top));
}
// Destructor
Button::~Button()
{}
	
// Functions
void Button::Update(const Vector2f mouse_position)
{
	// If the mouse is over the button
	if (m_Shape.getGlobalBounds().contains(mouse_position) && !Joystick::isConnected(0))
	{
		m_Hovered = true;
		// If the user clicks over the button
		if (Mouse::isButtonPressed(Mouse::Left))
			m_Clicked = true;
		// When user releases the click and is still over the button (simulate mouse button up event)
		else if (m_Clicked)
		{
			m_Pressed = true;
			m_Clicked = false;
		}
	}
	// Else, if user clicked on the button but is not over it anymore
	else if (!m_Selected)
	{
		if (m_Hovered)
			m_Hovered = false;
		// Reset the click (because it means the user didn't want to clicked on this button)
		if (m_Clicked)
			m_Clicked = false;
	}
}

void Button::Render(RenderTarget& target)
{
	if (m_Activated && m_Selected)
		m_Text.setFillColor(m_HoverColor);
	
	else if (m_Activated)
		m_Text.setFillColor(m_IdleColor);
	
	else if (m_Hovered || m_Selected)
		m_Text.setFillColor(m_HoverColor);
	
	else
		m_Text.setFillColor(m_IdleColor);

	if (m_Activated)
		target.draw(m_Shape);
	
	target.draw(m_Text);
}

