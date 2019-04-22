#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/MovementComponent.h"

// Constructors
MovementComponent::MovementComponent(float maxVelocity, float acceleration, float deceleration) :
maxVelocity(maxVelocity), 
velocity({0,0}),
acceleration(acceleration),
deceleration(deceleration)
{}

MovementComponent::MovementComponent(const MovementComponent & other)
{
	this->maxVelocity = other.maxVelocity;
	this->acceleration = other.acceleration;
	this->deceleration = other.deceleration;
	this->velocity = other.velocity;
}

// Destructor
MovementComponent::~MovementComponent()
{}

// Functions
void MovementComponent::Move(const float & dt, const float dir_x, const float dir_y)
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

void MovementComponent::Update(const float & dt, sf::Sprite *sprite)
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

// Operator
MovementComponent MovementComponent::operator=(const MovementComponent & other)
{
	this->maxVelocity = other.maxVelocity;
	this->acceleration = other.acceleration;
	this->deceleration = other.deceleration;
	this->velocity = other.velocity;

	return *this;
}

// Getters
const sf::Vector2f & MovementComponent::getVelocity() const
{
	return this->velocity;
}

const float & MovementComponent::getMaxVelocity() const
{
	return this->maxVelocity;
}

void MovementComponent::setMaxVelocity(float maxVelocity)
{
	this->maxVelocity = maxVelocity;
}
// Setters
void MovementComponent::setVelocity(sf::Vector2f velocity)
{
	this->velocity = velocity;
}

void MovementComponent::setVelocity(float x, float y)
{
	this->velocity = sf::Vector2f(x, y);
}

void MovementComponent::setVelocityX(float x)
{
	this->velocity.x = x;
}

void MovementComponent::setVelocityY(float y)
{
	this->velocity.y = y;
}
