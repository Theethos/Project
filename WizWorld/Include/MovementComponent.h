#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H

class MovementComponent
{
public:
	// Constructors
	MovementComponent(float maxVelocity, float acceleration, float deceleration);
	MovementComponent(const MovementComponent &other);
	// Destructor
	virtual ~MovementComponent();

	// Function
	void Move(const float & dt, const float dir_x, const float dir_y);
	void Update(const float & dt, sf::Sprite *sprite);

	// Operator
	MovementComponent operator=(const MovementComponent &other);

	// Getters
	const sf::Vector2f &getVelocity() const;
	const float & getMaxVelocity() const;

	// Setters
	void setVelocity(sf::Vector2f velocity);
	void setVelocity(float x, float y);
	void setVelocityX(float x);
	void setVelocityY(float y);

private:
	// Maximum "speed"
	float maxVelocity;

	float acceleration;
	float deceleration;
	
	// Current "speed"
	sf::Vector2f velocity;
};

#endif //!MOVEMENT_COMPONENT_H

