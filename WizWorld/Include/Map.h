#ifndef MAP_H
#define MAP_H

class Map
{
public:
	// Constructor
	Map(std::string texture_path, int map_scale = 1, bool collision = false);
	Map(const Map &map);
	// Destructor
	virtual ~Map();

	// Functions
	void Update(const float & dt);
	void Render(sf::RenderTarget* target);
	void InitPositions(std::string path);

	// Getters
	sf::Vector2f getSize() const;
	sf::Vector2f getPosition() const;
	sf::Vector2f getStartingPosition(std::string key) const;
	const sf::RectangleShape & getShape() const;
	const int & getScale() const;
	const sf::Color getPixelColor(int x, int y) const;
	sf::Texture *getTexture();

	// Setter
	inline void setScale(int scale) { this->scale = scale; }

private:
	sf::RectangleShape map;
	sf::Texture* mapTexture;
	sf::Image mapImage;
	std::map<std::string, sf::Vector2f> startingPositions;
	int scale;
};



#endif // !MAP_H