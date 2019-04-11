#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/Map.h"

Map::Map(std::string texture_path, int map_scale) : scale(map_scale)
{
	this->mapTexture = new sf::Texture;
	if (this->mapTexture->loadFromFile(texture_path))
	{
		this->map.setTexture(this->mapTexture);
		this->map.setPosition(0, 0);
		this->map.setSize(static_cast<sf::Vector2f>(this->mapTexture->getSize()));
		this->map.setScale(scale, scale);
	}
	else
	{
		this->map.setFillColor(sf::Color::Black);
	}

}

Map::~Map()
{
	delete this->mapTexture;
}

void Map::update(const float & dt)
{
}

void Map::render(sf::RenderTarget * target)
{
	target->draw(this->map);
}

sf::Vector2f Map::getSize() const
{
	return this->map.getSize();
}

sf::Vector2f Map::getPosition() const
{
	return this->map.getPosition();
}
