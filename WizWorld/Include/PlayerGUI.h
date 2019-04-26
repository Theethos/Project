#ifndef PLAYER_GUI_H
#define PLAYER_GUI_H

#include "Player.h"

class PlayerGUI
{
public:
	// Constructor
	PlayerGUI(sf::RenderWindow &window, Player &player, std::string &player_name);
	// Destructor
	virtual ~PlayerGUI();

	// Functions
	virtual void Update(const float &dt);
	virtual void Render(sf::RenderTarget *target);

private:
	// Entity ralated to
	Player &_player;

	// Global
	sf::RenderWindow &_window;
	sf::RectangleShape _globalShape;
	sf::Color _globalColor;
	sf::Font _font;

	// Health bar
	sf::RectangleShape _healthBar;
	sf::Text _healthPoints;

	// Exp bar
	sf::RectangleShape _expBar;
	sf::Text _expPoints;

	// Infos
	sf::Text _pseudo;
	sf::Text _level;
};


#endif // !PLAYER_GUI_H

