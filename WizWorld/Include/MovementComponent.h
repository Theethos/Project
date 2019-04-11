#ifndef _MOVEMENT_COMPONENT_H_
#define _MOVEMENT_COMPONENT_H_

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
	float maxVelocity;

	float acceleration;
	float deceleration;
	
	// Current "speed"
	sf::Vector2f velocity;

};

#endif //!_MOVEMENT_COMPONENT_H_

