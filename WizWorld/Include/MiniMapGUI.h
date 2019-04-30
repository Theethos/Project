#ifndef MINI_MAP_GUI_H
#define MINI_MAP_GUI_H

#include "GUI.h"
#include "Map.h"

class MiniMapGUI : public GUI
{
public:
	// Constructor
	MiniMapGUI(sf::RenderWindow& window, Player& player, sf::Texture& map_texture);
	// Destructor
	~MiniMapGUI();

	// Functions
	void Update(const float& dt);
	void Render(sf::RenderTarget& target);

	// Setter
	void SetTexture(sf::Texture& texture);

	static const float s_MiniMapScale;
private:
	// Redefining GlobalShape
	sf::RectangleShape m_GlobalShape;

	// Private function
	void UpdatePosition(const sf::Vector2f& mouse_position);
	void UpdatePlayerPosition();

	// Related map
	sf::RectangleShape m_MapShape;
	sf::Texture& m_MapTexture;

	// Entity infos
	sf::CircleShape m_PlayerPosition;
};

#endif // !MINI_MAP_GUI_H
