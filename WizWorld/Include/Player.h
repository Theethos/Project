#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Entity.h"


class Player : public Entity
{
public:
	Player(double speed, double x_pos, double y_pos, sf::Texture *texture);
	virtual ~Player();

};

#endif //!_PLAYER_H_