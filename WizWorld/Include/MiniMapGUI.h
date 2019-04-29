#ifndef MINI_MAP_GUI_H
#define MINI_MAP_GUI_H

#include "GUI.h"
#include "Map.h"

class MiniMapGUI : public GUI
{
public:
	// Constructor
	MiniMapGUI(sf::RenderWindow &window, Player & player, sf::Texture *mapTexture);
	// Destructor
	~MiniMapGUI();

	// Functions
	void Update(const float& dt);
	void Render(sf::RenderTarget *target);

	// Setter
	void setTexture(sf::Texture *texture);

	static const float _miniMapScale;
private:
	// Private function
	void UpdatePosition(const sf::Vector2f &mousPos);
	void UpdatePlayerPosition();

	// Related map
	sf::RectangleShape _mapShape;
	sf::Texture *_mapTexture;

	// Entity infos
	sf::CircleShape _playerPosition;
};

#endif // !MINI_MAP_GUI_H
