#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/GUI.h"

using namespace sf;

// Static variables;
bool GUI::s_Token = false;
std::list<GUI*> GUI::s_Instances;

// Constructor
GUI::GUI(RenderWindow& window, Player& player) :
m_Window(window),
m_Player(player),
m_Visible(true),
m_Move(false),
m_Offset(0, 0)
{
	if (!m_Font.loadFromFile("../External/Fonts/GOTHICB.TTF"))
		std::cerr << "Error while loading font in PlayerGUI. Line " << __LINE__ << std::endl;

	m_GlobalColor = Color(0, 0, 0, 128);
	m_GlobalTextColor = Color(Color::White);
	m_GlobalShape.setOutlineThickness(1);
	m_GlobalShape.setOutlineColor(Color::Black);

	// Add the new GUI element to the vector that store every instance
	// It is used to check for collision between instance
	GUI::s_Instances.push_back(this);
}
// Destructor
GUI::~GUI()
{
	s_Instances.remove(this);
}

// Function
void GUI::Move()
{
	// Move the GUI in Drag&Drop
	Vector2f mouse_position(Mouse::getPosition());
	if (Mouse::isButtonPressed(Mouse::Button::Left) && m_Move)
	{
		
		m_Window.setMouseCursorVisible(false);
		mouse_position -= m_Offset;
		Vector2f window_size(m_Window.getSize());
		
		if (mouse_position.x < 0)
			mouse_position.x = 0;
		else if (mouse_position.x > window_size.x - m_GlobalShape.getSize().x)
			mouse_position.x = window_size.x - m_GlobalShape.getSize().x;
		if (mouse_position.y < 0)
			mouse_position.y = 0;
		else if (mouse_position.y > window_size.y - m_GlobalShape.getSize().y)
			mouse_position.y = window_size.y - m_GlobalShape.getSize().y;
		
		// Update positions with the virtual function
		UpdatePosition(mouse_position);
	}
	else if (Mouse::isButtonPressed(Mouse::Button::Left) && m_GlobalShape.getGlobalBounds().contains(mouse_position))
	{
		GUI::s_Token = true;
		m_Move = true;
		m_Window.setMouseCursorVisible(false);
		m_Offset = Vector2f(mouse_position - m_GlobalShape.getPosition());
	}
	else
	{
		// Checking for collision between instances
		if (m_Move)
		{
			for (auto &it : GUI::s_Instances)
			{
				if (it != this)
				{
					if (it->m_GlobalShape.getGlobalBounds().intersects(m_GlobalShape.getGlobalBounds()))
					{
						UpdatePosition(GetNewPosition(it->m_GlobalShape.getGlobalBounds()));
					}
				}
			}
		}
		m_Move = false;
		m_Window.setMouseCursorVisible(true);
		GUI::s_Token = false;
	}
}

// Private Function
const Vector2f GUI::GetNewPosition(const FloatRect & intersect) const
{
	// Calculate the minimum offSet of the intersection
	float offSet_top = std::abs(m_GlobalShape.getPosition().y + m_GlobalShape.getSize().y - intersect.top);
	float offSet_left = std::abs(m_GlobalShape.getPosition().x + m_GlobalShape.getSize().x - intersect.left);
	float offSet_bottom = std::abs((m_GlobalShape.getPosition().y) - (intersect.top + intersect.height));
	float offSet_right = std::abs((m_GlobalShape.getPosition().x) - (intersect.left + intersect.width));

	float min = std::min(offSet_bottom, std::min(offSet_left, std::min(offSet_right, offSet_top)));

	Vector2f newPosition(m_GlobalShape.getPosition());

	// And then calculate the new position of the GUI
	if (min == offSet_bottom)
	{
		if (intersect.top + intersect.height > m_Window.getPosition().y + m_Window.getSize().y - m_GlobalShape.getSize().y)
			newPosition.y = intersect.top - m_GlobalShape.getSize().y;
		else
			newPosition.y = intersect.top + intersect.height;
	}
	else if (min == offSet_top)
	{
		if (intersect.top - m_GlobalShape.getSize().y < 0)
			newPosition.y = intersect.top + intersect.height;
		else
			newPosition.y = intersect.top - m_GlobalShape.getSize().y;
	}
	else if (min == offSet_right)
	{
		if (intersect.left + intersect.width > m_Window.getPosition().x + m_Window.getSize().x - m_GlobalShape.getSize().x)
			newPosition.x = intersect.left - m_GlobalShape.getSize().x;
		else
			newPosition.x = intersect.left + intersect.width;
	}
	else if (min == offSet_left)
	{
		if (intersect.left - m_GlobalShape.getSize().x < 0)
			newPosition.x = intersect.left + intersect.width;
		else
			newPosition.x = intersect.left - m_GlobalShape.getSize().x;
	}

	return newPosition;
}
