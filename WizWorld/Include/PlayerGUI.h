#ifndef PLAYER_GUI_H
#define PLAYER_GUI_H

#include "GUI.h"

class PlayerGUI : public GUI
{
public:
	// Constructor
	PlayerGUI(sf::RenderWindow &window, Player &player, std::string &player_name);
	// Destructor
	~PlayerGUI();

	// Functions
	void Update(const float &dt);
	void Render(sf::RenderTarget *target);

private:
	// Private function
	void UpdatePosition(const sf::Vector2f &mousePos);

	// Health bar
	sf::RectangleShape _healthBarFull;
	sf::RectangleShape _healthBar;
	sf::Text _healthPoints;

	// Exp bar
	sf::RectangleShape _expBarFull;
	sf::RectangleShape _expBar;
	sf::Text _expPoints;

	// Mana bar
	sf::RectangleShape _manaBarFull;
	sf::RectangleShape _manaBar;
	sf::Text _manaPoints;

	// Infos
	sf::Text _pseudo;
	sf::CircleShape _levelShape;
	sf::Text _level;
};


#endif // !PLAYER_GUI_H

