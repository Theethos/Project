#include "../Include/TileMap.h"

TileMap::TileMap(std::string config_file_path)
{
	this->initMap(config_file_path);
}

TileMap::~TileMap()
{
}

void TileMap::initTilesTextures(std::string config_file_path)
{
	std::ifstream config_file(config_file_path);

	if (config_file.is_open())
	{
		int id = 0;
		std::string tile_path = "";
		while (config_file >> id >> tile_path)
		{
			this->tilesTextures[id].loadFromFile(tile_path);
		}
	}

	config_file.close();
}

void TileMap::initMap(std::string config_file_path)
{
	std::ifstream config_file(config_file_path);

	if (config_file.is_open())
	{
		config_file >> this->dimensions.x >> this->dimensions.y;

		int i = 0, j = 0, k = 0;

		for (i; i < this->dimensions.x; ++i)
		{
			for (j; j < this->dimensions.y; ++j)
			{

			}
		}
	}

	config_file.close();
}
