#ifndef MENU_GUI_H
#define MENU_GUI_H

#include "GUI.h"

class MenuGUI : public GUI
{
public:
	// Constructor
	MenuGUI(sf::RenderWindow &window, Player &player);
	// Destructor
	~MenuGUI();

	// Functions
	void Update(const float &dt);
	void Render(sf::RenderTarget &target);

private:
	// Redefining GlobalShape
	sf::ConvexShape m_GlobalShape;

	// Private function
	void UpdatePosition(const sf::Vector2f &mouse_position);
};

#endif // !MENU_GUI_H
