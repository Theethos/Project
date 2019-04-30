#ifndef GUI_H
#define GUI_H

#include "Player.h"

class GUI
{
public:
	GUI(sf::RenderWindow& window, Player& player);
	virtual ~GUI();

	// Functions
	virtual void Update(const float & dt) = 0;
	virtual void Render(sf::RenderTarget& target) = 0;
	// Function which behavior has to defined in UpdatePosition()
	inline void Toggle() { (m_Visible ? m_Visible = false : m_Visible = true); }

	// token to control the number of moving GUI (Drag&Drop) : only one at a time
	static bool s_Token;

private:
	// List of all instances -> required to check collisions between modules.
	static std::list<GUI*> s_Instances;
protected:
	bool m_Visible;
	bool m_Move;
	sf::Vector2f m_Offset;

	sf::RenderWindow& m_Window;
	sf::Font m_Font;

	// Entity related to
	Player &m_Player;

	// Global
	sf::Shape* m_Shape;
	sf::Color m_GlobalColor;
	sf::Color m_GlobalTextColor;

	// Private functions
	// Defines the behavior to use when function Move() is called (When user use Drag&Drop on the GUI module)
	virtual void UpdatePosition(const sf::Vector2f &mouse_position) = 0;
	// Get the most likely position of the GUI module if it collides with an other
	virtual const sf::Vector2f GetNewPosition(const sf::FloatRect & intersect) const;
	template <typename TypeOfShape = sf::RectangleShape> // As the GlobalShape can be a Circle, a Rectangle or a ConvexShape.
	void Move()
	{
		// Move the GUI in Drag&Drop
		sf::Vector2f mouse_position(m_Window.mapPixelToCoords(Mouse::getPosition(m_Window)));
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && m_Move)
		{

			m_Window.setMouseCursorVisible(false);
			mouse_position -= m_Offset;
			sf::Vector2f window_size(m_Window.getSize());

			if (mouse_position.x < 0)
				mouse_position.x = 0;
			else if (mouse_position.x > window_size.x - m_Shape->getGlobalBounds().width)
				mouse_position.x = window_size.x - m_Shape->getGlobalBounds().width;
			if (mouse_position.y < 0)
				mouse_position.y = 0;
			else if (mouse_position.y > window_size.y - m_Shape->getGlobalBounds().height)
				mouse_position.y = window_size.y - m_Shape->getGlobalBounds().height;

			// Update positions with the virtual function
			UpdatePosition(mouse_position);
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && m_Shape->getGlobalBounds().contains(mouse_position))
		{
			GUI::s_Token = true;
			m_Move = true;
			m_Window.setMouseCursorVisible(false);
			m_Offset = sf::Vector2f(mouse_position - m_Shape->getPosition());
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
						if (it->m_Shape->getGlobalBounds().intersects(m_Shape->getGlobalBounds()))
						{
							m_Shape = dynamic_cast<TypeOfShape*>(m_Shape);
							UpdatePosition(GetNewPosition(it->m_Shape->getGlobalBounds()));
						}
					}
				}
			}
			m_Move = false;
			m_Window.setMouseCursorVisible(true);
			GUI::s_Token = false;
		}
	}
};

#endif // !GUI_H

