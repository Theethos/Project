#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <vector>
#define _REQUIRE_SFML_
	#include "Macro_Include.h"
#undef _REQUIRE_SFML_

class TileMap
{
public:
	TileMap(std::string config_file_path);
	virtual ~TileMap();

private:
	// Private class 
	struct Tile
	{
		sf::RectangleShape tile;
		sf::Texture *texture;

		Tile(sf::Texture *texture, float pos_x, float pos_y)
		{
			this->texture = texture;

			this->tile.setSize(sf::Vector2f(this->texture->getSize().x, this->texture->getSize().y));
			this->tile.setTexture(this->texture);
			this->tile.setPosition(sf::Vector2f(pos_x, pos_y));
		}
		~Tile(){}
	};

	// Attributes
	std::vector<std::vector<std::vector<Tile>>> map;
	std::map<int, sf::Texture> tilesTextures;
	sf::Vector2u dimensions;
	
	// Functions
	void initTilesTextures(std::string config_file_path);
	void initMap(std::string config_file_path);
};


#endif //!TILE_MAP_H