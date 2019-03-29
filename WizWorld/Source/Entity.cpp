#include "../Include/Entity.h"

Entity::Entity(double speed, sf::Texture *texture) : m_speed(speed)
{
	m_sprite = nullptr;
	m_texture = nullptr;
}

Entity::~Entity()
{
	delete m_sprite;
}
/* This fonction is meant to be overloaded by entities that need to move */
void Entity::move(const double& dt, const double x_motion, const double y_motion)
{
	if (m_sprite)
		m_sprite->move(x_motion * dt * m_speed, y_motion * dt * m_speed);
}

void Entity::update(const double & dt)
{}

void Entity::render(sf::RenderTarget* target)
{
	if (m_sprite)
		target->draw(*m_sprite);
}

void Entity::createSprite(sf::Texture * texture)
{
	m_sprite = new sf::Sprite();
	m_texture = texture;
	m_sprite->setTexture(*m_texture);
}
