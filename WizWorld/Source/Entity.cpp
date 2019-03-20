#include "../Include/Entity.h"

Entity::Entity() : m_speed(100.f)
{
	m_shape.setSize(sf::Vector2f(50.f, 50.f));
}

Entity::Entity(float speed, float x_shape, float y_shape) : m_speed(speed)
{
	m_shape.setSize(sf::Vector2f(x_shape, y_shape));
}

Entity::~Entity()
{}

void Entity::move(const float& dt, const float x_motion, const float y_motion)
{
	m_shape.move(x_motion * dt * m_speed, y_motion * dt * m_speed);
}

void Entity::update(const float & dt)
{
}

void Entity::render(sf::RenderTarget & target)
{
	target.draw(m_shape);
}
