#ifndef MAP_H
#define MAP_H

class Map
{
public:
	Map(std::string texture_path, int map_scale = 1);
	virtual ~Map();

	void update(const float & dt);
	void render(sf::RenderTarget* target);

	// Getters
	sf::Vector2f getSize() const;
	sf::Vector2f getPosition() const;

private:
	sf::RectangleShape map;
	sf::Texture* mapTexture;
	int scale;
};



#endif // !MAP_H