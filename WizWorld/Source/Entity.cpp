#include "../Include/Entity.h"


/* Constructor */
// If the entity needs a sprite, to move or to have animations, it needs to use the initrs to create them
Entity::Entity() : sprite(nullptr), movement(nullptr), animation(nullptr), hitbox(nullptr)
{}

Entity::~Entity()
{}

/*	Move the entity if it has a sprite and a movement_component.
	Play animation if it has a animation_component */
void Entity::move(const float& dt, const float x_motion, const float y_motion)
{
	if (this->sprite && this->movement)
	{
		this->movement->move(dt, x_motion, y_motion);
		this->sprite->move(this->movement->getVelocity());
		// An entity with animation needs to define those four moves
		if (this->animation)
		{
			if (this->movement->getVelocity().y == 0)
			{
				if (this->movement->getVelocity().x < 0)
				{
					this->animation->setSide(AnimationSide::LEFT);
					this->animation->playAnimation(this->movement->getVelocity().x, dt, "MOVE_LEFT");
				}
				else if (this->movement->getVelocity().x > 0)
				{
					this->animation->setSide(AnimationSide::RIGHT);
					this->animation->playAnimation(this->movement->getVelocity().x, dt, "MOVE_RIGHT");
				}
			}
			else
			{
				if (this->movement->getVelocity().y < 0)
				{
					this->animation->setSide(AnimationSide::UP);
					this->animation->playAnimation(this->movement->getVelocity().y, dt, "MOVE_UP");
				}
				else if (this->movement->getVelocity().y > 0)
				{
					this->animation->setSide(AnimationSide::DOWN);
					this->animation->playAnimation(this->movement->getVelocity().y, dt, "MOVE_DOWN");
				}
			}
		}
	}
}

void Entity::render(sf::RenderTarget* target)
{
	if (this->sprite)
	{
		target->draw(*this->sprite);
		this->hitbox->render(target);
	}
}

/* Initializers (if an entity use one of these initrs, it needs to delete what it has created in its OWN destructor */
void Entity::createSprite()
{
	this->sprite = new sf::Sprite();
	this->hitbox = new HitboxComponent(this->sprite, 64, 64);

}

void Entity::iniatializeAnimationComponent()
{
	this->animation = new AnimationComponent(this->sprite);
}

/* Has to be overloaded because each entity has its textures */
void Entity::initTextures()
{}


void Entity::initMovementComponent(float maxVelocity, float acceleration, float deceleration)
{
	this->movement = new MovementComponent(maxVelocity, acceleration, deceleration);
}

/* Getters */
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
