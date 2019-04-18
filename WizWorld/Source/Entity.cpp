#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/Entity.h"

// Constructor
Entity::Entity() : 
sprite(nullptr), 
movement(nullptr), 
animation(nullptr), 
hitbox(nullptr)
{}
// Destructor
Entity::~Entity()
{}

// Functions
void Entity::Move(const float& dt, const float x_motion, const float y_motion)
{
	if (this->sprite && this->movement)
	{
		this->movement->Move(dt, x_motion, y_motion);
		this->sprite->move(this->movement->getVelocity());
		// An entity with animation needs to define those four "MOVE_..."
		// Plays the right animation
		if (this->animation)
		{
			if (this->movement->getVelocity().y == 0)
			{
				// Moving left
				if (this->movement->getVelocity().x < 0)
				{
					this->animation->setSide(AnimationSide::LEFT);
					this->animation->PlayAnimation(this->movement->getVelocity().x, dt, "MOVE_LEFT");
				}
				// Moving right
				else if (this->movement->getVelocity().x > 0)
				{
					this->animation->setSide(AnimationSide::RIGHT);
					this->animation->PlayAnimation(this->movement->getVelocity().x, dt, "MOVE_RIGHT");
				}
			}
			else
			{
				// Moving up
				if (this->movement->getVelocity().y < 0)
				{
					this->animation->setSide(AnimationSide::UP);
					this->animation->PlayAnimation(this->movement->getVelocity().y, dt, "MOVE_UP");
				}
				// Moving up
				else if (this->movement->getVelocity().y > 0)
				{
					this->animation->setSide(AnimationSide::DOWN);
					this->animation->PlayAnimation(this->movement->getVelocity().y, dt, "MOVE_DOWN");
				}
			}
		}
	}
}

void Entity::Render(sf::RenderTarget* target)
{
	if (this->sprite)
	{
		target->draw(*this->sprite);
	}
}

void Entity::InitSprite()
{
	this->sprite = new sf::Sprite();
	this->hitbox = new HitboxComponent(this->sprite, 64, 64);

}

void Entity::InitAnimationComponent()
{
	this->animation = new AnimationComponent(this->sprite);
}

void Entity::InitTextures()
{}

void Entity::InitMovementComponent(float maxVelocity, float acceleration, float deceleration)
{
	this->movement = new MovementComponent(maxVelocity, acceleration, deceleration);
}

// Getters
MovementComponent * Entity::getMovement() const
{
	if (this->movement)
		return this->movement;
}

AnimationComponent * Entity::getAnimation() const
{
	if (this->animation)
		return this->animation;
}
