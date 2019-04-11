#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Entity.h"

class Player : public Entity
{
public:
	Player(float maxVelocity, float x_pos, float y_pos, std::string config_file, int sprite_scale = 1);
	virtual ~Player();

	void iniatializeAnimationComponent(std::string config_file);
	void update(const float &dt);

	// Getters
	sf::Sprite* getSprite() const;
};

#endif //!_PLAYER_H_