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

	// Add the new GUI element to the vector that store every instance
	// It is used to check for collision between instance
	GUI::s_Instances.push_back(this);
}
// Destructor
GUI::~GUI()
{
	s_Instances.remove(this);
}

// Private Function
const Vector2f GUI::GetNewPosition(const FloatRect & intersect) const
{
	// Calculate the minimum offSet of the intersection
	float offSet_top = std::abs(m_Shape->getPosition().y + m_Shape->getGlobalBounds().height - intersect.top);
	float offSet_left = std::abs(m_Shape->getPosition().x + m_Shape->getGlobalBounds().width - intersect.left);
	float offSet_bottom = std::abs((m_Shape->getPosition().y) - (intersect.top + intersect.height));
	float offSet_right = std::abs((m_Shape->getPosition().x) - (intersect.left + intersect.width));

	float min = std::min(offSet_bottom, std::min(offSet_left, std::min(offSet_right, offSet_top)));

	Vector2f newPosition(m_Shape->getPosition());

	// And then calculate the new position of the GUI
	if (min == offSet_bottom)
	{
		if (intersect.top + intersect.height > m_Window.getPosition().y + m_Window.getSize().y - m_Shape->getGlobalBounds().height)
			newPosition.y = intersect.top - m_Shape->getGlobalBounds().height;
		else
			newPosition.y = intersect.top + intersect.height;
	}
	else if (min == offSet_top)
	{
		if (intersect.top - m_Shape->getGlobalBounds().height < 0)
			newPosition.y = intersect.top + intersect.height;
		else
			newPosition.y = intersect.top - m_Shape->getGlobalBounds().height;
	}
	else if (min == offSet_right)
	{
		if (intersect.left + intersect.width > m_Window.getPosition().x + m_Window.getSize().x - m_Shape->getGlobalBounds().width)
			newPosition.x = intersect.left - m_Shape->getGlobalBounds().width;
		else
			newPosition.x = intersect.left + intersect.width;
	}
	else if (min == offSet_left)
	{
		if (intersect.left - m_Shape->getGlobalBounds().width < 0)
			newPosition.x = intersect.left + intersect.width;
		else
			newPosition.x = intersect.left - m_Shape->getGlobalBounds().width;
	}

	return newPosition;
}
