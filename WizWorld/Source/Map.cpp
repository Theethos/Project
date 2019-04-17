#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/Map.h"

// Constructor
Map::Map(std::string texture_path, int map_scale) : 
scale(map_scale)
{
	this->mapTexture = new sf::Texture;
	if (this->mapTexture->loadFromFile(texture_path))
	{
		this->map.setTexture(this->mapTexture);
		this->map.setPosition(0, 0);
		this->map.setSize(static_cast<sf::Vector2f>(this->mapTexture->getSize()));
		this->map.setScale(scale, scale);

		this->mapImage = this->mapTexture->copyToImage();
	}
	else
	{
		this->map.setFillColor(sf::Color::Black);
	}

}
// Destructor
Map::~Map()
{
	delete this->mapTexture;
}

// Functions
void Map::Update(const float & dt)
{
}

void Map::Render(sf::RenderTarget * target)
{
	target->draw(this->map);
}

// Getters
sf::Vector2f Map::getSize() const
{
	return this->map.getSize();
}

sf::Vector2f Map::getPosition() const
{
	return this->map.getPosition();
}

const sf::RectangleShape& Map::getShape() const
{
	return this->map;
}

const int & Map::getScale() const
{
	return this->scale;
}

const sf::Color Map::getPixelColor(int x, int y) const
{
	if (0 <= x && x < mapImage.getSize().x && 0 <= y && y < mapImage.getSize().y)
		return this->mapImage.getPixel(x, y);
	else
		return sf::Color::Red;
}

