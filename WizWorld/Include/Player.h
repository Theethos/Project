#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Entity.h"
#include "StatisticsComponent.h"

class Player : public Entity
{
public:
	// Constructor
	Player(float maxVelocity, float x_pos, float y_pos, std::string config_file, std::string name, sf::Font* font, int sprite_scale = 1);
	// Destructor
	virtual ~Player();

	// Functions
	void Update(const float &dt);
	void Render(sf::RenderTarget* target);

	// Getter
	sf::Sprite* getSprite() const;
	const std::string &getName() const;
	StatisticsComponent &getStatistics();

private:
	// Pseudo of the player
	std::string name;
	sf::Text nameRendered;
	sf::Font* font;

	// Attributes of the player
	StatisticsComponent _statistics;

	// Private functions
	void InitAnimationComponent(std::string config_file);
	void InitName();


};

#endif //!_PLAYER_H_