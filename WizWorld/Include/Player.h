#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Entity.h"

class Player : public Entity
{
public:
	Player(float maxVelocity, float x_pos, float y_pos, std::string config_file, std::string name, sf::Font* font, int sprite_scale = 1);
	virtual ~Player();

	void iniatializeAnimationComponent(std::string config_file);
	void update(const float &dt);
	void render(sf::RenderTarget* target);

	void initName();

	// Getters
	sf::Sprite* getSprite() const;

private:
	std::string name;
	sf::Text nameRendered;
	sf::Font* font;

};

#endif //!_PLAYER_H_