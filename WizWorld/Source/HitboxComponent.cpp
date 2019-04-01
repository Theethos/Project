#include "../Include/HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite *sprite, const float width, const float height) : m_sprite(sprite)
{
	m_hitbox.setPosition(m_sprite->getPosition());
	m_hitbox.setSize(sf::Vector2f(width, height));

	m_hitbox.setFillColor(sf::Color::Transparent);
	m_hitbox.setOutlineThickness(1.f);
	m_hitbox.setOutlineColor(sf::Color::Red);
}

HitboxComponent::~HitboxComponent()
{}

void HitboxComponent::update()
{
	m_hitbox.setPosition(m_sprite->getPosition());
}

void HitboxComponent::render(sf::RenderTarget * target) const
{
	target->draw(m_hitbox);
}

bool HitboxComponent::checkCollision(const sf::FloatRect & rect)
{
	return m_hitbox.getGlobalBounds().intersects(rect);
}