#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Entity.h"


class Player : public Entity
{
public:
	Player(float maxVelocity, float x_pos, float y_pos);
	virtual ~Player();

	void iniatializeAnimationComponent();
	void update(const float &dt);
};

#endif //!_PLAYER_H_