#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/Map.h"

// Constructor
Map::Map(std::string texture_path, int map_scale, bool collision) :
scale(map_scale)
{
	this->mapTexture = new sf::Texture;
	if (this->mapTexture->loadFromFile(texture_path))
	{
		if (collision)
			this->mapImage = this->mapTexture->copyToImage();
		else
		{
			this->map.setTexture(this->mapTexture);
			this->map.setPosition(0, 0);
			this->map.setSize(static_cast<sf::Vector2f>(this->mapTexture->getSize()));
			this->map.setScale(scale, scale);
		}
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

sf::Texture * Map::getTexture()
{
	return this->mapTexture;
}

sf::Vector2f Map::getStartingPosition(std::string key) const
{
	if (this->startingPositions.count(key))
	{
		return this->startingPositions.at(key);
	}
}
/////////////////////////////////////////////////////////////////////
/// Initializes the starting position with the parameters in the given file
/// Format :
/// Key >> x >> y;
/////////////////////////////////////////////////////////////////////
void Map::InitPositions(std::string path)
{
	std::ifstream config_file(path);
	if (config_file.is_open())
	{
		std::string key;
		float x, y;

		while (config_file >> key >> x >> y)
		{
			this->startingPositions[key] = sf::Vector2f(x * this->scale, y * this->scale);
		}
		config_file.close();
	}
}

