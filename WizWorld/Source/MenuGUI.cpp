#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/MenuGUI.h"

using namespace sf;

// Constructor
MenuGUI::MenuGUI(RenderWindow &window, Player &player) :
GUI(window, player),
m_GlobalShape(0)
{
	CircleShape corner(m_Window.getSize().y * 0.03);
	
	int index = 0;
	for (unsigned i = 0; i < corner.getPointCount(); ++i)
	{
		Vector2f point = corner.getPoint(i);
		if (point.x >= 0 && point.x <= corner.getRadius() && point.y >= corner.getRadius() && point.y <= 2 * corner.getRadius())
		{
			m_GlobalShape.setPointCount(m_GlobalShape.getPointCount() + 1);
			m_GlobalShape.setPoint(index++, point);
		}
	}
	for (unsigned i = 0; i < corner.getPointCount(); ++i)
	{
		Vector2f point = corner.getPoint(i);
		if (point.x >= corner.getRadius() && point.x <= 2 * corner.getRadius() && point.y >= corner.getRadius() && point.y <= 2 * corner.getRadius())
		{
			point.x += m_Window.getSize().x * 0.5;
			m_GlobalShape.setPointCount(m_GlobalShape.getPointCount() + 1);
			m_GlobalShape.setPoint(index++, point);
		}
	}
	m_GlobalShape.setPosition(Vector2f(m_Window.getPosition().x + m_Window.getSize().x * 0.25, m_Window.getPosition().y)
							- Vector2f(corner.getRadius(), corner.getRadius() * 1.06)); // 1.06 in hard otherwise it doesn't reach the top of the window
	m_GlobalShape.setFillColor(m_GlobalColor);
	m_GlobalShape.setOutlineThickness(1);
	m_GlobalShape.setOutlineColor(Color::Black);

	m_Shape = &m_GlobalShape;
}
// Destructor
MenuGUI::~MenuGUI()
{
}

void MenuGUI::Update(const float& dt)
{
	if (m_Visible)
	{
		if (!Joystick::isConnected(0) && (!GUI::s_Token || m_Move))
			Move<ConvexShape>();
	}
}

void MenuGUI::Render(RenderTarget& target)
{
	target.draw(m_GlobalShape);
}

void MenuGUI::UpdatePosition(const Vector2f& mouse_position)
{
	//m_Shape->setPosition(mouse_position);
	m_GlobalShape.setPosition(mouse_position - Vector2f(0, m_Window.getSize().y * 0.03 * 1.06));
}
