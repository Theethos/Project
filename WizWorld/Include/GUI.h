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
	virtual void Move();
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
	sf::RectangleShape m_GlobalShape;
	sf::Color m_GlobalColor;
	sf::Color m_GlobalTextColor;

	// Private functions
	// Defines the behavior to use when function Move() is called (When user use Drag&Drop on the GUI module)
	virtual void UpdatePosition(const sf::Vector2f &mouse_position) = 0;
	// Get the most likely position of the GUI module if it collides with an other
	virtual const sf::Vector2f GetNewPosition(const sf::FloatRect & intersect) const;
};

#endif // !GUI_H

