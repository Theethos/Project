#ifndef MAP_H
#define MAP_H

class Map
{
public:
	// Constructor
	Map(std::string texture_path, int map_scale = 1);
	// Destructor
	virtual ~Map();

	// Functions
	void Update(const float & dt);
	void Render(sf::RenderTarget* target);

	// Getters
	sf::Vector2f getSize() const;
	sf::Vector2f getPosition() const;
	const sf::RectangleShape & getShape() const;
	const int & getScale() const;
	const sf::Color getPixelColor(int x, int y) const;

private:
	sf::RectangleShape map;
	sf::IntRect displayedMap;
	sf::Texture* mapTexture;
	sf::Image mapImage;
	int scale;
};



#endif // !MAP_H