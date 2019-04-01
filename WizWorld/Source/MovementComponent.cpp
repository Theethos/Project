#include "../Include/MovementComponent.h"

/* Constructor */
MovementComponent::MovementComponent(float maxVelocity, float acceleration, float deceleration)
	: m_maxVelocity(maxVelocity), m_velocity({0,0}), m_acceleration(acceleration), m_deceleration(deceleration)
{}

/* Destructor */
MovementComponent::~MovementComponent()
{}

/* Functions */
void MovementComponent::move(const float & dt, const float dir_x, const float dir_y)
{
	// Update the velocity
	m_velocity.x += dir_x * m_acceleration * dt;
	m_velocity.y += dir_y * m_acceleration * dt; 
		
	// Checking if the velocity is not over the max velocity
	// Going right
	if (m_velocity.x > m_maxVelocity)
	{
		m_velocity.x = m_maxVelocity;
	}
	// Going left
	else if (m_velocity.x < -m_maxVelocity)
	{
		m_velocity.x = -m_maxVelocity;
	}
	// Going down
	if (m_velocity.y > m_maxVelocity)
	{
		m_velocity.y = m_maxVelocity;
	}
	// Going up
	else if (m_velocity.y < -m_maxVelocity)
	{
		m_velocity.y = -m_maxVelocity;
	}
}

void MovementComponent::update(const float & dt, sf::Sprite *sprite)
{
	// Decelerating phase and check that velocity doesn't go below 0
	// Going right
	if (m_velocity.x > 0)
	{
		m_velocity.x -= m_deceleration * dt;
		if (m_velocity.x < 0)
		{
			m_velocity.x = 0;
		}
	}
	// Going left
	else if (m_velocity.x < 0)
	{
		m_velocity.x += m_deceleration * dt;
		if (m_velocity.x > 0)
		{
			m_velocity.x = 0;
		}
	}
	// Going down
	if (m_velocity.y > 0)
	{
		m_velocity.y -= m_deceleration * dt;
		if (m_velocity.y < 0)
		{
			m_velocity.y = 0;
		}
	}
	// Going up
	else if (m_velocity.y < 0)
	{
		m_velocity.y += m_deceleration * dt;
		if (m_velocity.y > 0)
		{
			m_velocity.y = 0;
		}
	}
	// Finaly move the sprite with the correct velocity
	sprite->move(m_velocity);
}

const sf::Vector2f & MovementComponent::getVelocity() const
{
	return m_velocity;
}

const float & MovementComponent::getMaxVelocity() const
{
	return m_maxVelocity;
}