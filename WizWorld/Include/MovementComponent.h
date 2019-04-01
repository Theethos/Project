#ifndef _MOVEMENT_COMPONENT_H_
#define _MOVEMENT_COMPONENT_H_

#define _REQUIRE_SFML_
	#include "Macro_Include.h"
#undef _REQUIRE_SFML_

class MovementComponent
{
public:
	MovementComponent(float maxVelocity, float acceleration, float deceleration);
	virtual ~MovementComponent();

	void move(const float & dt, const float dir_x, const float dir_y);
	void update(const float & dt, sf::Sprite *sprite);

	/* Getters */
	const sf::Vector2f &getVelocity() const;
	const float & getMaxVelocity() const;

private:
	// Maximum "speed"
	float m_maxVelocity;

	float m_acceleration;
	float m_deceleration;
	
	// Current "speed"
	sf::Vector2f m_velocity;

};

#endif //!_MOVEMENT_COMPONENT_H_

