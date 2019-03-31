#include "../Include/Entity.h"


/* Constructor */
// If the entity needs a sprite, to move or to have animations, it needs to use the initializers to create them
Entity::Entity() : m_sprite(nullptr), m_movement(nullptr), m_animation(nullptr)
{}

Entity::~Entity()
{}

/*	Move the entity if it has a sprite and a movement_component.
	Play animation if it has a animation_component */
void Entity::move(const float& dt, const float x_motion, const float y_motion)
{
	if (m_sprite && m_movement)
	{
		m_movement->move(dt, x_motion, y_motion);
		m_sprite->move(m_movement->getVelocity());
		// An entity with animation needs to define those four moves
		if (m_animation)
		{
			if (m_movement->getVelocity().y == 0)
			{
				if (m_movement->getVelocity().x < 0)
				{
					m_animation->setSide(AnimationSide::LEFT);
					m_animation->playAnimation(dt, "MOVE_LEFT");
				}
				else if (m_movement->getVelocity().x > 0)
				{
					m_animation->setSide(AnimationSide::RIGHT);
					m_animation->playAnimation(dt, "MOVE_RIGHT");
				}
			}
			else
			{
				if (m_movement->getVelocity().y < 0)
				{
					m_animation->setSide(AnimationSide::UP);
					m_animation->playAnimation(dt, "MOVE_UP");
				}
				else if (m_movement->getVelocity().y > 0)
				{
					m_animation->setSide(AnimationSide::DOWN);
					m_animation->playAnimation(dt, "MOVE_DOWN");
				}
			}
		}
	}
}

void Entity::render(sf::RenderTarget* target)
{
	if (m_sprite)
		target->draw(*m_sprite);
}

/* Initializers (if an entity use one of these initializers, it needs to delete what it has created in its OWN destructor */
void Entity::createSprite()
{
	m_sprite = new sf::Sprite();
}

void Entity::iniatializeAnimationComponent()
{
	m_animation = new AnimationComponent(m_sprite);
}

/* Has to be overloaded because each entity has its textures */
void Entity::initializeTextures()
{}

void Entity::initializeMovementComponent(float maxVelocity, float acceleration, float deceleration)
{
	m_movement = new MovementComponent(maxVelocity, acceleration, deceleration);
}

/* Getters */
MovementComponent * Entity::getMovement() const
{
	if (m_movement)
		return m_movement;
}

AnimationComponent * Entity::getAnimation() const
{
	if (m_animation)
		return m_animation;
}
