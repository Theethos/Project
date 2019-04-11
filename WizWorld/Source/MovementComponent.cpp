#include "../Include/Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/MovementComponent.h"

/* Constructor */
MovementComponent::MovementComponent(float maxVelocity, float acceleration, float deceleration)
	: maxVelocity(maxVelocity), velocity({0,0}), acceleration(acceleration), deceleration(deceleration)
{}

/* Destructor */
MovementComponent::~MovementComponent()
{}

/* Functions */
void MovementComponent::move(const float & dt, const float dir_x, const float dir_y)
{
	// Update the velocity
	this->velocity.x += dir_x * this->acceleration * dt;
	this->velocity.y += dir_y * this->acceleration * dt; 
		
	// Checking if the velocity is not over the max velocity
	// Going right
	if (this->velocity.x > this->maxVelocity)
	{
		this->velocity.x = this->maxVelocity;
	}
	// Going left
	else if (this->velocity.x < -this->maxVelocity)
	{
		this->velocity.x = -this->maxVelocity;
	}
	// Going down
	if (this->velocity.y > this->maxVelocity)
	{
		this->velocity.y = this->maxVelocity;
	}
	// Going up
	else if (this->velocity.y < -this->maxVelocity)
	{
		this->velocity.y = -this->maxVelocity;
	}
}

void MovementComponent::update(const float & dt, sf::Sprite *sprite)
{
	// Decelerating phase and check that velocity doesn't go below 0
	// Going right
	if (this->velocity.x > 0)
	{
		this->velocity.x -= this->deceleration * dt;
		if (this->velocity.x < 0)
		{
			this->velocity.x = 0;
		}
	}
	// Going left
	else if (this->velocity.x < 0)
	{
		this->velocity.x += this->deceleration * dt;
		if (this->velocity.x > 0)
		{
			this->velocity.x = 0;
		}
	}
	// Going down
	if (this->velocity.y > 0)
	{
		this->velocity.y -= this->deceleration * dt;
		if (this->velocity.y < 0)
		{
			this->velocity.y = 0;
		}
	}
	// Going up
	else if (this->velocity.y < 0)
	{
		this->velocity.y += this->deceleration * dt;
		if (this->velocity.y > 0)
		{
			this->velocity.y = 0;
		}
	}
	// Finaly move the sprite with the correct velocity
	sprite->move(this->velocity);
}

const sf::Vector2f & MovementComponent::getVelocity() const
{
	return this->velocity;
}

const float & MovementComponent::getMaxVelocity() const
{
	return this->maxVelocity;
}