#include "../Include/Entity.h"

Entity::Entity() : m_speed(200.f)
{
	m_shape.setSize(sf::Vector2f(50.f, 50.f));
}

Entity::Entity(double speed, double x_shape, double y_shape) : m_speed(speed)
{
	m_shape.setSize(sf::Vector2f(x_shape, y_shape));
}

Entity::~Entity()
{}

void Entity::move(const double& dt, const double x_motion, const double y_motion)
{
	m_shape.move(x_motion * dt * m_speed, y_motion * dt * m_speed);
}

void Entity::update(const double & dt)
{
}

void Entity::render(sf::RenderTarget* target)
{
	target->draw(m_shape);
}
